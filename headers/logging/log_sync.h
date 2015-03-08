#ifndef BOUNCE_LOGGING_LOG_SYNC_
#define BOUNCE_LOGGING_LOG_SYNC_

#include <ostream>
#include <sstream>

namespace bounce {


    class LogSync {
    public:
        explicit LogSync(std::wostream& output_stream);
        ~LogSync();
        
        template<typename T>
        LogSync& operator<<(const T& t);
        
        std::wostream& operator<<(std::wostream& (*manip)(std::wostream&))
        {
            manip(buffer_stream_);
            return buffer_stream_;
        }
        
    private:
        std::wostream& output_stream_;
        std::wstringstream buffer_stream_;
    };
    
    template<typename T>
    LogSync& LogSync::operator<<(const T& t)
    {
        buffer_stream_ << t;
        return *this;
    }

}

#endif // BOUNCE_LOGGING_LOG_SYNC_
