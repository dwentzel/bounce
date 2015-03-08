#ifndef BOUNCE_LOGGING_NULL_LOG_MANAGER_H_
#define BOUNCE_LOGGING_NULL_LOG_MANAGER_H_

#include "log_manager.h"

namespace bounce {

    class NullLogManager : public LogManager {
    public:
        virtual ~NullLogManager();
        
        virtual void Startup();
        virtual void Shutdown();
        
        virtual std::wostream& Log(const LogLevel&);
        
        virtual void AddOutput(std::unique_ptr<LogOutput> output);
    };

}

#endif // BOUNCE_LOGGING_NULL_LOG_MANAGER_H_
