#ifndef BOUNCE_LOGGING_LOG_FACADE_H_
#define BOUNCE_LOGGING_LOG_FACADE_H_

#include "log_manager.h"

namespace bounce {

    class LogFacade {
    public:
        static void SetFactory(std::unique_ptr<LogManagerFactoryBase> factory);
        static void Startup();
        static void Shutdown();
        static void AddOutput(std::unique_ptr<LogOutput> output);
        
        static std::wostream& Log(const LogLevel& log_level);
        
    private:
        static std::unique_ptr<LogManagerFactoryBase> factory_;
        static std::unique_ptr<LogManager> log_manager_;
        
    private:
        LogFacade();
        ~LogFacade();
        
        LogFacade(const LogFacade&) = delete;
        LogFacade& operator=(const LogFacade&) = delete;
        
    };

}

#endif // BOUNCE_LOGGING_LOG_FACADE_H_
