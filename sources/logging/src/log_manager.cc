#include "log_manager.h"

#include "framework/contracts.h"
#include "framework/lock_free_queue.h"

#include "log_stream_buffer.h"
#include "log_worker.h"

#include "file_log_output.h"
#include <thread>
#include <iostream>

namespace bounce {
    class DefaultLogManagerImpl : public bounce::LogManagerImpl {
    private:
        LockFreeQueue<LogMessagePtr> message_queue_;
        
        LogWorkerContext log_worker_context_;
        LogWorker log_worker_;
        
        LogStreamBuffer buffer_;
        std::wostream log_stream_;
        LogLevel max_log_level_;
        
        std::unique_ptr<std::thread> worker_thread_;
        
    public:
        DefaultLogManagerImpl();
        ~DefaultLogManagerImpl();
        
        void Startup();
        void Shutdown();
        
        LogLevel max_log_level() const;
        
        void max_log_level(LogLevel log_level);
        
        std::wostream& Log(const LogLevel&);
        
        void AddOutput(std::unique_ptr<LogOutput> output);
    };
    
}

bounce::DefaultLogManagerImpl::DefaultLogManagerImpl()
: log_worker_context_(message_queue_), buffer_(message_queue_), log_stream_(&buffer_), max_log_level_(LOG_LEVEL_DEBUG)
{
    
}

bounce::DefaultLogManagerImpl::~DefaultLogManagerImpl()
{
    Shutdown();
    //delete logger;
}

void bounce::DefaultLogManagerImpl::Startup()
{
    CONTRACT_ENSURES(worker_thread_ != nullptr);
    worker_thread_ = std::unique_ptr<std::thread>(new std::thread(&LogWorker::Run, &log_worker_, std::ref(log_worker_context_)));
}

void bounce::DefaultLogManagerImpl::Shutdown()
{
    log_worker_.Stop();
    worker_thread_->join();
}

bounce::LogLevel bounce::DefaultLogManagerImpl::max_log_level() const
{
    return max_log_level_;
}

void bounce::DefaultLogManagerImpl::max_log_level(LogLevel log_level)
{
    max_log_level_ = log_level;
}

std::wostream& bounce::DefaultLogManagerImpl::Log(const LogLevel&)
{
    return log_stream_;
}

void bounce::DefaultLogManagerImpl::AddOutput(std::unique_ptr<LogOutput> output)
{
    log_worker_context_.AddOutput(std::move(output));
}

bounce::LogManagerImpl::~LogManagerImpl()
{
    
}


bounce::NullLogManagerImpl::~NullLogManagerImpl()
{
    
}

void bounce::NullLogManagerImpl::Startup()
{
    
}

void bounce::NullLogManagerImpl::Shutdown()
{
    
}

bounce::LogLevel bounce::NullLogManagerImpl::max_log_level() const
{
    return LogLevel::LOG_LEVEL_DEBUG;
}

void bounce::NullLogManagerImpl::max_log_level(LogLevel log_level)
{
    
}

std::wostream& bounce::NullLogManagerImpl::Log(const LogLevel&)
{
    return std::wcout;
}

void bounce::NullLogManagerImpl::AddOutput(std::unique_ptr<LogOutput> output)
{
    
}



bounce::LogManagerImplementationFactoryBase::~LogManagerImplementationFactoryBase()
{
    
}




std::unique_ptr<bounce::LogManagerImplementationFactoryBase> bounce::LogManager::factory_;

bounce::LogManager::LogManager()
{
    if (!factory_) {
        factory_ = std::unique_ptr<LogManagerImplementationFactoryBase>(new LogManagerImplementationFactory<DefaultLogManagerImpl>());
    }
    
    impl_ = factory_->Create();
}

bounce::LogManager::~LogManager()
{
    impl_->Shutdown();
}

void bounce::LogManager::SetFactory(std::unique_ptr<LogManagerImplementationFactoryBase> factory)
{
    factory_ = std::move(factory);
}

void bounce::LogManager::Startup()
{
    impl_->Startup();
}

void bounce::LogManager::Shutdown()
{
    impl_->Shutdown();
}

bounce::LogManager& bounce::LogManager::instance()
{
    static LogManager instance;
    return instance;
}

bounce::LogLevel bounce::LogManager::max_log_level() const
{
    return impl_->max_log_level();
}

void bounce::LogManager::max_log_level(LogLevel log_level)
{
    impl_->max_log_level(log_level);
}

std::wostream& bounce::LogManager::Log(const LogLevel& log_level)
{
    return impl_->Log(log_level);
}

void bounce::LogManager::AddOutput(std::unique_ptr<LogOutput> output)
{
    impl_->AddOutput(std::move(output));
}
