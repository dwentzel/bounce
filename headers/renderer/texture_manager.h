#ifndef BOUNCE_RENDERER_TEXTURE_MANAGER_H_
#define BOUNCE_RENDERER_TEXTURE_MANAGER_H_

#include <string>
#include "framework/object_cache.h"
#include "texture.h"

namespace bounce {

    class TextureManager {
    private:
        std::string texture_directory_path_;
        ObjectCache<Texture> textures_;
        
        TextureManager(const TextureManager&) = delete;

    public:
        static const unsigned int INVALID_INDEX;
        
        TextureManager(const std::string& texture_directory_path);
        
        unsigned int GenerateTexture(const std::string& texture_path);
                
        const Texture& GetTexture(unsigned int texture_handle) const;
        unsigned int GetTextureHandle(const std::string& texture_name) const;
        
        void BindTexture(unsigned int texture_handle);
        
    };

}

#endif // BOUNCE_RENDERER_TEXTURE_MANAGER_H_
