// Server.cpp
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>
#include <cstdint> // Для uint32_t

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main(void)
{
	const char IP_SERV[] = "127.0.0.1";
	const int PORT_NUM = 12346;
	int erStat;

	in_addr ip_to_num;
	erStat = inet_pton(AF_INET, IP_SERV, &ip_to_num);

	if (erStat <= 0) { cerr << "Error in IP translation" << endl; return 1; }

	WSADATA wsData;
	erStat = WSAStartup(MAKEWORD(2, 2), &wsData);

	if (erStat != 0) { cerr << "Error WinSock version initializaion: " << WSAGetLastError() << endl; return 1; }
	else cout << "WinSock initialization is OK" << endl;

	SOCKET ServSock = socket(AF_INET, SOCK_STREAM, 0);

	if (ServSock == INVALID_SOCKET) { cerr << "Error initialization socket: " << WSAGetLastError() << endl; WSACleanup(); return 1; }
	else cout << "Server socket initialization is OK" << endl;

	sockaddr_in servInfo;
	ZeroMemory(&servInfo, sizeof(servInfo));

	servInfo.sin_family = AF_INET;
	servInfo.sin_addr = ip_to_num;
	servInfo.sin_port = htons(PORT_NUM);

	erStat = bind(ServSock, (sockaddr*)&servInfo, sizeof(servInfo));

	if (erStat != 0) { cerr << "Error Socket binding: " << WSAGetLastError() << endl; closesocket(ServSock); WSACleanup(); return 1; }
	else cout << "Binding socket to Server info is OK" << endl;

	erStat = listen(ServSock, SOMAXCONN);

	if (erStat != 0) { cerr << "Can't start to listen to: " << WSAGetLastError() << endl; closesocket(ServSock); WSACleanup(); return 1; }
	else cout << "Listening..." << endl;

	sockaddr_in clientInfo;
	ZeroMemory(&clientInfo, sizeof(clientInfo));
	int clientInfo_size = sizeof(clientInfo);
	SOCKET ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &clientInfo_size);

	if (ClientConn == INVALID_SOCKET) { cerr << "Can't connect to a client: " << WSAGetLastError() << endl; closesocket(ServSock); WSACleanup(); return 1; }
	else {
		cout << "Connection to a client established successfully" << endl;
		char clientIP[22];
		inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, INET_ADDRSTRLEN);
		cout << "Client connected with IP address " << clientIP << endl;
	}

	// --- Логика приема ARINC-данных ---
	uint32_t received_word_value; // Переменная для хранения принятого 32-битного слова
	short packet_size = 0;

	while (true) {
		// Принимаем ровно 4 байта и сохраняем их в received_word_value
		packet_size = recv(ClientConn,
			reinterpret_cast<char*>(&received_word_value),
			sizeof(uint32_t),
			0);

		if (packet_size == SOCKET_ERROR) {
			cerr << "Receive error: " << WSAGetLastError() << endl;
			break;
		}

		if (packet_size == 0) {
			cout << "Client disconnected." << endl;
			break;
		}

		// Выводим принятое значение в шестнадцатеричном формате
		cout << "Received ARINC message: 0x" << hex << received_word_value << dec << endl;

		// Если вам нужен функционал чата, вам придется переделать логику обмена на сервере и клиенте.
		// Сейчас сервер просто ждет следующего сообщения от клиента (нет fgets/send-ответа)
	}

	closesocket(ServSock);
	closesocket(ClientConn);
	WSACleanup();

	return 0;
}
