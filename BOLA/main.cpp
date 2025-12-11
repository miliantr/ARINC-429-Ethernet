#include <iostream>
#include <QTcpSocket>

#include "arinc429.h"

#define IP "127.0.0.1"
#define PORT 12346

int main()
{

    Arinc429 myWord;
    std::cout << std::hex << myWord.encodeWord(DISCRETE, CAPTURE, GLONASS_3, 2, WEST).word;

    return 0;
}
