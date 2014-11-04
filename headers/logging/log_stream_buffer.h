#ifndef BOUNCE_LOGGING_LOG_STREAM_BUFFER_
#define BOUNCE_LOGGING_LOG_STREAM_BUFFER_

#include <vector>
#include <sstream>
#include "log_message.h"
#include "log_output.h"

namespace bounce {
    
    class LogStreamBuffer : public std::wstringbuf {
    private:
        LogMessageQueue& message_queue_;
        
        std::vector<std::unique_ptr<LogOutput>> outputs_;
        
    public:
        LogStreamBuffer(LogMessageQueue& message_queue);
        
        virtual int sync();
        
        //void AddOutput(std::unique_ptr<LogOutput> output);
    };

}

#endif // BOUNCE_LOGGING_LOG_STREAM_BUFFER_
