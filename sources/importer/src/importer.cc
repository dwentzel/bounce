#include "importer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "logging/log.h"

bounce::Importer::Importer(const ResourceLoader& resource_loader,
                           ModelManager& model_manager,
                           TextureManager& texture_manager,
                           MaterialManager& material_manager,
                           VertexBuffer& vertex_buffer)
: resource_loader_(resource_loader),
  model_manager_(model_manager),
  texture_manager_(texture_manager),
  material_manager_(material_manager),
  vertex_buffer_(vertex_buffer)
{}


int bounce::Importer::ImportFile(const std::string& filename)
{
    std::string data = resource_loader_.LoadModelData(filename);
    
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFileFromMemory(data.c_str(), data.size(),
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                                       aiProcess_SortByPType);
    
    if (!scene) {
        LOG_ERROR << "Could not read scene from " << filename << std::endl;
    }
    
    const int vertex_total_size = sizeof(aiVector3D) * 2 + sizeof(aiVector2D);
    
    int total_vertex_count = 0;
    
    unsigned int model_handle = model_manager_.next_handle();
    Model& model = model_manager_.CreateModel();
    
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[i];
        unsigned int mesh_face_count = mesh->mNumFaces;
        
        model.AddMeshMaterialIndex(mesh->mMaterialIndex);
        
        int vbo_size = vertex_buffer_.current_size();
        
        model.AddMeshStartIndex(vbo_size / vertex_total_size);
        
        for (unsigned int j = 0; j < mesh_face_count; ++j) {
            const aiFace& face = mesh->mFaces[j];
            
            for (int k = 0; k < 3; ++k) {
                aiVector3D vertex_position = mesh->mVertices[face.mIndices[k]];
                aiVector3D uv = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][face.mIndices[k]] : aiVector3D(0.0f);                
                aiVector3D normal = mesh->HasNormals() ? mesh->mNormals[face.mIndices[k]] : aiVector3D(1.0f, 1.0f, 1.0f);
                vertex_buffer_.AddData(&vertex_position, sizeof(aiVector3D));
                vertex_buffer_.AddData(&uv, sizeof(aiVector2D));
                vertex_buffer_.AddData(&normal, sizeof(aiVector3D));
            }
        }
        
        int mesh_vertex_count = mesh->mNumVertices;
        total_vertex_count += mesh_vertex_count;
        model.AddMeshSize((vertex_buffer_.current_size() - vbo_size) / vertex_total_size);
    }
    
    int material_count = scene->mNumMaterials;
    
    for (int i = 0; i < material_count; ++i) {
        model.AddMeshMaterialIndex(material_manager_.next_index());
        
        Material& new_material = material_manager_.CreateMaterial();
        
        const aiMaterial* material = scene->mMaterials[i];
        
//        aiString name;
//        if (material->Get(AI_MATKEY_NAME, name) != AI_SUCCESS) {
//            
//        }
        
        aiString texture;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texture) == AI_SUCCESS) {
            std::string path(texture.C_Str());
            
            int texture_index = texture_manager_.IndexOf(path);
            
            if (texture_index == -1) {
                texture_index = texture_manager_.next_handle();
                texture_manager_.LoadTexture(path);
                new_material.texture_handle(texture_index);
            }
            else {
                new_material.texture_handle(texture_index);
            }
        }
        
        aiColor3D color_diffuse;
        if (material->Get(AI_MATKEY_COLOR_DIFFUSE, color_diffuse) != AI_SUCCESS) {
            
        }
        new_material.diffuse(&color_diffuse);
        
        aiColor3D color_specular;
        if (material->Get(AI_MATKEY_COLOR_SPECULAR, color_specular) != AI_SUCCESS) {
            
        }
        new_material.specular(&color_specular);

        aiColor3D color_ambient;
        if (material->Get(AI_MATKEY_COLOR_AMBIENT, color_ambient) != AI_SUCCESS) {
            
        }
        new_material.ambient(&color_ambient);

        aiColor3D color_emissive;
        if (material->Get(AI_MATKEY_COLOR_EMISSIVE, color_emissive) != AI_SUCCESS) {
            
        }
        new_material.emissive(&color_emissive);

        float shininess;
        if (material->Get(AI_MATKEY_SHININESS, shininess) != AI_SUCCESS) {
            
        }
        new_material.shininess(shininess);
    }
    
    return model_handle;
}