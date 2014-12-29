#ifndef BOUNCE_LOGGING_LOG_OUTPUT_
#define BOUNCE_LOGGING_LOG_OUTPUT_

#include "log_message.h"

namespace bounce {

    class LogOutput {
    private:
        LogOutput(const LogOutput&) = delete;
        LogOutput& operator=(const LogOutput&) = delete;
        
    protected:
        LogOutput();
        
    public:
        virtual ~LogOutput();
        
        virtual void Output(const LogMessage& message) = 0;
    };

}

#endif // BOUNCE_LOGGING_LOG_OUTPUT_
