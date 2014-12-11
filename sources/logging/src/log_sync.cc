#include "log_sync.h"

bounce::LogSync::LogSync(std::wostream& output_stream) : output_stream_(output_stream)
{
    
}

bounce::LogSync::~LogSync()
{
    output_stream_ << buffer_stream_.rdbuf() << std::flush;
}
