#include "geometry_pass_program.h"

bounce::GeometryPassProgram::GeometryPassProgram(const ResourceLoader& resource_loader)
: ShaderProgram(resource_loader)
{
    
}

void bounce::GeometryPassProgram::Init()
{
    CreateProgram();
    
    LoadVertexShader("geometry_pass.vert.glsl");
    LoadFragmentShader("geometry_pass.frag.glsl");
    LinkProgram();
    
    wvp_matrix_location_ = GetUniformLocation("WVP");
    vp_matrix_location_ = GetUniformLocation("VP");
    view_matrix_location_ = GetUniformLocation("V");
    world_matrix_location_ = GetUniformLocation("W");
    
    color_texture_unit_location_ = GetUniformLocation("gColorMap");
}

void bounce::GeometryPassProgram::SetWorldMatrix(const glm::mat4& model_matrix)
{
    glUniformMatrix4fv(world_matrix_location_, 1, GL_FALSE, &model_matrix[0][0]);
}

void bounce::GeometryPassProgram::SetViewMatrix(const glm::mat4& view_matrix)
{
    glUniformMatrix4fv(view_matrix_location_, 1, GL_FALSE, &view_matrix[0][0]);
}

void bounce::GeometryPassProgram::SetWVPMatrix(const glm::mat4& wvp_matrix)
{
    glUniformMatrix4fv(wvp_matrix_location_, 1, GL_FALSE, &wvp_matrix[0][0]);
}

void bounce::GeometryPassProgram::SetVPMatrix(const glm::mat4& vp_matrix)
{
    glUniformMatrix4fv(wvp_matrix_location_, 1, GL_FALSE, &vp_matrix[0][0]);
}

void bounce::GeometryPassProgram::SetColorTextureUnit(int texture_unit)
{
    glUniform1i(color_texture_unit_location_, texture_unit);
}
