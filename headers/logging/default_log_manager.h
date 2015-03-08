#ifndef BOUNCE_LOGGING_DEFAULT_LOG_MANAGER_H_
#define BOUNCE_LOGGING_DEFAULT_LOG_MANAGER_H_

#include "log_manager.h"

namespace bounce {

    class DefaultLogManagerImpl;
    
    class DefaultLogManager : public bounce::LogManager {
    public:
        DefaultLogManager();
        ~DefaultLogManager();
        
        void Startup();
        void Shutdown();
        
        std::wostream& Log(const LogLevel& log_level);
        
        void AddOutput(std::unique_ptr<LogOutput> output);
    private:
        std::unique_ptr<DefaultLogManagerImpl> impl_;
        
    private:
        DefaultLogManager(const DefaultLogManager&) = delete;
        DefaultLogManager& operator=(const DefaultLogManager&) = delete;
    };

}

#endif // BOUNCE_LOGGING_DEFAULT_LOG_MANAGER_H_
