#ifndef BOUNCE_LOGGING_DEFAULT_LOGGER_H_
#define BOUNCE_LOGGING_DEFAULT_LOGGER_H_

#include <iostream>

namespace bounce {
    
    class DefaultLogger : public Logger
    {
    private:
        LogStream log_stream;
        
    public:
        ~DefaultLogger()
        {
//            std::wcout << "Default logger destroyed." << std::endl;
        }
        
        LogStream& Log(const LogLevel& logLevel)
        {
            return log_stream;
        }
    };
    
}


#endif // BOUNCE_LOGGING_DEFAULT_LOGGER_H_
