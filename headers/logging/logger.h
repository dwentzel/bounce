#ifndef BOUNCE_LOGGER_H_
#define BOUNCE_LOGGER_H_

#include <iostream>
#include <ostream>
#include <sstream>

namespace bounce {
    
    enum LogLevel {
        LOG_LEVEL_ERROR,
        LOG_LEVEL_WARNING,
        LOG_LEVEL_INFO,
        LOG_LEVEL_DEBUG
    };
    

    
    class Logger {
    private:
    protected:
        
    public:
        virtual ~Logger() = 0;
        
        //virtual LogStream& Log(const LogLevel& logLevel) = 0;
    };
    
    inline Logger::~Logger() {}
}


#endif // BOUNCE_LOGGER_H_
