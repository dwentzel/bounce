#ifndef BOUNCE_RENDERER_TEXTURE_MANAGER_H_
#define BOUNCE_RENDERER_TEXTURE_MANAGER_H_

#include <string>
#include "framework/object_cache.h"
#include "texture.h"

#include "bounce_engine_export.h"

namespace bounce {

    template class bounce_engine_EXPORT ObjectCache < Texture > ;

    class bounce_engine_EXPORT TextureManager {
    private:
        std::string texture_directory_path_;
        ObjectCache<Texture> textures_;
        
    public:
        TextureManager(const std::string& texture_directory_path);
        
        unsigned int GenerateTexture(const std::string& texture_path);
        
        bool HasTexture(const std::string& texture_path) const;
        
        const Texture& GetTexture(unsigned int texture_handle) const;
        int GetTextureHandle(const std::string& texture_name) const;
        
        void BindTexture(unsigned int texture_handle);
        
//        int IndexOf(const std::string& texture) const;
//        void LoadTexture(const std::string& texture);
//        unsigned int next_handle() const;
    };

}

#endif // BOUNCE_RENDERER_TEXTURE_MANAGER_H_
