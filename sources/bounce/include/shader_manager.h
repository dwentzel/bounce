#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#include <string>

namespace bounce {

class ShaderManager {
public:
	GLuint loadShaders(const std::string& vertexShaderFilePath,
			const std::string& fragmentShaderFilePath);

private:
	void compileShader(const int& shaderId, const std::string& shaderCode);
	std::string loadShaderCode(const std::string& shaderFilePath);
};

}
#endif
