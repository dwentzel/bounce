#include <iostream>

//#include <io.h>
//#include <fcntl.h>

#include "console_log_output.h"

void bounce_mac::ConsoleLogOutput::Output(const bounce::LogMessage& message)
{
//	_setmode(_fileno(stdout), _O_U16TEXT);
	std::wcout << message;
    //std::wcout << message << "\n";
}
