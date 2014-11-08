#include <fstream>
#include <iostream>
#include "bounce_gl.h"
#include "shader_manager.h"

void bounce::ShaderManager::CompileShader(const int& shader_id, const std::string& shader_code)
{
	GLint result = GL_FALSE;
	int info_log_length;

	const char* source_pointer = shader_code.c_str();
	glShaderSource(shader_id, 1, &source_pointer, 0);
	glCompileShader(shader_id);

	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	
	GLchar* vertex_shader_error_message = new GLchar[info_log_length];
	glGetShaderInfoLog(shader_id, info_log_length, 0, vertex_shader_error_message);
	fprintf(stdout, "%s\n", vertex_shader_error_message);
	delete[] vertex_shader_error_message;
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
    std::string vertex_shader_code;
    vertex_shader_code = LoadShaderCode(shader_code_file_path);
    
    LOG_DEBUG << "Compiling shader: " << shader_code_file_path << std::endl;
    CompileShader(shader_id, vertex_shader_code);
    
//    LOG_DEBUG << "Linking program\n";

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
    int info_log_length;
    glGetProgramiv(program_id_, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &info_log_length);
    
    GLchar *program_error_message = new GLchar[std::max(info_log_length, 1)];
    glGetProgramInfoLog(program_id_, info_log_length, 0, program_error_message);
    
    LOG_WARNING << "Linking program: " << program_error_message;
    //    fprintf(stdout, "%s\n", program_error_message);
    
    delete[] program_error_message;
    
    glDeleteShader(vertex_shader_id_);
    glDeleteShader(fragment_shader_id_);
}

void bounce::ShaderManager::program_id(GLuint id)
{
    program_id_ = id;
}


