#ifndef BOUNCE_LOGGING_LOG_H_
#define BOUNCE_LOGGING_LOG_H_

#define LOG(log_level) \
if (true) ::bounce::LogSync(::bounce::LogFacade::Log(log_level))

#define LOG_ERROR LOG(::bounce::LOG_LEVEL_ERROR)
#define LOG_WARNING LOG(::bounce::LOG_LEVEL_WARNING)
#define LOG_INFO LOG(::bounce::LOG_LEVEL_INFO)
#define LOG_DEBUG LOG(::bounce::LOG_LEVEL_DEBUG)

#include <ostream>

namespace bounce {
        
    std::wostream& operator<<(std::wostream& out, const std::string& str);
    std::wostream& operator<<(std::wostream& out, const unsigned char* data);
    
}

#include "log_sync.h"
#include "log_facade.h"

#endif // BOUNCE_LOGGING_LOG_H_
