#include "log_sync.h"

#include "framework/contracts.h"

bounce::LogSync::LogSync(std::wostream& output_stream) : output_stream_(output_stream)
{
    CONTRACT_REQUIRES(output_stream.good());
}

bounce::LogSync::~LogSync()
{
    output_stream_ << buffer_stream_.rdbuf() << std::flush;
}
