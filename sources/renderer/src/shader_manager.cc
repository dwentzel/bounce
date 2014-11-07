#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "bounce/bounce_gl.h"
#include "shader_manager.h"

using namespace bounce;

void ShaderManager::CompileShader(const int& shader_id, const std::string& shader_code)
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

std::string ShaderManager::LoadShaderCode(const std::string& shaderFilePath)
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

GLuint ShaderManager::LoadShaders(const std::string& vertexFilePath,
		const std::string& fragmentFilePath)
{

	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertex_shader_code;
	vertex_shader_code = LoadShaderCode(vertexFilePath);
	//std::cout << "vsc: " << vertexShaderCode << std::endl;

	std::string fragment_shader_code;
	fragment_shader_code = LoadShaderCode(fragmentFilePath);
	//std::cout << "fsc: " << fragmentShaderCode << std::endl;

	LOG_DEBUG << "Compiling shader: " << vertexFilePath << std::endl;
	CompileShader(vertex_shader_id, vertex_shader_code);
    
	LOG_DEBUG << "Compiling shader: " << fragmentFilePath << std::endl;
	CompileShader(fragment_shader_id, fragment_shader_code);
    
	LOG_DEBUG << "Linking program\n";
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);
    ASSERT_NO_GL_ERROR();
    
	GLint result = GL_FALSE;
	int info_log_length;
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
	
	GLchar *program_error_message = new GLchar[std::max(info_log_length, 1)];
	glGetProgramInfoLog(program_id, info_log_length, 0, program_error_message);

    LOG_WARNING << "Linking program: " << program_error_message;
//    fprintf(stdout, "%s\n", program_error_message);
	
    delete[] program_error_message;

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return program_id;
}
