#ifndef BOUNCE_RENDERER_TEXTURE_
#define BOUNCE_RENDERER_TEXTURE_

#include <string>
#include <cstdint>

#include "bounce_gl.h"

namespace bounce {

    class Texture {
    private:
        bool initialized_;
        
        unsigned int size_;
        unsigned int width_;
        unsigned int height_;
        
        GLuint texture_id_;
        
        std::string name_;
        std::uint8_t* data_;
        
        void Initialize();
        
    public:
        Texture(unsigned int size, unsigned int width, unsigned int height, std::uint8_t* data);
        ~Texture();
        
        void UseTexture();
        
        const std::string& name() const;
        
        unsigned int size() const;
        unsigned int width() const;
        unsigned int height() const;
        
        const std::uint8_t* data() const;
    };
    
}

#endif // BOUNCE_RENDERER_TEXTURE_
