#include "resource_loader.h"

#include <sstream>
#include <fstream>

#include "logging/log.h"

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
        
        while (getline(file_stream, line)) {
            output_stream << line << "\n";
        }
        
        file_stream.close();
    }
    else {
        LOG_ERROR << "Could not find file " << file_path;
    }
    
    return output_stream.str();
}

std::string bounce::ResourceLoader::LoadShaderData(const std::string& shader_path) const
{
    return LoadFileData(resources_base_path_ + "/shaders/" + shader_path);
}

std::string bounce::ResourceLoader::LoadModelData(const std::string& model_path) const
{
    return LoadFileData(resources_base_path_ + "/models/" + model_path);
}