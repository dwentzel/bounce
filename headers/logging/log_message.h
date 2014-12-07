#ifndef BOUNCE_LOGGING_LOG_MESSAGE_H_
#define BOUNCE_LOGGING_LOG_MESSAGE_H_

#include "framework/lock_free_queue.h"

namespace bounce {

    typedef std::wstring LogMessage;
    typedef std::unique_ptr<LogMessage> LogMessagePtr;
    typedef LockFreeQueue<LogMessagePtr> LogMessageQueue;    
}

#endif // BOUNCE_LOGGING_LOG_MESSAGE_H_