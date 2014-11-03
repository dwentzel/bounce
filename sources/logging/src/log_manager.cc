#include "log_manager.h"

#include "stdout_log_output.h"

bounce::LogManager::LogManager() : max_log_level_(LOG_LEVEL_DEBUG)
{
    log_stream_.AddOutput(std::unique_ptr<LogOutput>(new StdoutLogOutput()));
}



bounce::LogManager::~LogManager() {
    //delete logger;
}
