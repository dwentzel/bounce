#ifndef BOUNCE_LOGGING_LOG_STREAM_BUFFER_
#define BOUNCE_LOGGING_LOG_STREAM_BUFFER_

#include <vector>
#include <sstream>

#include "framework/lock_free_queue.h"

#include "log_message.h"

namespace bounce {
    
    class LogStreamBuffer : public std::wstringbuf {
    public:
        LogStreamBuffer(LockFreeQueue<LogMessagePtr>& message_queue);
        
        virtual int sync();
        
    private:
        LockFreeQueue<LogMessagePtr>& message_queue_;
        
    };

}

#endif // BOUNCE_LOGGING_LOG_STREAM_BUFFER_
