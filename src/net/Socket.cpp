#include "net/Socket.h"

using namespace std;
using namespace javaish::net;

Socket::Socket(){
	
}

Socket::Socket(std::string host, unsigned int port) : host(host), port(port) {

}

Socket::Socket(int fileDescriptor) : fileDescriptor(fileDescriptor){

}

unsigned int Socket::read(char* buffer, unsigned int bufferSize){
	return 0;
}

std::string Socket::readString(){
	std::string toFill;

	return toFill;
}

std::string Socket::readString(unsigned int maxSize){
	std::string toFill;

	return toFill;

}

