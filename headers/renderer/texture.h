#ifndef BOUNCE_RENDERER_TEXTURE_H_
#define BOUNCE_RENDERER_TEXTURE_H_

#include <string>
#include <cstdint>

#include "bounce_gl.h"

namespace bounce {

    class Texture {
    private:        
        unsigned int size_;
        unsigned int width_;
        unsigned int height_;
        
        GLuint texture_id_;
        std::string name_;
        
        const std::uint8_t* data_;
        
        Texture(unsigned int size, unsigned int width, unsigned int height, const std::uint8_t* data);
        
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
        
    public:
        static Texture Create(unsigned int size, unsigned int width, unsigned int height, const std::uint8_t* data);
        
        Texture(Texture&& source);
        ~Texture();
        
        void UseTexture();
        
        const std::string& name() const;
        
        unsigned int size() const;
        unsigned int width() const;
        unsigned int height() const;
        
    };
    
}

#endif // BOUNCE_RENDERER_TEXTURE_H_
