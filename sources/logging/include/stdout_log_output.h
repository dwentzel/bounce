#ifndef BOUNCE_LOGGING_STDOUT_LOG_OUTPUT_
#define BOUNCE_LOGGING_STDOUT_LOG_OUTPUT_

#include "log_output.h"

namespace bounce {

    class StdoutLogOutput : public LogOutput {
    public:        
        virtual void Output(const LogMessage& message);
    };

}

#endif // BOUNCE_LOGGING_STDOUT_LOG_OUTPUT_
