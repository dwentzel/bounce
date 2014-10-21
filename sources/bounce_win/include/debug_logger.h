#ifndef BOUNCE_WIN_DEBUGLOGGER_H_
#define BOUNCE_WIN_DEBUGLOGGER_H_

#include <sstream>
#include "logging/logger.h"

namespace bounce_win {

    struct DebugStream : public std::ostringstream
    {
    public:
        //DebugStream() {}

        template<typename T>
        const DebugStream& operator<<(const T& v) const {
            OutputDebugString(v);
        }
    };

    class DebugLogger : public bounce::Logger {
    public:
        DebugLogger() {}

        std::ostream& Log(const bounce::LogLevel& log_level) {
            return stream;
        }

    private:
        DebugStream stream;
    };
}

#endif // BOUNCE_WIN_DEBUGLOGGER_H_