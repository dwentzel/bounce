#include <iostream>
#include "stdout_log_output.h"

void bounce::StdoutLogOutput::Output(const std::wstring& message)
{
    std::wcout << message << "\n";
}
