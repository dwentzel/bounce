#ifndef BOUNCE_BOUNCE_WIN_DEBUG_STRING_OUTPUT_H_
#define BOUNCE_BOUNCE_WIN_DEBUG_STRING_OUTPUT_H_

#include "logging/log_output.h"

namespace bounce_win {

    class DebugStringOutput : public bounce::LogOutput {
    private:

    public:
        virtual void Output(const bounce::LogMessage& message);
    };

}


#endif // #ifndef BOUNCE_BOUNCE_WIN_DEBUG_STRING_OUTPUT_H_