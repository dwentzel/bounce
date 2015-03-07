#include "shader_program.h"

#include "logging/log.h"

#include <algorithm>
#include <fstream>

namespace {
    
    void LogShaderInfoLog(bounce::LogLevel log_level, GLuint shader_id)
    {
        CHECK_GL_ERROR();
        
        int info_log_length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        
        if (info_log_length > 0) {
            GLchar* vertex_shader_error_message = new GLchar[info_log_length];
            glGetShaderInfoLog(shader_id, info_log_length, 0, vertex_shader_error_message);
            LOG(log_level) << "Shader info log: " << vertex_shader_error_message << std::endl;
            delete[] vertex_shader_error_message;
        }
        
        CHECK_GL_ERROR();
    }
    
    void LogProgramInfoLog(bounce::LogLevel log_level, GLuint program_id)
    {
        CHECK_GL_ERROR();
        
        int info_log_length;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
        
        if (info_log_length > 0) {
            GLchar *program_error_message = new GLchar[std::max(info_log_length, 1)];
            glGetProgramInfoLog(program_id, info_log_length, 0, program_error_message);
            
            LOG(log_level) << "Shader program info log: " << program_error_message << std::endl;
            
            delete[] program_error_message;
        }
        
        CHECK_GL_ERROR();
    }
}

bounce::ShaderProgram::ShaderProgram(const ResourceLoader& resource_loader)
: resource_loader_(resource_loader)
{

}

void bounce::ShaderProgram::CreateProgram()
{
    CHECK_GL_ERROR();
    program_id_ = glCreateProgram();
    CHECK_GL_ERROR();
}

void bounce::ShaderProgram::CompileShader(GLuint shader_id, const std::string& shader_code)
{
    CHECK_GL_ERROR();
    
    GLint result = GL_FALSE;
    
    const char* source_pointer = shader_code.c_str();
    glShaderSource(shader_id, 1, &source_pointer, 0);
    glCompileShader(shader_id);
    
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    
    if (result == GL_FALSE) {
        LOG_ERROR << "Failed to compile shader" << std::endl;
        LogShaderInfoLog(LOG_LEVEL_ERROR, shader_id);
    }
    else {
        LogShaderInfoLog(LOG_LEVEL_WARNING, shader_id);
    }
    
    CHECK_GL_ERROR();
}

void bounce::ShaderProgram::LoadVertexShader(const std::string& shader_code_file_path)
{
    CHECK_GL_ERROR();
    
    vertex_shader_id_ = glCreateShader(GL_VERTEX_SHADER);
    LoadShader(shader_code_file_path, vertex_shader_id_);
    
    CHECK_GL_ERROR();
}

void bounce::ShaderProgram::LoadFragmentShader(const std::string& shader_code_file_path)
{
    CHECK_GL_ERROR();
    
    fragment_shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
    LoadShader(shader_code_file_path, fragment_shader_id_);
    
    CHECK_GL_ERROR();
}


void bounce::ShaderProgram::LoadShader(const std::string& shader_code_file_path, GLuint shader_id)
{
    CHECK_GL_ERROR();
    
    std::string shader_code = resource_loader_.LoadShaderData(shader_code_file_path);
    //shader_code = LoadShaderCode(base_path_ + "/" + shader_code_file_path);
    
    LOG_DEBUG << "Compiling shader: " << shader_code_file_path << std::endl;
    CompileShader(shader_id, shader_code);
    
    glAttachShader(program_id_, shader_id);
    
    CHECK_GL_ERROR();
}

void bounce::ShaderProgram::LinkProgram()
{
    CHECK_GL_ERROR();
    
    glLinkProgram(program_id_);
    
    GLint result = GL_FALSE;
    glGetProgramiv(program_id_, GL_LINK_STATUS, &result);
    
    if (result == GL_FALSE) {
        LOG_ERROR << "Failed to link shader program" << std::endl;
        LogProgramInfoLog(LOG_LEVEL_ERROR, program_id_);
    }
    else {
        LogProgramInfoLog(LOG_LEVEL_WARNING, program_id_);
    }
    
    glDeleteShader(vertex_shader_id_);
    glDeleteShader(fragment_shader_id_);
    
    CHECK_GL_ERROR();
}

GLint bounce::ShaderProgram::GetUniformLocation(const GLchar* uniform)
{
    GLint location = glGetUniformLocation(program_id_, uniform);

    if (location == static_cast<GLint>(GL_INVALID_INDEX)) {
        LOG_WARNING << "Invalid uniform location: " << uniform;
    }

    return location;
}

void bounce::ShaderProgram::UseProgram()
{
    glUseProgram(program_id_);
}
