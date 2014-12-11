#include "model.h"

const unsigned short bounce::Model::MAX_MESH_COUNT  = std::numeric_limits<unsigned short>::max();

bounce::Model bounce::Model::Create()
{
    return Model();
}

bounce::Model::Model()
{
    
}

void bounce::Model::AddMesh(unsigned short index_offset, unsigned short index_count, unsigned int base_vertex, unsigned short material_index)
{
    if (meshes_.size() >= MAX_MESH_COUNT) {
        throw std::out_of_range("too many meshes");
    }
    
    MeshData mesh_data;
    mesh_data.index_offset = index_offset;
    mesh_data.index_count = index_count;
    mesh_data.base_vertex = base_vertex;
    mesh_data.material_index = material_index;
    
    meshes_.push_back(mesh_data);
}

unsigned short bounce::Model::mesh_count() const
{
    return static_cast<unsigned short>(meshes_.size());
}

unsigned short bounce::Model::GetMeshIndexOffset(unsigned short mesh_index) const
{
    return meshes_[mesh_index].index_offset;
}

unsigned short bounce::Model::GetMeshIndexCount(unsigned short mesh_index) const
{
    return meshes_[mesh_index].index_count;
}

unsigned int bounce::Model::GetMeshBaseVertex(unsigned short mesh_index) const
{
    return meshes_[mesh_index].base_vertex;
}

unsigned short bounce::Model::GetMeshMaterialIndex(unsigned short mesh_index) const
{
    return meshes_[mesh_index].material_index;
}
