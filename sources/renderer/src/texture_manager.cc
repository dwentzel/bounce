#include "texture_manager.h"
#include <fstream>
#include <algorithm>
#include <limits>

#include "logging/log.h"
#include "exceptions.h"

#include <cassert>

const unsigned int bounce::TextureManager::INVALID_INDEX = std::numeric_limits<unsigned int>::max();

bounce::TextureManager::TextureManager(const ResourceLoader& resource_loader)
: resource_loader_(resource_loader)
{
}

const bounce::Texture& bounce::TextureManager::GetTexture(unsigned int texture_handle) const
{
    return textures_.GetObject(texture_handle);
}

void bounce::TextureManager::BindTexture(unsigned int texture_handle)
{
    textures_.GetObject(texture_handle).UseTexture();
}

unsigned int bounce::TextureManager::GetTextureHandle(const std::string& texture_name) const
{
    std::vector<Texture>::const_iterator iter =
        std::find_if(textures_.begin(), textures_.end(),
                     [&texture_name](const Texture& texture) { return texture_name == texture.name(); } );
    
    assert(std::distance(textures_.begin(), iter) < std::numeric_limits<unsigned int>::max());
    return iter == textures_.end() ? INVALID_INDEX : static_cast<unsigned int>(std::distance(textures_.begin(), iter));
}

unsigned int bounce::TextureManager::GenerateTexture(const std::string& texture)
{
    std::unique_ptr<ImageData> image_data{ resource_loader_.LoadImageData("textures/" + texture) };
    
    unsigned int handle = textures_.GenerateObject(std::move(image_data));
    return handle;

}
