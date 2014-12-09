#ifndef BOUNCE_LOGGING_STDOUT_LOG_OUTPUT_
#define BOUNCE_LOGGING_STDOUT_LOG_OUTPUT_

#include "logging/log_output.h"

namespace bounce_mac {

    class ConsoleLogOutput : public bounce::LogOutput {
    public:        
        virtual void Output(const bounce::LogMessage& message);
    };

}

#endif // BOUNCE_LOGGING_STDOUT_LOG_OUTPUT_
