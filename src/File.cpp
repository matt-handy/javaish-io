#include <sstream>
#include <File.h>

using namespace std;
using namespace javaish;

File::File(string filenameInput, int flagsInput, int modeInput) :
  filename(filenameInput),
  flags(flagsInput),
  mode(modeInput)
{
	this->open(this->filename, this->flags, this->mode);
}

File::File() :
  handle(-1),
  filename(""),
  flags(0),
  mode(0)
{
}

File::~File()
{
  	this->close();
}

string File::toString()
{
  	stringstream buffer;

  	buffer << File::getName() << "::handle: " << this->handle << endl;
  	buffer << File::getName() << "::filename: " << this->filename << endl;
  	buffer << File::getName() << "::flags: " << this->flags << endl;
  	buffer << File::getName() << "::mode: " << this->mode << endl;
  
  	return buffer.str();
}

int File::readline(unsigned char* data, int bytesToRead, unsigned char delimiter, bool keepDelimiter)
{
  	int bytesRead = 0;
  	int totalBytesRead = 0;
  	bool gotDelimiter = false;
  	unsigned char singleCharacter = 0x00;
  	while ((totalBytesRead < bytesToRead) && (gotDelimiter == false))
  	{
    		bytesRead = this->read(&singleCharacter, 1);
    		if (bytesRead > 0)
    		{
      		if (singleCharacter != delimiter)
      		{
        			data[totalBytesRead] = singleCharacter;
        			totalBytesRead = totalBytesRead + 						bytesRead;
      		}
      		else
      		{
        			gotDelimiter = true;
        
        			if (keepDelimiter == true)
        			{
          				data[totalBytesRead] = 								singleCharacter;
          				totalBytesRead = totalBytesRead + bytesRead;
        			}
      		}
    		}
    
    		if ((bytesRead <= 0) && (totalBytesRead < bytesToRead))
    		{
      		break;
    		}
  	}
  
  	return totalBytesRead;
}
