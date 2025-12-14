#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <chrono> 

#include "arinc429.h"

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char* argv[])
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
    std::vector<char> clientBuff(sizeof(uint32_t));
    Arinc429 myWord;
    uint32_t value = myWord.encodeWord(DISCRETE, CAPTURE, GLONASS_3, 2, WEST).word;
    memcpy(clientBuff.data(), &value, sizeof(uint32_t));
    using namespace std::chrono;
    milliseconds interval(100);
    auto last_send_time = high_resolution_clock::now();
    while (true) {
        auto current_time = high_resolution_clock::now();
        auto elapsed_time = current_time - last_send_time;
        if (elapsed_time >= interval) {
            short packet_size = send(client, clientBuff.data(), clientBuff.size(), 0);
            last_send_time = current_time;
        }
    }
    closesocket(client);
    WSACleanup();
    return 0;
}
