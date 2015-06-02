#ifndef JAVAISH_CONFIGURATION_H
#define JAVAISH_CONFIGURATION_H

#include <stddef.h>
#include <map>
#include <string>

namespace javaish
{
	class Configuration
		{
		public:
			bool read(const char * location);
		
			std::string getValue(const char * subject);

		private:
			const static size_t MaximumLineLength;
			const static std::string Blank;
			const static std::string Dot;
			const static std::string Equals;
			const static std::string Comment;

			std::map<std::string, std::string> configCollection;
		
		};
}

#endif