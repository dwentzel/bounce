#ifndef BOUNCE_LOGGING_LOGMANAGER_H_
#define BOUNCE_LOGGING_LOGMANAGER_H_

#include <memory>
#include "log.h"

#include "bounce_engine_export.h"

namespace bounce {

    class LogManagerImpl;
    
    class bounce_engine_EXPORT LogManager {
    private:
        LogManager();
        ~LogManager();

        LogManager(const LogManager&) = delete;
        LogManager& operator=(const LogManager&) = delete;
        
        LogManagerImpl* impl_;


        
    public:
        static LogManager& instance();
        
        LogLevel max_log_level() const;
        void max_log_level(LogLevel log_level);
        
        std::wostream& Log(const LogLevel& log_level);
        
        void Startup();
        void Shutdown();
    };
    

    
}
#endif // BOUNCE_LOGGING_LOGMANAGER_H_
