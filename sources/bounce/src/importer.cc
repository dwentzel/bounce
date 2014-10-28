#include "importer.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "model.h"

bounce::Model bounce::Importer::ImportFile(const std::string& filename)
{
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(filename,
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_SortByPType);
    
    if (!scene) {
        
    }
    
    const int vertex_total_size = sizeof(aiVector3D) * 2 + sizeof(aiVector2D);
    
    int total_vertex_count = 0;
    
    Model model;
    
    for (int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[i];
        int mesh_face_count = mesh->mNumFaces;
        
        model.AddMeshMaterialIndex(mesh->mMaterialIndex);
        
        int vbo_size = vertex_buffer_.current_size();
        
        model.AddMeshStartIndex(vbo_size / vertex_total_size);
        
        for (int j = 0; j < mesh_face_count; ++j) {
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
        
        return model;
    }
}