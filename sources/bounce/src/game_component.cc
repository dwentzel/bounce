#include "game_component.h"

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

const bounce::GameComponentType* bounce::GameComponentType::Render = new bounce::GameComponentType(1);

const bounce::GameComponentType* bounce::RenderComponent::component_type_s_ = bounce::GameComponentType::Render;

const bounce::GameComponentType* bounce::RenderComponent::component_type() {
    return component_type_s_;
}

void bounce::RenderComponent::startup() {

}

void bounce::RenderComponent::shutdown() {
    
}

glm::vec3 position = glm::vec3(0, 0, 15);
float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;
float speed = 3.0f;
float mouseSpeed = 0.5f;

int xpos, ypos;

void bounce::RenderComponent::update() {
    std::vector<GLfloat> vertices;
    
    const GLfloat* mesh_vertex_data = mesh_->vertex_data();
    int mesh_vertex_count = mesh_->vertex_count();
    
    vertices.insert(vertices.end(), mesh_vertex_data, mesh_vertex_data + mesh_vertex_count);
    
    std::vector<GLfloat> normals;
    
    const GLfloat* mesh_normal_data = mesh_->normal_data();
    int mesh_normal_count = mesh_->normal_count();
    
    normals.insert(normals.end(), mesh_normal_data, mesh_normal_data + mesh_normal_count);
    
    std::vector<GLfloat> colors;
    
    const GLfloat* mesh_color_data = mesh_->color_data();
    int mesh_color_count = mesh_->color_count();
    
    colors.insert(colors.end(), mesh_color_data, mesh_color_data + mesh_color_count);
    
    std::vector<GLuint> indices;
    
    const GLuint* mesh_index_data = mesh_->index_data();
    int mesh_index_count = mesh_->index_count();
    
    indices.insert(indices.end(), mesh_index_data, mesh_index_data + mesh_index_count);
    
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    
    GLuint normalBuffer;
    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
    
    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
    
    //GLuint element_buffer;
    //glGenBuffers(1, &element_buffer);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    
    glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle),
                        sin(verticalAngle), cos(verticalAngle) * cos(verticalAngle));
    
    glm::vec3 position(0, 0, 5);
    float fov = initialFoV;
    
    glm::mat4 projection = glm::perspective(fov, 4.0f / 3.0f, 0.1f, 100.0f);
    
    glm::mat4 view = glm::lookAt(position, glm::vec3(0, 0, 0),
                                 glm::vec3(0, 1, 0));
    
    //glm::mat4 model = glm::rotate(glm::mat4(1.0f), horizontalAngle,
    //    glm::vec3(0, 1, 0))
    //    * glm::rotate(glm::mat4(1.0f), verticalAngle, glm::vec3(1, 0, 0));
    
    //glm::mat4 model = object.model_matrix();
    
    //glm::mat4 model = glm::mat4(1.0f);
    
    glm::quat horizontal = glm::angleAxis(0.0f, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::quat vertical = glm::angleAxis(0.0f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
    
    
    glm::quat rot = vertical * horizontal;
    
    //model_matrix_ = glm::toMat4(rot);
    
    //model_matrix_ = glm::rotate(glm::mat4(1.0f), vertical_angle_, glm::vec3(1, 0, 0)) *
    //    glm::rotate(glm::mat4(1.0f), horizontal_angle_, glm::vec3(0, 1, 0))
    //    ;
    
    //glm::quat rot = RotationBetweenVectors(glm::vec3(1, 0, 0), direction);
    glm::mat4 model = glm::toMat4(rot);
    
    
    glm::mat4 mvp = projection * view * model;
    //glm::mat4 mvp = projection * view;
    
    //glUniformMatrix4fv(matrix_id_, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(matrix_id_, 1, GL_FALSE, &mvp[0][0]);
    
    
    const int vertexArray = 0;
    const int colorArray = 1;
    const int normalArray = 2;
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(vertexArray, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(vertexArray);
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(colorArray, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(colorArray);
    
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glVertexAttribPointer(normalArray, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(normalArray);
    
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
    
    
    
    glDrawArrays(GL_TRIANGLES, 0, 3 * 12);
    
    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    
    glDisableVertexAttribArray(vertexArray);
    glDisableVertexAttribArray(colorArray);
    glDisableVertexAttribArray(normalArray);
}