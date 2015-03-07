#ifndef BOUNCE_LOGGING_LOGMANAGER_H_
#define BOUNCE_LOGGING_LOGMANAGER_H_

#include "log.h"
#include "log_output.h"
#include <memory>

namespace bounce {

    class LogManagerImpl {
    public:
        virtual ~LogManagerImpl();
        
        virtual void Startup() = 0;
        virtual void Shutdown() = 0;
        
        virtual LogLevel max_log_level() const = 0;
        
        virtual void max_log_level(LogLevel log_level) = 0;
        
        virtual std::wostream& Log(const LogLevel&) = 0;
        
        virtual void AddOutput(std::unique_ptr<LogOutput> output) = 0;
    };
    
    class NullLogManagerImpl : public LogManagerImpl {
    public:
        virtual ~NullLogManagerImpl();
        
        virtual void Startup();
        virtual void Shutdown();
        
        virtual LogLevel max_log_level() const;
        
        virtual void max_log_level(LogLevel log_level);
        
        virtual std::wostream& Log(const LogLevel&);
        
        virtual void AddOutput(std::unique_ptr<LogOutput> output);
    };
    
    class LogManagerImplementationFactoryBase {
    public:
        virtual ~LogManagerImplementationFactoryBase();
        
        virtual std::unique_ptr<LogManagerImpl> Create() = 0;
    };
    
    template <class T>
    class LogManagerImplementationFactory : public LogManagerImplementationFactoryBase {
    public:
        std::unique_ptr<LogManagerImpl> Create();
    };
    
    template <class T>
    std::unique_ptr<LogManagerImpl> LogManagerImplementationFactory<T>::Create() {
        return std::unique_ptr<LogManagerImpl>{new T()};
    }
    
    class LogManager {
    public:
        static void SetFactory(std::unique_ptr<LogManagerImplementationFactoryBase> factory);
        static LogManager& instance();
        
        LogLevel max_log_level() const;
        void max_log_level(LogLevel log_level);
        
        std::wostream& Log(const LogLevel& log_level);
        
        void Startup();
        void Shutdown();

        void AddOutput(std::unique_ptr<LogOutput> output);
        
    private:
        static std::unique_ptr<LogManagerImplementationFactoryBase> factory_;
        
        LogManager();
        ~LogManager();
        
        LogManager(const LogManager&) = delete;
        LogManager& operator=(const LogManager&) = delete;
        
        std::unique_ptr<LogManagerImpl> impl_;
    };
    

    
}
#endif // BOUNCE_LOGGING_LOGMANAGER_H_
