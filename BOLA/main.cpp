#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>
#include <string>

#include "arinc429.h"

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char *argv[])
{
    WSADATA wsData;

    int erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

    SOCKET client = socket(AF_INET, SOCK_STREAM, 0);

    in_addr ip_to_num;
    erStat = inet_pton(AF_INET, "127.0.0.1", &ip_to_num);

    sockaddr_in servInfo;
    ZeroMemory(&servInfo, sizeof(servInfo));

    servInfo.sin_family = AF_INET;
    servInfo.sin_addr = ip_to_num;
    servInfo.sin_port = htons(12346);

    erStat = connect(client, (sockaddr*)&servInfo, sizeof(servInfo));

    const int BUFF_SIZE = 32;
    std::vector <char> serverBuff(BUFF_SIZE), clientBuff(BUFF_SIZE);
    short packet_size = 0;

    Arinc429 myWord;
    uint32_t value = myWord.encodeWord(DISCRETE, CAPTURE, GLONASS_3, 2, WEST).word;
    std::string s = std::to_string(value);
    std::vector <char> vec_str(s.begin(), s.end());

    clientBuff = vec_str;

    while (true) {
        packet_size = send(client, clientBuff.data(), clientBuff.size(), 0);
    }

    closesocket(client);
    WSACleanup();
    return 0;
}
