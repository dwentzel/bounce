#ifndef BOUNCE_RENDERER_TEXTURE_MANAGER_
#define BOUNCE_RENDERER_TEXTURE_MANAGER_

#include <string>
#include <vector>
#include "texture.h"

namespace bounce {

    class TextureManager {
    private:
        std::string texture_directory_path_;
        std::vector<Texture> textures_;
    public:
        TextureManager(const std::string& texture_directory_path);
        
        bool HasTexture(const std::string& texture_path) const;
        
        const Texture& GetTexture(unsigned int texture_handle) const;
        
        void UseTexture(unsigned int texture_handle);
        
        int IndexOf(const std::string& texture) const;
        void LoadTexture(const std::string& texture);
        unsigned int next_handle() const;
    };

}

#endif // BOUNCE_RENDERER_TEXTURE_MANAGER_
