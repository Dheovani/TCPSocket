#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

static void exit_error(const char *msg)
{
	printf(msg);
	WSACleanup();
	exit(EXIT_FAILURE);
}

int main(int argc, char **agrv)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		exit_error("WSAStartup failed\n");

	SOCKET server_socket;
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		exit_error("Socket failed");

	struct sockaddr_in addr = { AF_INET, htons(8080), 0 };

	if (bind(server_socket, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR)
		closesocket(server_socket), exit_error("Bind failed");

	if (listen(server_socket, SOMAXCONN) == SOCKET_ERROR)
		closesocket(server_socket), exit_error("Listen failed");

	printf("Server listening on port %d\n", PORT);

	SOCKET new_socket;
	int addr_lenght = sizeof(addr);
	if ((new_socket = accept(server_socket, (struct sockaddr*)&addr, &addr_lenght)) == INVALID_SOCKET)
		closesocket(server_socket), exit_error("Listen failed");

	int rec;
	char buffer[BUFFER_SIZE] = { 0 };
	if ((rec = recv(new_socket, buffer, BUFFER_SIZE, 0)) == SOCKET_ERROR) {
		closesocket(new_socket);
		closesocket(server_socket);
		exit_error("Receive failed\n");
	}

	printf("Message receiverd!\n\n"
		"Content: %s\n\n", buffer);

	printf("Now sending answer to client!");

	const char* hello = 
		"HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello, world!";

	if (send(new_socket, hello, (int)strlen(hello), 0) == SOCKET_ERROR) {
		closesocket(new_socket);
		closesocket(server_socket);
		exit_error("Send failed\n");
	}

	closesocket(new_socket);
	closesocket(server_socket);
	WSACleanup();

	return 0;
}