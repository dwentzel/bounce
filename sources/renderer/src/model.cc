#include "model.h"

bounce::Model bounce::Model::Create()
{
    return Model();
}

bounce::Model::Model()
{
    
}

void bounce::Model::AddMesh(unsigned short index_offset, unsigned short index_count, unsigned short base_vertex, unsigned short material_index)
{
    MeshData mesh_data;
    mesh_data.index_offset = index_offset;
    mesh_data.index_count = index_count;
    mesh_data.base_vertex = base_vertex;
    mesh_data.material_index = material_index;
    
    meshes_.push_back(mesh_data);
}

unsigned short bounce::Model::mesh_count() const
{
    return meshes_.size();
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
