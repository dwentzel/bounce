#ifndef BOUNCE_IMPORTER_H_
#define BOUNCE_IMPORTER_H_

#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include "vertex_buffer.h"
#include "model.h"

namespace bounce {

    class Importer {
    private:
        VertexBuffer& vertex_buffer_;
        
    public:
        Importer(VertexBuffer& vertex_buffer);
        Model ImportFile(const std::string& filename);
    };
    
    inline Importer::Importer(VertexBuffer& vertex_buffer) : vertex_buffer_(vertex_buffer) {}
    
}

#endif // BOUNCE_IMPORTER_H_