#ifndef BOUNCE_RENDERER_MESH_LOADER_H_
#define BOUNCE_RENDERER_MESH_LOADER_H_

#include "framework/resource_loader.h"
#include "mesh.h"

namespace bounce {

    class MeshLoader {
    private:
        const ResourceLoader& resource_loader_;
        
    public:
        MeshLoader(const ResourceLoader& resource_loader);
        
        Mesh* Load(const std::string& file) const;
    };

}

#endif // BOUNCE_RENDERER_MESH_LOADER_H_
