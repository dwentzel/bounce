#include "shader_program.h"

#include <fstream>

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



bounce::ShaderProgram::ShaderProgram(GLuint program_id)
: program_id_(program_id)
{
    
}

void bounce::ShaderProgram::CompileShader(const int& shader_id, const std::string& shader_code)
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

std::string bounce::ShaderProgram::LoadShaderCode(const std::string& shaderFilePath)
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

void bounce::ShaderProgram::LoadVertexShader(const std::string& shader_code_file_path)
{
    vertex_shader_id_ = glCreateShader(GL_VERTEX_SHADER);
    LoadShader(shader_code_file_path, vertex_shader_id_);
}

void bounce::ShaderProgram::LoadFragmentShader(const std::string& shader_code_file_path)
{
    fragment_shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
    LoadShader(shader_code_file_path, fragment_shader_id_);
}


void bounce::ShaderProgram::LoadShader(const std::string& shader_code_file_path, GLuint shader_id)
{
    std::string shader_code;
    shader_code = LoadShaderCode(shader_code_file_path);
    
    LOG_DEBUG << "Compiling shader: " << shader_code_file_path << std::endl;
    CompileShader(shader_id, shader_code);
    CHECK_GL_ERROR();
    
    glAttachShader(program_id_, shader_id);
    CHECK_GL_ERROR();
}

void bounce::ShaderProgram::LinkProgram()
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

void bounce::ShaderProgram::UseProgram()
{
    glUseProgram(program_id_);
}

void bounce::ShaderProgram::LoadUniforms()
{
    mvp_matrix_id_ = glGetUniformLocation(program_id_, "MVP");
    view_matrix_id_ = glGetUniformLocation(program_id_, "V");
    model_matrix_id_ = glGetUniformLocation(program_id_, "M");
    
    light_count_location_ = glGetUniformLocation(program_id_, "LightCount");
    
    light_position_id_ = glGetUniformLocation(program_id_, "LightPosition_worldspace");
    
    material_locations_.diffuse_id = glGetUniformLocation(program_id_, "Material_diffuse");
    material_locations_.ambient_id = glGetUniformLocation(program_id_, "Material_ambient");
    material_locations_.specular_id = glGetUniformLocation(program_id_, "Material_specular");
    material_locations_.emissive_id = glGetUniformLocation(program_id_, "Material_emissive");
    material_locations_.shininess_id = glGetUniformLocation(program_id_, "Material_shininess");
    
//    struct DirectionalLight {
//        vec3 color;
//        float diffuse_intensity;
//        float ambient_intensity;
//    };
//    
//    uniform DirectionalLight directionalLights[10];
    
    for (int i = 0; i < 10; ++i) {
        std::stringstream oss;
        oss << "[" << i << "]";
        std::string index(oss.str());
        
        light_location_[i].position = glGetUniformLocation(program_id_, ("LightPosition_worldspace" + index).c_str());
//        light_location_[i].direction = glGetUniformLocation(program_id_, ("directionalLights" + index + ".direction").c_str());
        light_location_[i].color = glGetUniformLocation(program_id_, ("directionalLights" + index + ".color").c_str());
        light_location_[i].diffuse_intensity = glGetUniformLocation(program_id_, ("directionalLights" + index + ".diffuse_intensity").c_str());
        light_location_[i].ambient_intensity = glGetUniformLocation(program_id_, ("directionalLights" + index + ".ambient_intensity").c_str());
    }
}

//void bounce::ShaderProgram::SetLightPosition(const float* light_position_data)
//{
//    glUniform3fv(light_position_id_, 1, light_position_data);
//}

void bounce::ShaderProgram::SetLightCount(unsigned int light_count)
{
    glUniform1i(light_count_location_, light_count);
}

void bounce::ShaderProgram::SetLight(unsigned int index, const struct DirectionalLight& light)
{
    glUniform3fv(light_location_[index].position, 1, &light.position[0]);
    glUniform3fv(light_location_[index].color, 1, &light.color[0]);
    glUniform1f(light_location_[index].ambient_intensity, light.ambient_intensity);
    glUniform1f(light_location_[index].diffuse_intensity, light.diffuse_intensity);
}

void bounce::ShaderProgram::SetViewMatrix(const float* view_matrix)
{
    glUniformMatrix4fv(view_matrix_id_, 1, GL_FALSE, view_matrix);
}

void bounce::ShaderProgram::SetModelMatrix(const float* model_matrix)
{
    glUniformMatrix4fv(model_matrix_id_, 1, GL_FALSE, model_matrix);
}

void bounce::ShaderProgram::SetMVPMatrix(const float* mvp_matrix)
{
    glUniformMatrix4fv(mvp_matrix_id_, 1, GL_FALSE, mvp_matrix);
}

void bounce::ShaderProgram::SetMaterial(const bounce::Material &material)
{
    glUniform3fv(material_locations_.diffuse_id, 1, material.diffuse());
    glUniform3fv(material_locations_.ambient_id, 1, material.ambient());
    glUniform3fv(material_locations_.specular_id, 1, material.specular());
    glUniform3fv(material_locations_.emissive_id, 1, material.emissive());
    glUniform1f(material_locations_.shininess_id, material.shininess());
}
