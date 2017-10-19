/*
 * dp_peripherals.cpp
 *
 *  Created on: Mar 8, 2017
 *      Author: jeff
 */

#include <unistd.h>
#include <cerrno>
#include "dp_peripherals.h"

namespace DP
{

void Peripheral::WriteConfig(std::string resource, const std::string& arg)
{
	std::string commandStr = "dpset " + id + " " + resource;
    WriteCommand(commandStr, arg);
}

void Peripheral::WriteCommand(std::string command, std::string arg)
{
	std::string commandLine = command + " " + arg + "\n";
    unsigned wrsize = write(cmdfd, commandLine.c_str(), commandLine.length());
    if (wrsize != commandLine.length())
    {
    	throw FrameworkException("WriteCommand", ERR_WRITE);
    }
}

void Sensor::StartDataStream()
{
	std::string commandLine = "dpcat " + id + " " + dataRsc + "\n";
    unsigned wrsize = write(dataFd, commandLine.c_str(), commandLine.length());
    if (wrsize != commandLine.length())
    {
    	throw FrameworkException("StartDataStream", ERR_WRITE);
    }
}

// FIXME: need to resolve how to use this one fct for both command replies and data streams
void Sensor::ReadResponse(char* buffer, int bufsize)
{
    int bufptr;
    int retval;

    for (bufptr = 0; bufptr < bufsize; bufptr++)
    {
        retval = read(dataFd, &buffer[bufptr], 1);
        if (retval < 0)
        {
            if (retval != EAGAIN && retval != EINTR)
            {
            	throw FrameworkException("ReadResponse", ERR_READ);
            }
            else
                continue;
        }
        else if (retval == 0)
        {
        	throw FrameworkException("ReadResponse", ERR_READ);
        }
        if (buffer[bufptr] == '\n')
        {
        	// check if this newline is NOT part of a command response, <nl><\>
        	if ((bufptr < bufsize-1) && (buffer[bufptr+1] != '\\'))
			{
        		// terminate the data string
				buffer[bufptr] = 0;
				break;
			}
        }
        else if (buffer[bufptr] == '\\')
        {
            // terminate the command response string, <nl><\>
        	buffer[bufptr] = 0;
        	break;
        }
    }
    if (bufptr == bufsize)
    {
    	throw FrameworkException("ReadResponse", ERR_READ);
    }
}

} // namespace DP

