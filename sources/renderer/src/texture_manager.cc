#include "texture_manager.h"
#include <fstream>
#include <algorithm>
#include <limits>

#include "logging/log.h"
#include "exceptions.h"

#include <cassert>

const unsigned int bounce::TextureManager::INVALID_INDEX = std::numeric_limits<unsigned int>::max();

bounce::TextureManager::TextureManager(const std::string& texture_directory_path)
: texture_directory_path_(texture_directory_path)
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

namespace {
    
#pragma pack(push, 1)
    struct BitMapHeader {
        uint16_t type;
        uint32_t size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset;
    };
#pragma pack(pop)

    struct Pixel {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
    };
    
}

unsigned int bounce::TextureManager::GenerateTexture(const std::string& texture)
{
    std::string texture_path = texture_directory_path_ + "/" + texture;
    
    struct BitMapHeader header;
    
    std::ifstream file(texture_path, std::ios::in | std::ios::binary);
    if (file) {
        file.read(reinterpret_cast<char*>(&header), sizeof(struct BitMapHeader));
        
        if (header.type != 0x4D42)
        {
            LOG_ERROR << L"File " << texture << L" is not a valid bitmap" << std::endl;
        }
        
        uint32_t width;
        uint32_t height;
        
        file.seekg(0x12);
        file.read(reinterpret_cast<char*>(&width), 4);
        file.read(reinterpret_cast<char*>(&height), 4);
        
        uint8_t* pixel_data = new uint8_t[header.size];
        
        file.seekg(header.offset);
        file.read(reinterpret_cast<char*>(pixel_data), header.size);
        file.close();
        
        unsigned int handle = textures_.GenerateObject(header.size, width, height, pixel_data);
        return handle;
    }
    else {
        LOG_ERROR << L"Could not find file " << texture_path << std::endl;
        throw RendererException();
    }
}
