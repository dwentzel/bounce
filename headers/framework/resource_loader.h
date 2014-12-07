#ifndef BOUNCE_FRAMEWORK_RESOURCE_LOADER_
#define BOUNCE_FRAMEWORK_RESOURCE_LOADER_

#include <string>

#include "bounce_engine_export.h"

namespace bounce {

    class bounce_engine_EXPORT ResourceLoader {
    private:
        const std::string resources_base_path_;
        
        std::string LoadFileData(const std::string& file_path) const;
        
        ResourceLoader& operator=(const ResourceLoader&) = delete;
    public:
        ResourceLoader(const std::string& resources_base_path);
        
        std::string LoadShaderData(const std::string& shader_path) const;
        std::string LoadModelData(const std::string& model_path) const;
        
    };

}

#endif // BOUNCE_FRAMEWORK_RESOURCE_LOADER_
