#include "file_log_output.h"

#include <locale>
#include <fstream>

bounce::FileLogOutput::FileLogOutput()
{
    file_.open("logfile.log", std::fstream::out | std::fstream::app);
//    file_.imbue(std::locale(file_.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
}

bounce::FileLogOutput::~FileLogOutput()
{
    file_.close();
}

void bounce::FileLogOutput::Output(const LogMessage& message)
{
    file_ << message;
}
