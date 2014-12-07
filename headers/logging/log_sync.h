#ifndef BOUNCE_LOGGING_LOG_SYNC_
#define BOUNCE_LOGGING_LOG_SYNC_

#include <ostream>
#include <sstream>

#include "bounce_engine_export.h"

namespace bounce {

    template class bounce_engine_EXPORT std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;

    class bounce_engine_EXPORT LogSync {
    private:
        std::wostream& output_stream_;
        std::wstringstream buffer_stream_;
        
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

    };
    
    template<typename T>
    LogSync& LogSync::operator<<(const T& t)
    {
        buffer_stream_ << t;
        return *this;
    }

}

#endif // BOUNCE_LOGGING_LOG_SYNC_
