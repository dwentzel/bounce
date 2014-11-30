#include "texture_manager.h"
#include <fstream>

#include "logging/log.h"

bounce::TextureManager::TextureManager(const std::string& texture_directory_path)
: texture_directory_path_(texture_directory_path)
{
    
}

bool bounce::TextureManager::HasTexture(const std::string& texture_path) const
{
    
    return false;
}

const bounce::Texture& bounce::TextureManager::GetTexture(unsigned int texture_handle) const
{
    return textures_[texture_handle];
}

void bounce::TextureManager::UseTexture(unsigned int texture_handle)
{
    textures_[texture_handle].UseTexture();
}

int bounce::TextureManager::IndexOf(const std::string& texture) const
{
    return -1;
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

void bounce::TextureManager::LoadTexture(const std::string& texture)
{
    std::string texture_path = texture_directory_path_ + "/" + texture;
    
    struct BitMapHeader header;
    
    std::ifstream file(texture_path, std::ios::in | std::ios::binary);
    if (file) {
        file.read((char*)&header, sizeof(struct BitMapHeader));
        
        if (header.type != 0x4D42)
        {
            LOG_WARNING << L"File " << texture << L" is not a valid bitmap" << std::endl;
        }
        
        uint32_t width;
        uint32_t height;
        
        file.seekg(0x12);
        file.read((char*)&width, 4);
        file.read((char*)&height, 4);
        
        uint8_t* pixel_data = new uint8_t[header.size];
        
        file.seekg(header.offset);
        file.read((char*)pixel_data, header.size);
        
        textures_.emplace_back(header.size, width, height, pixel_data);
        file.close();
    }
    else {
        LOG_WARNING << L"Could not find file " << texture_path << std::endl;
    }
}

unsigned int bounce::TextureManager::next_handle() const
{
    return textures_.size();
}
