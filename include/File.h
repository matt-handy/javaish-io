#ifndef JAVAISH_FILE_H
#define JAVAISH_FILE_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace javaish
{
	class File
	{
	public:
  
    		File(std::string filenameInput, int flagsInput, int modeInput);
  
  		File();
  
	     //brief Closes file if not already closed.
  		virtual ~File();
  
    		inline std::string getName()
  		{
    			return "File";
  		}
  
  		std::string toString();
  
  
  		inline bool isOpen()
  		{
    			return (this->handle != -1);
  		}
  
    		inline std::string getFilename()
  		{
    			return this->filename;
  		}
  
    		inline void setFilename(std::string filenameInput)
  		{
    			this->filename = filenameInput;
  		}
  
    		inline int getFlags()
  		{
    			return this->flags;
  		}
  
  		inline void setFlags(int flagsInput)
  		{
    			this->flags = flagsInput;
  		}
  
  		inline int getMode()
  		{
    			return this->mode;
  		}
  
    		inline void setMode(int modeInput)
  		{
    			this->mode = modeInput;
  		}

    		inline bool open(int fileHandleInput, std::string filenameInput, int flagsInput, int modeInput)
  		{
    			this->handle = fileHandleInput;
    			this->filename = filenameInput;
    			this->flags = flagsInput;
    			this->mode = modeInput;
    
    			return this->isOpen();
  		}
  
    		inline bool open(std::string filenameInput, int flagsInput, int modeInput)
  		{
    			this->filename = filenameInput;
    			this->flags = flagsInput;
    			this->mode = modeInput;
    
    			return this->open();
  		}
  
    		inline bool open()
  		{
    			bool returnValue = false;
    
    			if (this->handle == -1)
    			{
      			this->handle = ::open(this->filename.c_str(), this->flags, this->mode);
      			if (this->handle != -1)
      			{
        				returnValue = true;
      			}
    			}
    
    			return returnValue;
  		}
  
    		inline bool changeUserAndGroup(unsigned int userIdInput, unsigned int groupIdInput)
  		{
    			bool returnValue = false;
    
    			if (this->handle == -1)
    			{
      			if (::fchown(this->handle, userIdInput, groupIdInput) != -1)
      			{
        				returnValue = true;
      			}
    			}
    
    			return returnValue;
  		}
  
    		inline bool changeMode(int flagsInput)
  		{
    			bool returnValue = false;
    
    			if (this->handle == -1)
    			{
      			if (::fchmod(this->handle, flagsInput) != -1)
      			{
        				returnValue = true;
      			}
    			}
    
    			return returnValue;
  		}
  
    		inline int seek(int offset, int whence)
  		{
    			return ::lseek(this->handle, offset, whence);
  		}
  
    		inline bool close()
  		{
    			bool returnValue = false;
    
    			if (this->handle != -1)
    			{
      			int closeOk = ::close(this->handle);
      			if (closeOk != -1)
      			{
        				this->handle = -1;
        				returnValue = true;
      			}
    			}
    
    			this->filename = "";
    			this->flags = 0;
    			this->mode = 0;
    
    			return returnValue;
  		}
  
    		int readline(unsigned char* data, int bytesToRead, unsigned char delimiter = '\n',bool keepDelimiter = false);
  
    		inline static bool changeUserAndGroup(std::string filenameInput, unsigned int userIdInput, unsigned int groupIdInput)
  		{
    			bool returnValue = false;
    
    			if (::chown(filenameInput.c_str(), userIdInput, groupIdInput) != -1)
    			{
      			returnValue = true;
    			}
    
    			return returnValue;
  		}
  
    		inline static bool changeMode(std::string filenameInput,int flagsInput)
  		{
    			bool returnValue = false;
    
    			if (::chmod(filenameInput.c_str(), flagsInput) != -1)
    			{
      			returnValue = true;
    			}
    
    			return returnValue;
  		}
  

    		inline int getHandle()
  		{
    			return this->handle;
  		}
  
    		bool isClosed()
  		{
    			bool returnValue = false;
    
    			if (this->handle == -1)
    			{
      			returnValue = true;
    			}
    
    			return returnValue;
  		}
  
    		inline int write(unsigned char* data, int bytesToWrite)
  		{
    			return ::write(this->handle, data, bytesToWrite);
  		}  
  
    		inline int read(unsigned char* data,int bytesToRead)
  		{
    			return ::read(this->handle, data, bytesToRead);
  		}
  
  
	protected:
  
  		int handle;

  		/// file to do reading/writing on.
  		std::string filename;
  
  		/// open flags (same as system flags).
  		int flags;
  
  		/// open mode (same as system mode).
  		int mode;
  
	};
};

#endif
