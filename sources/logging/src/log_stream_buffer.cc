#include "log_stream_buffer.h"

int bounce::LogStreamBuffer::sync()
{
    std::wstring data = str();
    
    for (std::vector<std::unique_ptr<LogOutput>>::iterator i = outputs_.begin(); i != outputs_.end(); ++i) {
        (*i)->output(data);
    }
    
    str(L"");
    return 0;
}

void bounce::LogStreamBuffer::AddOutput(std::unique_ptr<LogOutput> output)
{
    outputs_.push_back(std::move(output));
}