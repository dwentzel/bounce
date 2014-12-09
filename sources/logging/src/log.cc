#include "log.h"

namespace bounce {
    
    std::wostream& operator<<(std::wostream& out, const std::string& str)
    {
        std::copy(str.begin(), str.end(), std::ostream_iterator<char, wchar_t>(out));
        return out;
    }
    
    std::wostream& operator<<(std::wostream& out, const unsigned char* data)
    {
        if (data == nullptr) {
            out << L"(null)";
        }
        else {
            out << std::string(reinterpret_cast<const char*>(data));
        }
        
        return out;
    }
    
}