#include "debug_string_output.h"

#include <Windows.h>

void bounce_win::DebugStringOutput::Output(const bounce::LogMessage& message)
{
    OutputDebugString(message.c_str());
}