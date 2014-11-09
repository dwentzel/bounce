#ifndef BOUNCE_RENDERER_TEXTURE_
#define BOUNCE_RENDERER_TEXTURE_

#include <string>
#include <cstdint>

namespace bounce {

    class Texture {
    private:
        unsigned int size_;
        unsigned int width_;
        unsigned int height_;
        
        std::string name_;
        std::uint8_t* data_;
        
    public:
        Texture(unsigned int size, unsigned int width, unsigned int height, std::uint8_t* data);
        ~Texture();
        
        const std::string& name() const;
        
        unsigned int size() const;
        unsigned int width() const;
        unsigned int height() const;
        
        const std::uint8_t* data() const;
    };

    inline unsigned int Texture::size() const
    {
        return size_;
    }
    
    inline unsigned int Texture::width() const
    {
        return width_;
    }
    
    inline unsigned int Texture::height() const
    {
        return height_;
    }
    
    inline const std::uint8_t* Texture::data() const
    {
        return data_;
    }
    
}

#endif // BOUNCE_RENDERER_TEXTURE_
