#include "log_stream_buffer.h"

bounce::LogStreamBuffer::LogStreamBuffer(LogMessageQueue& message_queue)
: message_queue_(message_queue)
{
}

int bounce::LogStreamBuffer::sync()
{
    std::wstring data = str();
    
    message_queue_.produce(LogMessagePtr(new std::wstring(data)));
    
    str(L"");
    return 0;
}
