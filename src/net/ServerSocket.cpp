#include "net/ServerSocket.h"
#include <iostream>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;
using namespace javaish::net;

ServerSocket::ServerSocket(unsigned short port, unsigned int soTimeout) : port(port), soTimeout(soTimeout) {
	struct sockaddr_in serverAddr;
	
	socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFileDescriptor < 0) 
		throw std::exception(); //TODO: Ex
	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(port);
	if (bind(socketFileDescriptor, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) 
		throw std::exception(); //TODO: Ex
	listen(socketFileDescriptor,5);

}

Socket* ServerSocket::acceptSocket()
{
	struct sockaddr_in clientAddr;
	socklen_t clientLen = sizeof(clientAddr);
	int socketFd = accept(socketFileDescriptor, (struct sockaddr *) &clientAddr, &clientLen);
	if (socketFd < 0) 
		throw std::exception(); //TODO: Ex
	
	return new Socket(socketFd);
}


