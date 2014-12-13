#include "mesh.h"

bounce::Mesh::Mesh(GLuint vao, GLuint vertex_buffer, GLuint index_buffer, unsigned int index_count)
: vao_(vao), vertex_buffer_(vertex_buffer), index_buffer_(index_buffer), index_count_(index_count)
{
    //TODO: assert index_count_ here
}

bounce::Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &index_buffer_);
    glDeleteBuffers(1, &vertex_buffer_);
}

void bounce::Mesh::Render()
{
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(index_count_), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
