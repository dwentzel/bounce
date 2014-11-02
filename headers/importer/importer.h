#ifndef BOUNCE_IMPORTER_H_
#define BOUNCE_IMPORTER_H_

#include <string>
#include <vector>
#include "renderer/material.h"
#include "renderer/vertex_buffer.h"
#include "renderer/model.h"

namespace bounce {

    class Importer {
    private:
        MaterialManager& material_manager_;
        VertexBuffer& vertex_buffer_;
        
        Importer(const Importer&) = delete;
        Importer& operator=(const Importer&) = delete;

    public:
        Importer(MaterialManager& material_manager, VertexBuffer& vertex_buffer);
        Model ImportFile(const std::string& filename);
    };
    
    inline Importer::Importer(MaterialManager& material_manager, VertexBuffer& vertex_buffer)
    : material_manager_(material_manager), vertex_buffer_(vertex_buffer)
    {}
    
}

#endif // BOUNCE_IMPORTER_H_