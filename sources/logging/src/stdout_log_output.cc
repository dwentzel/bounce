#include <iostream>

#include <io.h>
#include <fcntl.h>

#include "stdout_log_output.h"

void bounce::StdoutLogOutput::Output(const std::wstring&)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	//std::wcout << message;
    //std::wcout << message << "\n";
}
