#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QtEndian>
#include <cstdint>

class TcpClient : public QObject
{
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = nullptr);

    void connectToHost(const QString &hostAddress, quint16 port);
    void sendUint32(uint32_t value);
private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
};

#endif // TCPCLIENT_H
