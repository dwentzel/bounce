#include <iostream>
#include "stdout_log_output.h"

void bounce::StdoutLogOutput::output(const std::wstring& message)
{
    std::wcout << message;
}