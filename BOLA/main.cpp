#include <QCoreApplication>
#include <QTimer>

#include "arinc429.h"
#include "tcpclient.h"

#define IP "127.0.0.1"
#define PORT 12346

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TcpClient client;
    Arinc429 myWord;
    const QString host = "127.0.0.1";
    const quint16 port = 12346;
    //client.connectToHost(host, port);
    //QTimer::singleShot(2000, [&client, &myWord](){
    //    client.sendUint32(myWord.encodeWord(DISCRETE, CAPTURE, GLONASS_3, 2, WEST).word);
    //});

    return 0;
}
