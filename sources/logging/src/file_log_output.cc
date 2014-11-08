#include "file_log_output.h"

bounce::FileLogOutput::FileLogOutput()
{
    file_.open("logfile.log", std::fstream::out | std::fstream::app);
}

bounce::FileLogOutput::~FileLogOutput()
{
    file_.close();
}

void bounce::FileLogOutput::Output(const LogMessage& message)
{
    file_ << message;
}