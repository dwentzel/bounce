#include "log_manager.h"

#include "stdout_log_output.h"
#include "file_log_output.h"

bounce::LogManager::LogManager()
: log_worker_context_(message_queue_), buffer_(message_queue_), log_stream_(&buffer_), max_log_level_(LOG_LEVEL_DEBUG)
{
    //buffer_.AddOutput(std::unique_ptr<LogOutput>(new StdoutLogOutput()));
    log_worker_context_.AddOutput(std::unique_ptr<LogOutput>(new StdoutLogOutput()));
    log_worker_context_.AddOutput(std::unique_ptr<LogOutput>(new FileLogOutput()));
}

bounce::LogManager::~LogManager()
{
    log_worker_.Stop();
    worker_thread_->join();
    //delete logger;
}

void bounce::LogManager::Startup()
{
    worker_thread_ = std::unique_ptr<std::thread>(new std::thread(&LogWorker::Run, &log_worker_, std::ref(log_worker_context_)));
}

void bounce::LogManager::Shutdown()
{
    log_worker_.Stop();
    worker_thread_->join();
}
