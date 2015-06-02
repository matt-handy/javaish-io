#include <Configuration.h>
#include <File.h>
#include <iostream>
#include <cstring>

using namespace std;
using namespace javaish;

const size_t Configuration::MaximumLineLength = 5000;
const string Configuration::Blank = " ";
const string Configuration::Dot = ".";
const string Configuration::Equals = "=";
const string Configuration::Comment = "#";



std::string Configuration::getValue(const char * key)
{
	return configCollection[key];
}

bool Configuration::read(const char * location)
{
	bool returnValue = false;
  
	configCollection.clear();
  
	char contentsChar[Configuration::MaximumLineLength + 1];
	string contents = "";
	string key = "";
	string value = "";
	bool done = false;
	int bytesRead = 0;
  
	File file;
	file.open(location, O_RDONLY, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP);
	if (file.isOpen() == true)
	{
		done = false;
		while (done == false)
		{
			::memset(contentsChar, 0x00, sizeof(contentsChar));
			bytesRead = file.readline((unsigned char*)contentsChar, Configuration::MaximumLineLength);
			if ((bytesRead != 0) && (bytesRead != -1))
			{
				contents = contentsChar;
        
				// get rid of comments
				string::size_type position = contents.find(Configuration::Comment, 0);
				if (position != string::npos)
				{
					contents = contents.substr(0, position);
				}
        
				position = contents.find(Configuration::Equals, 0);
				if (position != string::npos)
				{
					key = contents.substr(0, position);
					value = contents.substr(position + 1);
          
					// remove leading white space
					string::size_type firstNonBlankPosition = key.find_first_not_of(Configuration::Blank);
					if (firstNonBlankPosition != string::npos)
					{
						key = key.substr(firstNonBlankPosition);
					}
					else
					{
						/// no nonblank characters found in key
						continue;
					}
          
					// remove trailing white space
					firstNonBlankPosition = key.find_last_not_of(Configuration::Blank);
					if (firstNonBlankPosition != string::npos)
					{
						key = key.substr(0, firstNonBlankPosition + 1);
					}
					else
					{
						/// no nonblank characters found in key
						continue;
					}
          
					// remove leading white space
					firstNonBlankPosition = value.find_first_not_of(Configuration::Blank);
					if (firstNonBlankPosition != string::npos)
					{
						value = value.substr(firstNonBlankPosition);
					}
					else
					{
						/// no nonblank characters found in value
					}
          
					// remove trailing white space
					firstNonBlankPosition = value.find_last_not_of(Configuration::Blank);
					if (firstNonBlankPosition != string::npos)
					{
						value = value.substr(0, firstNonBlankPosition + 1);
					}
					else
					{
						/// no nonblank characters found in value
					}
          
					configCollection[key] = value;
				}
				else
				{
					/// no equals character found in key
					continue;
				}
			}
			else if (bytesRead == 0)
			{
				/// at end of file
				done = true;
				returnValue = true;
			}
			else
			{
				/// error reading from file.
				done = true;
				returnValue = false;
			}
		}
    
		if (file.close() == false)
		{
			/// error closing file
		}
	}
	else
	{
		returnValue = false;
	}
  
	return returnValue;
}


