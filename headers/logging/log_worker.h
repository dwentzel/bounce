#ifndef BOUNCE_LOGGING_LOG_WORKER_
#define BOUNCE_LOGGING_LOG_WORKER_

#include <memory>
#include <vector>
#include "log_output.h"
#include "log_message.h"

namespace bounce {
    
    class LogWorkerContext {
    private:
        typedef std::vector<std::unique_ptr<LogOutput>> LogOutputList;
        
        LogMessageQueue& message_queue_;
        LogOutputList outputs_;
        
        LogMessagePtr PollMessage();
        void OutputMessage(const LogMessage& message);
        
        LogWorkerContext& operator=(const LogWorkerContext&) = delete;

    public:
        LogWorkerContext(LogMessageQueue& message_queue);
        
        void AddOutput(std::unique_ptr<LogOutput> output);
        
        void OutputMessages();
    };
    
    class LogWorker {
    private:
        std::atomic<int> running_;
        
    public:
        LogWorker();
//        LogWorker(const LogWorker& source);
        
        void Run(LogWorkerContext& context);
        
        void Stop();
    };
}

#endif // BOUNCE_LOGGING_LOG_WORKER_
