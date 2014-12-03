#include "model_loader.h"

bounce::ModelLoader::ModelLoader(TextureManager& texture_manager, ModelManager& model_manager)
: texture_manager_(texture_manager), model_manager_(model_manager),
base_vertex_(0), index_offset_(0)
{
    
}

void bounce::ModelLoader::Begin()
{
    
}

int bounce::ModelLoader::LoadModel(const bounce::ImportedModel& imported_model)
{
    int model_index = model_manager_.next_handle();
    Model& model = model_manager_.CreateModel();
    
    for (unsigned int i = 0; i < imported_model.mesh_count(); ++i) {
        
        
        unsigned int imported_model_mesh_first_vertex = imported_model.GetMeshFirstVertex(i);
        unsigned short imported_model_mesh_vertex_count = imported_model.GetMeshVertexCount(i);
        
        unsigned short imported_model_mesh_index_offset = imported_model.GetMeshIndexOffset(i);
        unsigned short imported_model_mesh_index_count = imported_model.GetMeshIndexCount(i);

        const ImportedMaterial& imported_model_mesh_material = imported_model.GetMeshMaterial(i);
        
        unsigned short material_index = LoadMaterial(imported_model_mesh_material);
        
        model.AddMesh(imported_model_mesh_index_offset + index_offset_,
                      imported_model_mesh_index_count,
                      imported_model_mesh_first_vertex + base_vertex_,
                      material_index);
        
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

int bounce::ModelLoader::LoadMaterial(const bounce::ImportedMaterial& imported_material)
{
    const std::string& texture_path = imported_material.texture_path();
    
    if (texture_path != "") {
        if (texture_manager_.HasTexture(texture_path))
        {
            return texture_manager_.IndexOf(texture_path);
        }
        else {
            texture_manager_.LoadTexture(texture_path);
            return texture_manager_.IndexOf(texture_path);
        }
    }
    
    return -1;
}
