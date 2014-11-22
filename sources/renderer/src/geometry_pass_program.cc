#include "geometry_pass_program.h"

bounce::GeometryPassProgram::GeometryPassProgram()
{
    
}

bounce::GeometryPassProgram::~GeometryPassProgram()
{
    
}

bool bounce::GeometryPassProgram::Init()
{
    CHECK_GL_ERROR();
    
    CreateProgram();
    
    LoadVertexShader("geometry_pass.vert.glsl");
    LoadFragmentShader("geometry_pass.frag.glsl");
    LinkProgram();
    
    mwvp_matrix_location_ = GetUniformLocation("MWVP");
    wvp_matrix_location_ = GetUniformLocation("WVP");
    view_matrix_location_ = GetUniformLocation("V");
    world_matrix_location_ = GetUniformLocation("W");
    model_matrix_location_ = GetUniformLocation("M");
    
    color_texture_unit_location_ = GetUniformLocation("gColorMap");
    
    
    if (mwvp_matrix_location_ == GL_INVALID_INDEX
        || wvp_matrix_location_ == GL_INVALID_INDEX
        || view_matrix_location_ == GL_INVALID_INDEX
        || world_matrix_location_ == GL_INVALID_INDEX
        || model_matrix_location_ == GL_INVALID_INDEX) {
        
        LOG_ERROR << "Invalid uniform location in GeometryPassProgram";
        return false;
    }
    
    CHECK_GL_ERROR();
    return true;
}

void bounce::GeometryPassProgram::SetModelMatrix(const glm::mat4& model_matrix)
{
    CHECK_GL_ERROR();
    glUniformMatrix4fv(model_matrix_location_, 1, GL_FALSE, &model_matrix[0][0]);
    CHECK_GL_ERROR();
}

void bounce::GeometryPassProgram::SetWorldMatrix(const glm::mat4& model_matrix)
{
    CHECK_GL_ERROR();
    glUniformMatrix4fv(world_matrix_location_, 1, GL_FALSE, &model_matrix[0][0]);
    CHECK_GL_ERROR();
}

void bounce::GeometryPassProgram::SetViewMatrix(const glm::mat4& view_matrix)
{
    CHECK_GL_ERROR();
    glUniformMatrix4fv(view_matrix_location_, 1, GL_FALSE, &view_matrix[0][0]);
    CHECK_GL_ERROR();
}

void bounce::GeometryPassProgram::SetWVPMatrix(const glm::mat4& wvp_matrix)
{
    CHECK_GL_ERROR();
    glUniformMatrix4fv(wvp_matrix_location_, 1, GL_FALSE, &wvp_matrix[0][0]);
    CHECK_GL_ERROR();
}

void bounce::GeometryPassProgram::SetMWVPMatrix(const glm::mat4& mwvp_matrix)
{
    CHECK_GL_ERROR();
    glUniformMatrix4fv(mwvp_matrix_location_, 1, GL_FALSE, &mwvp_matrix[0][0]);
    CHECK_GL_ERROR();
}

void bounce::GeometryPassProgram::SetColorTextureUnit(unsigned int texture_unit)
{
    glUniform1i(color_texture_unit_location_, texture_unit);
}