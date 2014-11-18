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
    
    mwvp_matrix_id_ = GetUniformLocation("MWVP");
    wvp_matrix_id_ = GetUniformLocation("WVP");
    view_matrix_id_ = GetUniformLocation("V");
    world_matrix_id_ = GetUniformLocation("W");
    model_matrix_id_ = GetUniformLocation("M");
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