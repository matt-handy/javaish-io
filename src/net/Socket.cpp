#include "net/Socket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;
using namespace javaish::net;

const size_t Socket::BufferSize = 1024;

Socket::Socket(std::string host, unsigned int port) : host(host), port(port) {
	fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (fileDescriptor < 0){ 
		printf("Error on socket create\n");
		throw std::exception(); //TODO: Ex
	}
	struct hostent *server = gethostbyname(host.c_str());

	struct sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(port);
	if (connect(fileDescriptor,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){ 
		printf("Error on socket connect\n");
		throw std::exception(); //TODO: Ex
	}
}

Socket::Socket(int fileDescriptor) : fileDescriptor(fileDescriptor){

}

Socket::~Socket(){
	close(fileDescriptor);
}

unsigned int Socket::sRead(char* buffer, unsigned int bufferSize){
	int nBytes;
	nBytes = read(fileDescriptor, buffer, bufferSize);
	if(nBytes < 0){
		printf("Error on read\n");
		throw std::exception(); //TODO: Ex
	}
	return nBytes;
}

std::string Socket::readString(){
	std::string toFill;
	char *buffer = new char[BufferSize];
	nullBuffer(buffer, BufferSize);	
	bool readAgain = true;
	while(readAgain){
		unsigned int valRead = sRead(buffer, BufferSize);
		toFill.append(buffer);		
		if(valRead < BufferSize){
			readAgain = false;
		}else{
			nullBuffer(buffer, BufferSize);
		}
	}
	
	return toFill;
}

std::string Socket::readString(unsigned int maxSize){
	char *buffer = new char[maxSize];
	nullBuffer(buffer, maxSize);
	std::string retVal = buffer;	
	delete[] buffer;
	return retVal;
}

void Socket::nullBuffer(char * buffer, unsigned int size){
	for(unsigned int idx = 0; idx < size; idx++){
		buffer[idx] = 0;
	}
}

void Socket::sWrite(std::string message){
	int bytesWritten = write(fileDescriptor, message.c_str(), message.size());
	if(bytesWritten < 0){
		printf("Error on write\n");
		throw std::exception(); //TODO: Ex
	}
}