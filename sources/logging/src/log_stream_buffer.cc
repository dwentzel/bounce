#include "log_stream_buffer.h"

bounce::LogStreamBuffer::LogStreamBuffer(LockFreeQueue<LogMessagePtr>& message_queue)
: message_queue_(message_queue)
{
}

int bounce::LogStreamBuffer::sync()
{
    std::wstring data = str();
    
    message_queue_.Produce(LogMessagePtr(new LogMessage(data)));
    
    str(L"");
    return 0;
}
