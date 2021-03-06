#ifndef BOUNCE_RENDERER_TEXTURE_MANAGER_H_
#define BOUNCE_RENDERER_TEXTURE_MANAGER_H_

#include <string>
#include "framework/resource_loader.h"
#include "framework/object_cache.h"
#include "texture.h"

namespace bounce {

    class TextureManager {
    public:
        static const unsigned int INVALID_INDEX;
        
        explicit TextureManager(const ResourceLoader& resource_loader);
        
        unsigned int GenerateTexture(const std::string& texture_path);
        
        const Texture& GetTexture(unsigned int texture_handle) const;
        unsigned int GetTextureHandle(const std::string& texture_name) const;
        
        void BindTexture(unsigned int texture_handle);
    
    private:
        const ResourceLoader& resource_loader_;
        ObjectCache<Texture> textures_;
        
        TextureManager(const TextureManager&) = delete;
        TextureManager& operator=(const TextureManager&) = delete;
    };

}

#endif // BOUNCE_RENDERER_TEXTURE_MANAGER_H_
