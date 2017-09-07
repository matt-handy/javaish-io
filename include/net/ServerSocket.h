#ifndef JAVAISH_SERVERSOCKET_H
#define JAVAISH_SERVERSOCKET_H

#include <string>
#include "net/Socket.h"

namespace javaish
{
	namespace net
	{
	class ServerSocket
		{
		public:
			~ServerSocket();

			ServerSocket(unsigned short port, unsigned int soTimeout);

			Socket* acceptSocket();
		private:
			unsigned short port;
			unsigned int soTimeout;
			int socketFileDescriptor;	
		};
	}
}

#endif