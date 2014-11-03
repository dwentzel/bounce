#ifndef BOUNCE_LOGGING_LOG_OUTPUT_
#define BOUNCE_LOGGING_LOG_OUTPUT_

#include <string>

namespace bounce {

    class LogOutput {
    public:
        virtual ~LogOutput() = 0;
        virtual void output(const std::wstring& message) = 0;
    };

}

#endif // BOUNCE_LOGGING_LOG_OUTPUT_
