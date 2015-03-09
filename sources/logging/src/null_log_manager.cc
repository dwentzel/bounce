#include "null_log_manager.h"

#include <iostream>

bounce::NullLogManager::~NullLogManager()
{
}

void bounce::NullLogManager::Startup()
{
}

void bounce::NullLogManager::Shutdown()
{
}

std::wostream& bounce::NullLogManager::Log(const LogLevel&)
{
    return std::wcout;
}

void bounce::NullLogManager::AddOutput(std::unique_ptr<LogOutput>)
{
}
