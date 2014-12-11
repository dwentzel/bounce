#include "log_manager.h"

#include <thread>

#include "framework/lock_free_queue.h"

#include "log_stream_buffer.h"
#include "log_worker.h"

#include "file_log_output.h"

class bounce::LogManagerImpl {
private:
    LockFreeQueue<LogMessagePtr> message_queue_;

    LogWorkerContext log_worker_context_;
    LogWorker log_worker_;

    LogStreamBuffer buffer_;
    std::wostream log_stream_;
    LogLevel max_log_level_;

    std::unique_ptr<std::thread> worker_thread_;

public:
    LogManagerImpl();
    ~LogManagerImpl();

    void Startup();
    void Shutdown();

    LogLevel max_log_level() const;

    void max_log_level(LogLevel log_level);

    std::wostream& Log(const LogLevel&);

    void AddOutput(std::unique_ptr<LogOutput> output);
};

bounce::LogManagerImpl::LogManagerImpl()
    : log_worker_context_(message_queue_), buffer_(message_queue_), log_stream_(&buffer_), max_log_level_(LOG_LEVEL_DEBUG)
{

}

bounce::LogManagerImpl::~LogManagerImpl()
{
    Shutdown();
    //delete logger;
}

void bounce::LogManagerImpl::Startup()
{
    worker_thread_ = std::unique_ptr<std::thread>(new std::thread(&LogWorker::Run, &log_worker_, std::ref(log_worker_context_)));
}

void bounce::LogManagerImpl::Shutdown()
{
    log_worker_.Stop();
    worker_thread_->join();
}

bounce::LogLevel bounce::LogManagerImpl::max_log_level() const
{
    return max_log_level_;
}

void bounce::LogManagerImpl::max_log_level(LogLevel log_level)
{
    max_log_level_ = log_level;
}

std::wostream& bounce::LogManagerImpl::Log(const LogLevel&)
{
    return log_stream_;
}

void bounce::LogManagerImpl::AddOutput(std::unique_ptr<LogOutput> output)
{
    log_worker_context_.AddOutput(std::move(output));
}



bounce::LogManager::LogManager()
    : impl_(new LogManagerImpl())
{

}

bounce::LogManager::~LogManager()
{
    impl_->Shutdown();
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
