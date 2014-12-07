#include "imported_model.h"

#include <vector>

namespace bounce {
    struct MeshData {
        unsigned short first_vertex;
        unsigned short vertex_count;
        unsigned short first_index;
        unsigned short index_count;
        unsigned short material_index;
    };
}

class bounce::ImportedModelImpl {
private:
    std::vector<float> vertex_data_;
    std::vector<unsigned short> indices_;
    
    std::vector<MeshData> mesh_data_;
    std::vector<ImportedMaterial> materials_;
    
public:
    ImportedModelImpl()
    {
        
    }
    
    ~ImportedModelImpl() 
    {

    }

    void AddMesh(const MeshData& mesh_data)
    {
        mesh_data_.push_back(mesh_data);
    }
    
    void AddVertex(float x, float y, float z)
    {
        vertex_data_.push_back(x);
        vertex_data_.push_back(y);
        vertex_data_.push_back(z);
    }
    
    void AddUV(float x, float y)
    {
        vertex_data_.push_back(x);
        vertex_data_.push_back(y);
    }
    
    void AddNormal(float x, float y, float z)
    {
        vertex_data_.push_back(x);
        vertex_data_.push_back(y);
        vertex_data_.push_back(z);
    }
    
    void AddIndex(unsigned short index)
    {
        indices_.push_back(index);
    }
    
    void AddMaterial(const ImportedMaterial& material)
    {
        materials_.push_back(material);
    }
    
    unsigned short mesh_count() const
    {
        return mesh_data_.size();
    }
    
    unsigned short GetMeshIndexOffset(unsigned short mesh_index) const
    {
        return mesh_data_[mesh_index].first_index;
    }
    
    unsigned short GetMeshIndexCount(unsigned short mesh_index) const
    {
        return mesh_data_[mesh_index].index_count;
    }
    
    unsigned short GetMeshFirstVertex(unsigned short mesh_index) const
    {
        return mesh_data_[mesh_index].first_vertex;
    }
    
    unsigned short GetMeshVertexCount(unsigned short mesh_index) const
    {
        return mesh_data_[mesh_index].vertex_count;
    }
    
    const bounce::ImportedMaterial& GetMeshMaterial(unsigned short mesh_index) const
    {
        unsigned short material_index = mesh_data_[mesh_index].material_index;
        return materials_[material_index];
    }
    
    const std::vector<float>& vertex_data() const
    {
        return vertex_data_;
    }
    
    const std::vector<unsigned short>& index_data() const
    {
        return indices_;
    }
};

bounce::ImportedModel::ImportedModel()
: impl_(new ImportedModelImpl())
{
    
}

bounce::ImportedModel::ImportedModel(ImportedModel&& source)
: impl_(std::move(source.impl_))
{
    
}

bounce::ImportedModel::~ImportedModel()
{

}

void bounce::ImportedModel::AddMesh(unsigned short first_vertex,
                                    unsigned short vertex_count,
                                    unsigned short first_index,
                                    unsigned short index_count,
                                    unsigned short material_index)
{
    MeshData mesh_data;
    mesh_data.first_vertex = first_vertex;
    mesh_data.vertex_count = vertex_count;
    mesh_data.first_index = first_index;
    mesh_data.index_count = index_count;
    mesh_data.material_index = material_index;
    
    impl_->AddMesh(mesh_data);
}

void bounce::ImportedModel::AddVertex(float x, float y, float z)
{
    impl_->AddVertex(x, y, z);
}

void bounce::ImportedModel::AddIndex(unsigned short index)
{
    impl_->AddIndex(index);
}

void bounce::ImportedModel::AddUV(float x, float y)
{
    impl_->AddUV(x, y);
}

void bounce::ImportedModel::AddNormal(float x, float y, float z)
{
    impl_->AddNormal(x, y, z);
}

void bounce::ImportedModel::AddMaterial(const bounce::ImportedMaterial& material)
{
    impl_->AddMaterial(material);
}

unsigned short bounce::ImportedModel::mesh_count() const
{
    return impl_->mesh_count();
}

unsigned short bounce::ImportedModel::GetMeshIndexOffset(unsigned short mesh_index) const
{
    return impl_->GetMeshIndexOffset(mesh_index);
}

unsigned short bounce::ImportedModel::GetMeshIndexCount(unsigned short mesh_index) const
{
    return impl_->GetMeshIndexCount(mesh_index);
}

unsigned short bounce::ImportedModel::GetMeshFirstVertex(unsigned short mesh_index) const
{
    return impl_->GetMeshFirstVertex(mesh_index);
}

unsigned short bounce::ImportedModel::GetMeshVertexCount(unsigned short mesh_index) const
{
    return impl_->GetMeshVertexCount(mesh_index);
}

const bounce::ImportedMaterial& bounce::ImportedModel::GetMeshMaterial(unsigned short mesh_index) const
{
    return impl_->GetMeshMaterial(mesh_index);
}

const std::vector<float>& bounce::ImportedModel::vertex_data() const
{
    return impl_->vertex_data();
}

const std::vector<unsigned short>& bounce::ImportedModel::index_data() const
{
    return impl_->index_data();
}
