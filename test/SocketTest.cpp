#include <net/ServerSocket.h>
#include <net/Socket.h>
#include "gtest/gtest.h"

#include <iostream>
#include <thread>
#include <unistd.h>

using namespace javaish;
using namespace javaish::net;

void serverDriver() 
{
	ServerSocket sSocket(9000, 10);
	Socket *incoming = sSocket.acceptSocket();
	EXPECT_TRUE(incoming);
	char buffer[1024];
	for(int idx = 0; idx < 1024; idx++){
		buffer[idx] = 0;
	}
	unsigned int size = incoming->sRead(buffer, 1024);
	EXPECT_TRUE(size == 14);
	incoming->sWrite("This is also a test");

	delete incoming;
}

void serverDriver2() 
{
	ServerSocket sSocket(9001, 10);
	Socket *incoming = sSocket.acceptSocket();
	EXPECT_TRUE(incoming);
	char buffer[1024];
	for(int idx = 0; idx < 1024; idx++){
		buffer[idx] = 0;
	}
	unsigned int size = incoming->sRead(buffer, 1024);
	EXPECT_TRUE(size == 14);
	incoming->sWrite("This is also a test");

	delete incoming;
}

TEST(SocketTest, BasicReadTest){
	std::thread driver (serverDriver);
	usleep(10000);
	Socket testClient("127.0.0.1", 9000);
	testClient.sWrite("This is a test");

	char buffer[1024];
	for(int idx = 0; idx < 1024; idx++){
		buffer[idx] = 0;
	}

	unsigned int size = testClient.sRead(buffer, 1024);
	EXPECT_TRUE(size == 19);

	driver.join();
}

TEST(SocketTest, StringReadTest){
	std::thread driver (serverDriver2);
	usleep(10000);
	Socket testClient("127.0.0.1", 9001);
	testClient.sWrite("This is a test");

	std::string readString = testClient.readString();
	EXPECT_STREQ(readString.c_str(), "This is also a test");

	driver.join();
}

