#include <string>
#include <fstream>
#include "bounceGL.h"

GLuint LoadShaders(const char* vertexFilePath, const char* fragmentFilePath) {

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);

	if (vertexShaderStream.is_open()) {
		std::string line = "";
		while (getline(vertexShaderStream, line)) {
			vertexShaderCode += "\n" + line;
		}
		vertexShaderStream.close();
	}

	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);

	if (fragmentShaderStream.is_open()) {
		std::string line = "";
		while (getline(fragmentShaderStream, line)) {
			fragmentShaderCode = "\n" + line;
		}
		fragmentShaderStream.close();
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	return 0;
}
