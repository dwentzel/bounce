#include "resource_loader.h"
#include "exceptions.h"
#include "logging/log.h"

#include <sstream>
#include <fstream>

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

bounce::ResourceLoader::ResourceLoader(const std::string& resources_base_path)
: resources_base_path_(resources_base_path)
{
}

std::string bounce::ResourceLoader::LoadFileData(const std::string& file_path) const
{
    std::stringstream output_stream;
    std::ifstream file_stream(file_path, std::ios::in);
    
    if (file_stream.is_open()) {
        std::string line;
        
        while (std::getline(file_stream, line)) {
            output_stream << line << "\n";
        }
        
        file_stream.close();
    }
    else {
        LOG_ERROR << "Could not find file " << file_path;
    }
    
    return output_stream.str();
}

std::unique_ptr<bounce::ImageData> bounce::ResourceLoader::LoadImageData(const std::string& image_path) const
{
    struct BitMapHeader header;
    
    std::ifstream file(resources_base_path_ + "/" + image_path, std::ios::in | std::ios::binary);
    if (file) {
        file.read(reinterpret_cast<char*>(&header), sizeof(struct BitMapHeader));
        
        if (header.type != 0x4D42)
        {
            LOG_ERROR << L"File " << image_path << L" is not a valid bitmap" << std::endl;
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
        
        std::unique_ptr<ImageData> image_data{ new ImageData() };
        image_data->size(header.size);
        image_data->width(width);
        image_data->height(height);
        image_data->data(pixel_data);
        
        return image_data;
    }
    else {
        LOG_ERROR << L"Could not find file " << image_path << std::endl;
        throw BounceException();
    }
}

std::string bounce::ResourceLoader::LoadShaderData(const std::string& shader_path) const
{
    return LoadFileData(resources_base_path_ + "/shaders/" + shader_path);
}

std::string bounce::ResourceLoader::LoadModelData(const std::string& model_path) const
{
    return LoadFileData(resources_base_path_ + "/models/" + model_path);
}
