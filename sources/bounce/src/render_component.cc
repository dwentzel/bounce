#include "render_component.h"

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

void bounce::RenderComponent::Startup() {

}

void bounce::RenderComponent::Shutdown() {
    
}

void bounce::RenderComponent::Update()
{
    render_system_->RenderModel(model_);
}

//void bounce::RenderComponent::Update() {
//    std::vector<GLfloat> vertices;
//    
//    const GLfloat* mesh_vertex_data = mesh_->vertex_data();
//    int mesh_vertex_count = mesh_->vertex_count();
//    
//    vertices.insert(vertices.end(), mesh_vertex_data, mesh_vertex_data + mesh_vertex_count);
//    
//    std::vector<GLfloat> normals;
//    
//    const GLfloat* mesh_normal_data = mesh_->normal_data();
//    int mesh_normal_count = mesh_->normal_count();
//    
//    normals.insert(normals.end(), mesh_normal_data, mesh_normal_data + mesh_normal_count);
//    
//    std::vector<GLfloat> colors;
//    
//    const GLfloat* mesh_color_data = mesh_->color_data();
//    int mesh_color_count = mesh_->color_count();
//    
//    colors.insert(colors.end(), mesh_color_data, mesh_color_data + mesh_color_count);
//    
//    std::vector<GLuint> indices;
//    
//    const GLuint* mesh_index_data = mesh_->index_data();
//    int mesh_index_count = mesh_->index_count();
//    
//    indices.insert(indices.end(), mesh_index_data, mesh_index_data + mesh_index_count);
//    
//    const int vertexArray = 0;
//    const int colorArray = 1;
//    const int normalArray = 2;
//    
//    render_system_->BindArrayBuffer(vertexArray);
//    render_system_->BufferArrayData(vertices.size(), &vertices[0]);
//    CheckGlError();
//    
//    render_system_->BindArrayBuffer(colorArray);
//    render_system_->BufferArrayData(colors.size(), &colors[0]);
//    CheckGlError();
//    
////    render_system_->BindArrayBuffer(normalArray);
////    render_system_->BufferArrayData(normals.size(), &normals[0]);
//    
//    render_system_->BindArrayBuffer(vertexArray);
//    render_system_->VertexAttribPointer(vertexArray, 4);
//    render_system_->EnableVertexAttribArray(vertexArray);
//    CheckGlError();
//    
//    render_system_->BindArrayBuffer(colorArray);
//    render_system_->VertexAttribPointer(colorArray, 3);
//    render_system_->EnableVertexAttribArray(colorArray);
//    CheckGlError();
//    
////    render_system_->BindArrayBuffer(normalArray);
////    render_system_->VertexAttribPointer(normalArray, 3);
////    render_system_->EnableVertexAttribArray(normalArray);
//
//    glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
//    CheckGlError();
//    
//    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
//    
//    render_system_->DisableVertexAttrib(vertexArray);
//    render_system_->DisableVertexAttrib(colorArray);
//    render_system_->DisableVertexAttrib(normalArray);
//    CheckGlError();
//
//}