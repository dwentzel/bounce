#ifndef BOUNCE_FRAMEWORK_IMAGE_DATA_H_
#define BOUNCE_FRAMEWORK_IMAGE_DATA_H_

#include "bounce.h"
#include <cstdint>

namespace bounce {

    class ImageData {
    public:
        ImageData();
        ImageData(ImageData&& other);
        ~ImageData() NOEXCEPT;
        
        unsigned int size() const;
        void size(unsigned int value);
        
        unsigned int width() const;
        void width(unsigned int value);
        
        unsigned int height() const;
        void height(unsigned int value);
        
        const std::uint8_t* data() const;
        void data(const std::uint8_t* value);
        
    private:
        unsigned int size_;
        unsigned int width_;
        unsigned int height_;

        const std::uint8_t* data_;
        
    private:
        ImageData(const ImageData&) = delete;
        ImageData& operator=(const ImageData&) = delete;
    };
    
    

}

#endif // BOUNCE_FRAMEWORK_IMAGE_DATA_H_
