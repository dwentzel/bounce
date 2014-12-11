#ifndef BOUNCE_LOGGING_FILE_LOG_OUTPUT_
#define BOUNCE_LOGGING_FILE_LOG_OUTPUT_

#include <fstream>
#include "log_output.h"


namespace bounce {

    class FileLogOutput : public LogOutput {
    private:
        std::wfstream file_;
        
    public:
        FileLogOutput();
        virtual ~FileLogOutput();
        
        virtual void Output(const LogMessage& message);
    };

}

#endif // BOUNCE_LOGGING_FILE_LOG_OUTPUT_
