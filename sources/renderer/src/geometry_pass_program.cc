#include "geometry_pass_program.h"

bounce::GeometryPassProgram::GeometryPassProgram()
{
    
}

bounce::GeometryPassProgram::~GeometryPassProgram()
{
    
}

void bounce::GeometryPassProgram::Init()
{
    CHECK_GL_ERROR();
    
    ShaderProgram::Init();
    
    LoadVertexShader("geometry_pass.vert.glsl");
    LoadFragmentShader("geometry_pass.frag.glsl");
    LinkProgram();
    
    mwvp_matrix_id_ = glGetUniformLocation(program_id(), "MWVP");
    wvp_matrix_id_ = glGetUniformLocation(program_id(), "WVP");
    view_matrix_id_ = glGetUniformLocation(program_id(), "V");
    world_matrix_id_ = glGetUniformLocation(program_id(), "W");
    model_matrix_id_ = glGetUniformLocation(program_id(), "M");
    
    CHECK_GL_ERROR();
}

void bounce::GeometryPassProgram::SetModelMatrix(const float* model_matrix)
{
    CHECK_GL_ERROR();
    glUniformMatrix4fv(model_matrix_id_, 1, GL_FALSE, model_matrix);
    CHECK_GL_ERROR();
}

void bounce::GeometryPassProgram::SetWorldMatrix(const float* model_matrix)
{
    CHECK_GL_ERROR();
    glUniformMatrix4fv(world_matrix_id_, 1, GL_FALSE, model_matrix);
    CHECK_GL_ERROR();
}

void bounce::GeometryPassProgram::SetViewMatrix(const float* view_matrix)
{
    CHECK_GL_ERROR();
    glUniformMatrix4fv(view_matrix_id_, 1, GL_FALSE, view_matrix);
    CHECK_GL_ERROR();
}

void bounce::GeometryPassProgram::SetWVPMatrix(const float* wvp_matrix)
{
    CHECK_GL_ERROR();
    glUniformMatrix4fv(wvp_matrix_id_, 1, GL_FALSE, wvp_matrix);
    CHECK_GL_ERROR();
}

void bounce::GeometryPassProgram::SetMWVPMatrix(const float* mwvp_matrix)
{
    CHECK_GL_ERROR();
    glUniformMatrix4fv(mwvp_matrix_id_, 1, GL_FALSE, mwvp_matrix);
    CHECK_GL_ERROR();
}