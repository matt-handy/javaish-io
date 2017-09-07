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

			~Socket();

			unsigned int sRead(char * buffer, unsigned int bufferSize);
			std::string readString();

			std::string readString(unsigned int maxSize);

			void sWrite(std::string message);
		private:
			int fileDescriptor;	
			std::string host;
			unsigned int port;	
			void nullBuffer(char * buffer, unsigned int size);	

			const static size_t BufferSize;
		};
	}
}

#endif