#ifndef DEBUGLOGGER_H_
#define DEGBULOGGER_H_

#include <sstream>
#include "logging/Logger.hpp"

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

        std::ostream& Log(const bounce::LogLevel& logLevel) {
            return stream;
        }

    private:
        DebugStream stream;
    };
}

#endif