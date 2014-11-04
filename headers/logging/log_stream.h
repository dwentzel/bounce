#ifndef BOUNCE_LOGGING_LOG_STREAM_
#define BOUNCE_LOGGING_LOG_STREAM_

#include <ostream>
#include "log_stream_buffer.h"
#include "log_output.h"

namespace bounce {

    class LogStream : public std::wostream {
    private:
        LogStreamBuffer& buffer_;
        
    public:
        LogStream(LogStreamBuffer& buffer);
        
//        void AddOutput(std::unique_ptr<LogOutput> output);
        
    };
    
    std::wostream& operator<<(std::wostream& out, const std::string& str);
}

#endif // BOUNCE_LOGGING_LOG_STREAM_
