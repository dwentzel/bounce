#include "log_stream.h"


bounce::LogStream::LogStream(LogStreamBuffer& buffer) : buffer_(buffer), std::wostream(&buffer_)
{
}

void bounce::LogStream::AddOutput(std::unique_ptr<LogOutput> output)
{
    buffer_.AddOutput(std::move(output));
}


namespace bounce {
    
    std::wostream& operator<<(std::wostream& out, const std::string& str)
    {
        std::copy(str.begin(), str.end(), std::ostream_iterator<char, wchar_t>(out));
        return out;
    }
    
}