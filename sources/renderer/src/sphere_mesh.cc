#include "sphere_mesh.h"

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "logging/log.h"
#include "bounce_gl.h"

bounce::SphereMesh::SphereMesh() : vertex_count_(0), index_count_(0)
{
}

bounce::SphereMesh::~SphereMesh()
{
}

void bounce::SphereMesh::ImportFile(const std::string& filename)
{
    Assimp::Importer importer;
    
//    importer.Re
    
    const aiScene* scene = importer.ReadFile(filename,
                                             aiProcess_CalcTangentSpace |
                                             aiProcess_Triangulate |
                                             aiProcess_JoinIdenticalVertices |
                                             aiProcess_SortByPType);
    
    if (!scene) {
        LOG_ERROR << "Could not read scene from " << filename << std::endl;
    }
    
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[i];
        vertex_count_ += mesh->mNumVertices * 3;
        
        index_count_ += mesh->mNumFaces * 3;
    }
    
//    vertices_.resize(vertex_count_);
//    indices_.resize(index_count_);
    
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[i];
        
        unsigned int mesh_vertex_count = mesh->mNumVertices;
        
        for (unsigned int j = 0; j < mesh_vertex_count; ++j) {
            const aiVector3D& vertex = mesh->mVertices[j];
            vertices_.push_back(vertex.x);
            vertices_.push_back(vertex.y);
            vertices_.push_back(vertex.z);
        }
        
        unsigned int mesh_face_count = mesh->mNumFaces;
        
        for (unsigned int j = 0; j < mesh_face_count; ++j) {
            const aiFace& face = mesh->mFaces[j];
            
            for (int k = 0; k < 3; ++k) {
                indices_.push_back(face.mIndices[k]);
            }
        }
    }
    
    glGenBuffers(1, &vertex_buffer_);
    glGenBuffers(1, &index_buffer_);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, vertex_count_ * sizeof(float), &vertices_[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count_ * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);
}

void bounce::SphereMesh::Render()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, vertex_count_ * sizeof(float), &vertices_[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count_ * sizeof(unsigned int), &indices_[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_);
    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, 0);
    CHECK_GL_ERROR();
    glDisableVertexAttribArray(0);
}