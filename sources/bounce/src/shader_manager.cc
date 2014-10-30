#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "bounce_gl.h"
#include "shader_manager.h"

using namespace bounce;

void ShaderManager::compileShader(const int& shaderId, const std::string& shaderCode)
{
	GLint result = GL_FALSE;
	int infoLogLength;

	const char* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, 0);
	glCompileShader(shaderId);

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
	
	GLchar* vertexShaderErrorMessage = new GLchar[infoLogLength];
	glGetShaderInfoLog(shaderId, infoLogLength, 0, vertexShaderErrorMessage);
	fprintf(stdout, "%s\n", vertexShaderErrorMessage);
	delete[] vertexShaderErrorMessage;
}

std::string ShaderManager::loadShaderCode(const std::string& shaderFilePath)
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

GLuint ShaderManager::loadShaders(const std::string& vertexFilePath,
		const std::string& fragmentFilePath)
{

	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertex_shader_code;
	vertex_shader_code = loadShaderCode(vertexFilePath);
	//std::cout << "vsc: " << vertexShaderCode << std::endl;

	std::string fragment_shader_code;
	fragment_shader_code = loadShaderCode(fragmentFilePath);
	//std::cout << "fsc: " << fragmentShaderCode << std::endl;

	std::cout << "Compiling shader: " << vertexFilePath << std::endl;
	compileShader(vertex_shader_id, vertex_shader_code);
    
	std::cout << "Compiling shader: " << fragmentFilePath << std::endl;
	compileShader(fragment_shader_id, fragment_shader_code);
    
	std::cout << "Linking program\n";
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
	fprintf(stdout, "%s\n", program_error_message);
	delete[] program_error_message;

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	return program_id;
}
