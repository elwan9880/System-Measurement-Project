#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <intrin.h>
#include <iostream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define TESTNUM 1000
// change server IP address here
#define SERVERADDR "127.0.0.1"

int main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(SERVERADDR, DEFAULT_PORT, &hints, &result);

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		break;
	}

	freeaddrinfo(result);

	// everytime only send one char
	int recvbuflen = 1;
	char recvbuf;
	char *sendbuf = "a";

	// set clock
	double totalTicks = 0;

	// send data to server for TESTNUM times, each time send 1 bytes
	for (int i = 0; i < TESTNUM; i++)
	{
		double startTick = __rdtsc();
		send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
		recv(ConnectSocket, &recvbuf, recvbuflen, 0);
		double endTick = __rdtsc();
		totalTicks += (double)(endTick - startTick);
	}
	printf("Network round trip time: %f cycles.\n", totalTicks / TESTNUM);

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);;

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
	system("PAUSE");

	return 0;
}
