#ifndef BOUNCE_FRAMEWORK_RESOURCE_LOADER_
#define BOUNCE_FRAMEWORK_RESOURCE_LOADER_

#include <string>

namespace bounce {

    class ResourceLoader {
    private:
        std::string resources_base_path_;
        
    public:
        ResourceLoader(const std::string& resources_base_path);
        
        std::string LoadShader(const std::string& shader_path);
        std::string LoadModel(const std::string& model_path);
        
    };

}

#endif // BOUNCE_FRAMEWORK_RESOURCE_LOADER_
