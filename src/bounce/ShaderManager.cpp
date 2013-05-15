#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "bounceGL.h"
#include "ShaderManager.h"

using namespace bounce;

void ShaderManager::compileShader(const int& shaderId, const std::string& shaderCode) {
	GLint result = GL_FALSE;
	int infoLogLength;

	const char* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, 0);
	glCompileShader(shaderId);

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
	char vertexShaderErrorMessage[infoLogLength];
	glGetShaderInfoLog(shaderId, infoLogLength, 0, vertexShaderErrorMessage);
	fprintf(stdout, "%s\n", vertexShaderErrorMessage);
}

std::string ShaderManager::loadShaderCode(const std::string& shaderFilePath) {
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
		const std::string& fragmentFilePath) {

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode;
	vertexShaderCode = loadShaderCode(vertexFilePath);
	std::cout << "vsc: " << vertexShaderCode << std::endl;

	std::string fragmentShaderCode;
	fragmentShaderCode = loadShaderCode(fragmentFilePath);
	std::cout << "fsc: " << fragmentShaderCode << std::endl;

	std::cout << "Compiling shader: " << vertexFilePath << std::endl;
	compileShader(vertexShaderId, vertexShaderCode);

	std::cout << "Compiling shader: " << fragmentFilePath << std::endl;
	compileShader(fragmentShaderId, fragmentShaderCode);

	std::cout << "Linking program\n";
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	GLint result = GL_FALSE;
	int infoLogLength;
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
	char programErrorMessage[std::max(infoLogLength, 1)];
	glGetProgramInfoLog(programId, infoLogLength, 0, programErrorMessage);
	fprintf(stdout, "%s\n", programErrorMessage);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;

	return 0;
}
