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
	ptr = result;

	double startTick = 0, endTick =0;
	double setupTime = 0, shutdownTime =0;
	for(int i=0; i<50; i++){
		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		startTick = __rdtsc();
		// Connect to server.
		connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		endTick = __rdtsc();
		setupTime += (endTick - startTick);

		startTick = __rdtsc();
		// shutdown the connection since no more data will be sent
		shutdown(ConnectSocket, SD_SEND);
		closesocket(ConnectSocket);
		endTick = __rdtsc();
		shutdownTime += (endTick- startTick);
	}

	printf("Socket setup time: %f cycles.\nSocket shutdown time: %f cycles.\n", setupTime/50, shutdownTime/50);

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	system("PAUSE");
	return 0;
}
