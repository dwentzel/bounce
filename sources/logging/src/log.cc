#include "log.h"

namespace bounce {
    
    std::wostream& operator<<(std::wostream& out, const std::string& str)
    {
        std::copy(str.begin(), str.end(), std::ostream_iterator<char, wchar_t>(out));
        return out;
    }
    
}