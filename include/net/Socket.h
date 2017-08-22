#ifndef JAVAISH_SOCKET_H
#define JAVAISH_SOCKET_H

#include <string>

namespace javaish
{
	namespace net
	{
	class Socket
		{
		public:
			//TODO: Break this into a parent class
			Socket(int fileDescriptor);

			Socket(std::string host, unsigned int port);

			unsigned int read(char * buffer, unsigned int bufferSize);
			std::string readString();

			std::string readString(unsigned int maxSize);
		private:
			int fileDescriptor;	
			std::string host;
			unsigned int port;		
		};
	}
}

#endif