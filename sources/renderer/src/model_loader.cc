#include "model_loader.h"

#include <cassert>

bounce::ModelLoader::ModelLoader(TextureManager& texture_manager, MaterialManager& material_manager, ModelManager& model_manager)
: texture_manager_(texture_manager), material_manager_(material_manager), model_manager_(model_manager),
base_vertex_(0), index_offset_(0)
{
    
}

void bounce::ModelLoader::Begin()
{
    
}

unsigned int bounce::ModelLoader::LoadModel(const bounce::ImportedModel& imported_model)
{
    unsigned int model_index = model_manager_.GenerateModel();
    Model& model = model_manager_.GetModel(model_index);
    
    for (unsigned short i = 0; i < imported_model.mesh_count(); ++i) {
        unsigned int imported_model_mesh_vertex_count = imported_model.GetMeshVertexCount(i);
        if (imported_model_mesh_vertex_count > Model::MAX_MESH_VERTEX_COUNT) {
            throw std::out_of_range("too many vertices in model");
        }
        
        unsigned int imported_model_mesh_index_count = imported_model.GetMeshIndexCount(i);
        if (imported_model_mesh_index_count > Model::MAX_MESH_INDEX_COUNT) {
            throw std::out_of_range("too many indices in model");
        }

        const ImportedMaterial& imported_model_mesh_material = imported_model.GetMeshMaterial(i);
        
        unsigned int material_index = LoadMaterial(imported_model_mesh_material);
        
        model.AddMesh(index_offset_,
                      static_cast<unsigned short>(imported_model_mesh_index_count),
                      base_vertex_,
                      static_cast<unsigned short>(material_index));
        
        assert(index_offset_ + imported_model_mesh_index_count < std::numeric_limits<unsigned short>::max());
        index_offset_ += imported_model_mesh_index_count;
        base_vertex_ += imported_model_mesh_vertex_count;
    }
    
    const std::vector<float>& imported_model_vertex_data = imported_model.vertex_data();
    vertex_data_.insert(vertex_data_.end(), imported_model_vertex_data.begin(), imported_model_vertex_data.end());
    
    const std::vector<unsigned short>& imported_model_index_data = imported_model.index_data();
    index_data_.insert(index_data_.end(), imported_model_index_data.begin(), imported_model_index_data.end());
    
    return model_index;
}

void bounce::ModelLoader::End()
{
//    GLuint model_vertex_array;
//    GLuint model_vertex_buffer;
//    GLuint model_element_buffer;
//    
//    glGenVertexArrays(1, &model_vertex_array);
//    glBindVertexArray(model_vertex_array);
//    
//    glGenBuffers(1, &model_vertex_buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, model_vertex_buffer);
//    glBufferData(GL_ARRAY_BUFFER, vertex_data_.size() * sizeof(float), &vertex_data_[0], GL_STATIC_DRAW);
//    
//    // Vertex positions
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
//    // Texture coordinates
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    // Normal vectors
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
//    
//    glGenBuffers(1, &model_element_buffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model_element_buffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data_.size() * sizeof(unsigned short), &index_data_[0], GL_STATIC_DRAW);
//    
//    glBindVertexArray(0);
//    
//    model_manager_.vertex_array_object(model_vertex_array);
}

unsigned int bounce::ModelLoader::LoadMaterial(const bounce::ImportedMaterial& imported_material)
{
    unsigned int material_index = material_manager_.GenerateMaterial();
    Material& material = material_manager_.GetMaterial(material_index);
    
    material.diffuse(imported_material.diffuse());
    material.ambient(imported_material.ambient());
    material.specular(imported_material.specular());
    material.emissive(imported_material.emissive());
    material.specular(imported_material.specular());
    
    const std::string& texture_path = imported_material.texture_path();
    
    if (!texture_path.empty()) {
        unsigned int texture_handle = texture_manager_.GetTextureHandle(texture_path);
        if (texture_handle != TextureManager::INVALID_INDEX)
        {
            material.texture_handle(texture_handle);
        }
        else {
            texture_handle = texture_manager_.GenerateTexture(texture_path);
            material.texture_handle(texture_handle);
        }
    }
    
    return material_index;
}
