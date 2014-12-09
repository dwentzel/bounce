#include "log_message.h"

bounce::LogMessage::LogMessage(const std::wstring& message)
: message_(message)
{
    
}

bounce::LogMessage::~LogMessage()
{
    
}

namespace bounce {

std::wostream& operator<<(std::wostream& ostream, const bounce::LogMessage& message)
{
    ostream << message.message_;
    return ostream;
}

}