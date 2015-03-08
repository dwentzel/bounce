#include "default_log_manager.h"

#include "framework/contracts.h"
#include "framework/lock_free_queue.h"

#include "log_stream_buffer.h"
#include "log_worker.h"

#include "file_log_output.h"
#include <thread>
#include <iostream>

namespace bounce {
    class DefaultLogManagerImpl {
    public:
        DefaultLogManagerImpl();
        ~DefaultLogManagerImpl();
        
        void Startup();
        void Shutdown();
        
        std::wostream& Log(const LogLevel&);
        
        void AddOutput(std::unique_ptr<LogOutput> output);
    private:
        LockFreeQueue<LogMessagePtr> message_queue_;
        
        LogWorkerContext log_worker_context_;
        LogWorker log_worker_;
        
        LogStreamBuffer buffer_;
        std::wostream log_stream_;
        
        std::unique_ptr<std::thread> worker_thread_;
    private:
        DefaultLogManagerImpl(const DefaultLogManagerImpl&) = delete;
        DefaultLogManagerImpl& operator=(const DefaultLogManagerImpl&) = delete;
    };
    
}

bounce::DefaultLogManagerImpl::DefaultLogManagerImpl()
: log_worker_context_(message_queue_), buffer_(message_queue_), log_stream_(&buffer_)
{
    CONTRACT_ENSURES(log_stream_.good());
    log_stream_.exceptions(log_stream_.exceptions() | std::ios_base::failbit);
}

bounce::DefaultLogManagerImpl::~DefaultLogManagerImpl()
{
    Shutdown();
}

void bounce::DefaultLogManagerImpl::Startup()
{
    CONTRACT_ENSURES(worker_thread_ != nullptr);
    worker_thread_ = std::unique_ptr<std::thread>(new std::thread(&LogWorker::Run, &log_worker_, std::ref(log_worker_context_)));
}

void bounce::DefaultLogManagerImpl::Shutdown()
{
    log_worker_.Stop();
    if (worker_thread_ != nullptr) {
        worker_thread_->join();
        worker_thread_ = nullptr;
    }
}

std::wostream& bounce::DefaultLogManagerImpl::Log(const LogLevel&)
{
    return log_stream_;
}

void bounce::DefaultLogManagerImpl::AddOutput(std::unique_ptr<LogOutput> output)
{
    log_worker_context_.AddOutput(std::move(output));
}

bounce::DefaultLogManager::DefaultLogManager()
{
    CONTRACT_ENSURES(impl_ != nullptr);
    
    impl_ = std::unique_ptr<DefaultLogManagerImpl>(new DefaultLogManagerImpl());
}

bounce::DefaultLogManager::~DefaultLogManager()
{
}

void bounce::DefaultLogManager::Startup()
{
    impl_->Startup();
}

void bounce::DefaultLogManager::Shutdown()
{
    impl_->Shutdown();
}

std::wostream& bounce::DefaultLogManager::Log(const LogLevel& log_level)
{
    return impl_->Log(log_level);
}

void bounce::DefaultLogManager::AddOutput(std::unique_ptr<LogOutput> output)
{
    CONTRACT_REQUIRES(output != nullptr);
    impl_->AddOutput(std::move(output));
}
