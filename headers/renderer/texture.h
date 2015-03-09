#ifndef BOUNCE_RENDERER_TEXTURE_H_
#define BOUNCE_RENDERER_TEXTURE_H_

#include "framework/image_data.h"

#include <memory>
#include <string>
#include <cstdint>

#include "bounce_gl.h"

namespace bounce {

    class Texture {
    public:
        static Texture Create(std::unique_ptr<ImageData> image_data);
        
        Texture(Texture&& source);
        ~Texture();
        
        void UseTexture();
        
        const std::string& name() const;
        
        unsigned int size() const;
        unsigned int width() const;
        unsigned int height() const;

    private:
        std::unique_ptr<ImageData> image_data_;
        GLuint texture_id_;
        std::string name_;
        
        explicit Texture(std::unique_ptr<ImageData> image_data);

    private:
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
    };
    
}

#endif // BOUNCE_RENDERER_TEXTURE_H_
