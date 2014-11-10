#include <fstream>
#include <iostream>
#include "bounce_gl.h"
#include "shader_manager.h"

namespace {
    
    void LogShaderInfoLog(bounce::LogLevel log_level, GLuint shader_id)
    {
        int info_log_length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        
        if (info_log_length > 0) {
            GLchar* vertex_shader_error_message = new GLchar[info_log_length];
            glGetShaderInfoLog(shader_id, info_log_length, 0, vertex_shader_error_message);
            LOG(log_level) << "Shader info log: " << vertex_shader_error_message << std::endl;
            delete[] vertex_shader_error_message;
        }
    }
    
    void LogProgramInfoLog(bounce::LogLevel log_level, GLuint program_id)
    {
        int info_log_length;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
        
        if (info_log_length > 0) {
            GLchar *program_error_message = new GLchar[std::max(info_log_length, 1)];
            glGetProgramInfoLog(program_id, info_log_length, 0, program_error_message);
            
            LOG(log_level) << "Shader program info log: " << program_error_message << std::endl;
            
            delete[] program_error_message;
        }
    }
}

void bounce::ShaderManager::CompileShader(const int& shader_id, const std::string& shader_code)
{
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
    
    
}

std::string bounce::ShaderManager::LoadShaderCode(const std::string& shaderFilePath)
{
    std::string shaderCode;
    std::ifstream shaderStream(shaderFilePath, std::ios::in);
    
    if (shaderStream.is_open()) {
        std::string line = "";
        while (getline(shaderStream, line)) {
            shaderCode += line + "\n";
        }
        shaderStream.close();
    }
    
    return shaderCode;
}

void bounce::ShaderManager::LoadVertexShader(const std::string& shader_code_file_path)
{
    vertex_shader_id_ = glCreateShader(GL_VERTEX_SHADER);
    LoadShader(shader_code_file_path, vertex_shader_id_);
}

void bounce::ShaderManager::LoadFragmentShader(const std::string& shader_code_file_path)
{
    fragment_shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
    LoadShader(shader_code_file_path, fragment_shader_id_);
}


void bounce::ShaderManager::LoadShader(const std::string& shader_code_file_path, GLuint shader_id)
{
    std::string shader_code;
    shader_code = LoadShaderCode(shader_code_file_path);
    
    LOG_DEBUG << "Compiling shader: " << shader_code_file_path << std::endl;
    CompileShader(shader_id, shader_code);
    CHECK_GL_ERROR();
    
    glAttachShader(program_id_, shader_id);
    CHECK_GL_ERROR();
}

void bounce::ShaderManager::LinkProgram()
{
    ASSERT_NO_GL_ERROR();
    
    glLinkProgram(program_id_);
    ASSERT_NO_GL_ERROR();
    
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
}

void bounce::ShaderManager::program_id(GLuint id)
{
    program_id_ = id;
}


