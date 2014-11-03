#ifndef BOUNCE_IMPORTER_H_
#define BOUNCE_IMPORTER_H_

#include <string>
#include <vector>
#include "renderer/model_manager.h"
#include "renderer/material_manager.h"
#include "renderer/vertex_buffer.h"
#include "renderer/model.h"

namespace bounce {

    class Importer {
    private:
        ModelManager& model_manager_;
        MaterialManager& material_manager_;
        VertexBuffer& vertex_buffer_;
        
        Importer(const Importer&) = delete;
        Importer& operator=(const Importer&) = delete;

    public:
        Importer(ModelManager& model_manager_,
                 MaterialManager& material_manager,
                 VertexBuffer& vertex_buffer);
        int ImportFile(const std::string& filename);
    };    
}

#endif // BOUNCE_IMPORTER_H_