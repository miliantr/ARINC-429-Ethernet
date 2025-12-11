#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);

    // Подключение сигналов сокета к нашим слотам
    connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    // Обработка ошибок. В Qt 5 использовался сигнал error(QAbstractSocket::SocketError)
    // В Qt 6 используется errorOccurred(QAbstractSocket::SocketError)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &TcpClient::onErrorOccurred);
#else
    connect(socket, &QAbstractSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
#endif
}

void TcpClient::connectToHost(const QString &hostAddress, quint16 port)
{
    qDebug() << "Попытка подключения к" << hostAddress << ":" << port;
    socket->connectToHost(hostAddress, port);
}

void TcpClient::sendUint32(uint32_t value)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {

        // Функции qToBigEndian/qFromBigEndian прекрасно работают с uint32_t
        uint32_t networkValue = qToBigEndian(value);

        // Отправляем ровно 4 байта данных
        QByteArray data(reinterpret_cast<const char*>(&networkValue), sizeof(uint32_t));

        socket->write(data);
        qDebug() << "Отправлено uint32_t значение:" << value << "(в байтах BE:" << data.toHex() << ")";
    } else {
        qDebug() << "Ошибка: Соединение не установлено при попытке отправить uint32_t.";
    }
}

void TcpClient::onConnected()
{
    qDebug() << "Подключено к серверу!";
}

void TcpClient::onDisconnected()
{
    qDebug() << "Отключено от сервера.";
}

void TcpClient::onReadyRead()
{
    while (socket->bytesAvailable() >= static_cast<qint64>(sizeof(uint32_t))) {
        QByteArray rawData = socket->read(sizeof(uint32_t));

        uint32_t receivedValue = qFromBigEndian(*reinterpret_cast<const uint32_t*>(rawData.constData()));

        qDebug() << "Получено uint32_t значение:" << receivedValue;
    }
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    qDebug() << "Ошибка сокета:" << socket->errorString();
}
