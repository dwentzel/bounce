#ifndef BOUNCE_LOGGING_LOGMANAGER_H_
#define BOUNCE_LOGGING_LOGMANAGER_H_

#include <memory>
#include <thread>
#include "log.h"
#include "log_stream_buffer.h"
#include "log_worker.h"
#include "framework/lock_free_queue.h"

namespace bounce {
    
    class LogManager {
    private:
        LogManager();
        LogManager(const LogManager&) = delete;
        ~LogManager();
        
        void operator=(const LogManager&);
        
        LogMessageQueue message_queue_;
        
        LogWorkerContext log_worker_context_;
        LogWorker log_worker_;
        
        LogStreamBuffer buffer_;
        std::wostream log_stream_;
        LogLevel max_log_level_;
        
        std::unique_ptr<std::thread> worker_thread_;
        
    public:
        static LogManager& instance();
        
        LogLevel max_log_level() const;
        void max_log_level(LogLevel log_level);
        
        std::wostream& Log(const LogLevel& log_level);
        
        void Startup();
        void Shutdown();
    };
    
    inline LogManager& LogManager::instance()
    {
        static LogManager instance;
        return instance;
    }
    
    inline LogLevel LogManager::max_log_level() const
    {
        return max_log_level_;
    }
    
    inline void LogManager::max_log_level(LogLevel log_level)
    {
        max_log_level_ = log_level;
    }
    
    inline std::wostream& LogManager::Log(const LogLevel& log_level)
    {
        return log_stream_;
    }
    
}
#endif // BOUNCE_LOGGING_LOGMANAGER_H_
