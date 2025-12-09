#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

#include "arinc429.h"

static constexpr int PORT = 12346;

int main()
{
    WSADATA wsaData;


    Arinc429 myWord;
    std::cout << std::hex << myWord.encodeWord(DISCRETE, CAPTURE, GLONASS_3, 2, WEST).word;

    return 0;
}
