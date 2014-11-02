#ifndef BOUNCE_WIN_DEBUGLOGGER_H_
#define BOUNCE_WIN_DEBUGLOGGER_H_

#include <ostream>
#include <sstream>
#include "logging/logger.h"

namespace bounce_win {

    class DebugStream : public std::wostream
    {
    private:
        class DebugStreamBuffer : public std::wstringbuf
        {
        private:
            //std:stringstream 
        public:
            virtual int sync()
            {
                OutputDebugString(str().c_str());
                return 0;
            }
        };


        DebugStreamBuffer buffer;

    public:
        DebugStream() : std::wostream(&buffer) {}

    };

    class DebugLogger : public bounce::Logger 
    {
    private:
        DebugStream stream;

    public:
        DebugLogger() {}

        std::wostream& Log(const bounce::LogLevel& log_level) {
                return stream;
        }
    };
}

#endif // BOUNCE_WIN_DEBUGLOGGER_H_