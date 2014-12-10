#include "log_message.h"

bounce::LogMessage::LogMessage(const std::wstring& message)
: message_(message)
{
    
}

bounce::LogMessage::~LogMessage()
{
    
}

const wchar_t* bounce::LogMessage::c_str() const
{
    return message_.c_str();
}

namespace bounce {

std::wostream& operator<<(std::wostream& ostream, const bounce::LogMessage& message)
{
    ostream << message.message_;
    return ostream;
}

}