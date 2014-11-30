#ifndef BOUNCE_IMPORTER_H_
#define BOUNCE_IMPORTER_H_

#include <string>

#include "framework/resource_loader.h"
#include "renderer/model_manager.h"
#include "renderer/texture_manager.h"
#include "renderer/material_manager.h"
#include "renderer/vertex_buffer.h"
#include "renderer/model.h"

namespace bounce {

    class Importer {
    private:
        const ResourceLoader& resource_loader_;
        ModelManager& model_manager_;
        TextureManager& texture_manager_;
        MaterialManager& material_manager_;
        VertexBuffer& vertex_buffer_;
        
        Importer(const Importer&) = delete;
        Importer& operator=(const Importer&) = delete;

    public:
        Importer(const ResourceLoader& resource_loader,
                 ModelManager& model_manager,
                 TextureManager& texture_manager,
                 MaterialManager& material_manager,
                 VertexBuffer& vertex_buffer);
        
        int ImportFile(const std::string& filename);
    };    
}

#endif // BOUNCE_IMPORTER_H_