#ifndef BOUNCE_LOGGING_LOG_MESSAGE_H_
#define BOUNCE_LOGGING_LOG_MESSAGE_H_

#include <string>
#include <ostream>

namespace bounce {
    
    class LogMessage {
    private:
        std::wstring message_;
        
        friend std::wostream& operator<<(std::wostream& ostream, const LogMessage& message);
    public:
        LogMessage(const std::wstring& message);
        ~LogMessage();
    };
    
    std::wostream& operator<<(std::wostream& ostream, const LogMessage& message);
    
    typedef std::unique_ptr<LogMessage> LogMessagePtr;
}

#endif // BOUNCE_LOGGING_LOG_MESSAGE_H_
