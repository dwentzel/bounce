#include "mesh_loader.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wnewline-eof"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma clang diagnostic pop

#include "logging/log.h"

#include "exceptions.h"

bounce::MeshLoader::MeshLoader(const ResourceLoader& resource_loader)
: resource_loader_(resource_loader)
{
    
}

bounce::Mesh* bounce::MeshLoader::Load(const std::string& resource_name) const
{
    std::string data = resource_loader_.LoadModelData(resource_name);
    
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFileFromMemory(data.c_str(), data.size(),
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_SortByPType);
    
    if (!scene) {
        LOG_ERROR << "Could not read scene from " << resource_name;
        throw RendererException();
    }
    
    unsigned int vertex_count = 0;
    unsigned int index_count = 0;
    
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[i];
        vertex_count += mesh->mNumVertices * 3;
        
        index_count += mesh->mNumFaces * 3;
    }
    
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[i];
        
        unsigned int mesh_vertex_count = mesh->mNumVertices;
        
        for (unsigned int j = 0; j < mesh_vertex_count; ++j) {
            const aiVector3D& vertex = mesh->mVertices[j];
            vertices.push_back(vertex.x);
            vertices.push_back(vertex.y);
            vertices.push_back(vertex.z);
        }
        
        unsigned int mesh_face_count = mesh->mNumFaces;
        
        for (unsigned int j = 0; j < mesh_face_count; ++j) {
            const aiFace& face = mesh->mFaces[j];
            
            for (int k = 0; k < 3; ++k) {
                indices.push_back(face.mIndices[k]);
            }
        }
    }
    
    GLuint vao;
    GLuint vertex_buffer;
    GLuint index_buffer;
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    glBindVertexArray(0);
    
    return new Mesh(vao, vertex_buffer, index_buffer, index_count);
}
