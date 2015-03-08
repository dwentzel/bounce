#ifndef BOUNCE_LOGGING_LOGMANAGER_H_
#define BOUNCE_LOGGING_LOGMANAGER_H_

#include "log_level.h"
#include "log_output.h"
#include <memory>

namespace bounce {
    
    class LogManager {
    public:
        virtual ~LogManager();
        
        virtual void Startup() = 0;
        virtual void Shutdown() = 0;
        
        virtual std::wostream& Log(const LogLevel&) = 0;
        
        virtual void AddOutput(std::unique_ptr<LogOutput> output) = 0;
    };
        
    class LogManagerFactoryBase {
    public:
        LogManagerFactoryBase();
        virtual ~LogManagerFactoryBase();
        
        virtual std::unique_ptr<LogManager> Create() = 0;
    private:
        LogManagerFactoryBase(const LogManagerFactoryBase&) = delete;
        LogManagerFactoryBase& operator=(const LogManagerFactoryBase&) = delete;
    };
    
    template <class T>
    class LogManagerFactory : public LogManagerFactoryBase {
    public:
        LogManagerFactory();
        std::unique_ptr<LogManager> Create();
    };
    
    template <class T>
    LogManagerFactory<T>::LogManagerFactory()
    : LogManagerFactoryBase()
    {
    }
    
    template <class T>
    std::unique_ptr<LogManager> LogManagerFactory<T>::Create()
    {
        return std::unique_ptr<LogManager>{new T()};
    }
}
#endif // BOUNCE_LOGGING_LOGMANAGER_H_
