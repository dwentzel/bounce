#include "mesh.h"

bounce::Mesh::Mesh(GLuint vao, GLuint vertex_buffer, GLuint index_buffer, unsigned int index_count)
: vao_(vao), vertex_buffer_(vertex_buffer), index_buffer_(index_buffer), index_count_(index_count)
{
    
}

bounce::Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vao_);
}

void bounce::Mesh::Render()
{
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
