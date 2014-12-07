#include <thread>
#include "log_worker.h"

bounce::LogWorkerContext::LogWorkerContext(LogMessageQueue& message_queue) : message_queue_(message_queue)
{
    
}

void bounce::LogWorkerContext::AddOutput(std::unique_ptr<LogOutput> output)
{
    outputs_.push_back(std::move(output));
}

void bounce::LogWorkerContext::OutputMessage(const LogMessage& message)
{
    for (LogOutputList::iterator output = outputs_.begin(); output != outputs_.end(); ++output) {
        (*output)->Output(message);
    }
}

bounce::LogMessagePtr bounce::LogWorkerContext::PollMessage()
{
    LogMessagePtr message;
    
    if (message_queue_.consume(message)) {
        return message;
    }
    else {
        return nullptr;
    }
}

void bounce::LogWorkerContext::OutputMessages()
{
    LogMessagePtr message;
    
    while ((message = PollMessage()) != nullptr) {
        OutputMessage(*message);
    }
}

bounce::LogWorker::LogWorker()
{
    
}

void bounce::LogWorker::Run(LogWorkerContext& context)
{
    running_.store(1);
    
    while (running_ != 0) {
        context.OutputMessages();
        std::chrono::milliseconds d(1000);
        std::this_thread::sleep_for(d);
    }
}

void bounce::LogWorker::Stop()
{
    running_.store(false);
}