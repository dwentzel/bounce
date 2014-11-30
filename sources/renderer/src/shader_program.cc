#include "shader_program.h"

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

//std::string bounce::ShaderProgram::base_path_;
//
//void bounce::ShaderProgram::base_path(const std::string& path)
//{
//    ShaderProgram::base_path_ = path;
//}

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

void bounce::ShaderProgram::CompileShader(const int& shader_id, const std::string& shader_code)
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

//std::string bounce::ShaderProgram::LoadShaderCode(const std::string& shaderFilePath)
//{
//    std::string shaderCode;
//    std::ifstream shaderStream(shaderFilePath, std::ios::in);
//    
//    if (shaderStream.is_open()) {
//        std::string line = "";
//        while (getline(shaderStream, line)) {
//            shaderCode += line + "\n";
//        }
//        shaderStream.close();
//    }
//    else {
//        LOG_ERROR << "Could not find file " << shaderFilePath << std::endl;
//    }
//    
//    return shaderCode;
//}

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
    return glGetUniformLocation(program_id_, uniform);
}

void bounce::ShaderProgram::UseProgram()
{
    glUseProgram(program_id_);
}

//void bounce::ShaderProgram::LoadUniforms()
//{
//    CHECK_GL_ERROR();
//    mwvp_matrix_id_ = glGetUniformLocation(program_id_, "MWVP");
//    wvp_matrix_id_ = glGetUniformLocation(program_id_, "WVP");
//    view_matrix_id_ = glGetUniformLocation(program_id_, "V");
//    world_matrix_id_ = glGetUniformLocation(program_id_, "W");
//    model_matrix_id_ = glGetUniformLocation(program_id_, "M");
//    //
//    //    light_count_location_ = glGetUniformLocation(program_id_, "LightCount");
//    //
//    //    light_position_id_ = glGetUniformLocation(program_id_, "LightPosition_worldspace");
//    //
//    //    material_locations_.diffuse_id = glGetUniformLocation(program_id_, "Material_diffuse");
//    //    material_locations_.ambient_id = glGetUniformLocation(program_id_, "Material_ambient");
//    //    material_locations_.specular_id = glGetUniformLocation(program_id_, "Material_specular");
//    //    material_locations_.emissive_id = glGetUniformLocation(program_id_, "Material_emissive");
//    //    material_locations_.shininess_id = glGetUniformLocation(program_id_, "Material_shininess");
//    //
//    ////    struct DirectionalLight {
//    ////        vec3 color;
//    ////        float diffuse_intensity;
//    ////        float ambient_intensity;
//    ////    };
//    ////
//    ////    uniform DirectionalLight directionalLights[10];
//    //
//    //    for (int i = 0; i < 10; ++i) {
//    //        std::stringstream oss;
//    //        oss << "[" << i << "]";
//    //        std::string index(oss.str());
//    //
//    //        light_location_[i].position = glGetUniformLocation(program_id_, ("LightPosition_worldspace" + index).c_str());
//    ////        light_location_[i].direction = glGetUniformLocation(program_id_, ("directionalLights" + index + ".direction").c_str());
//    //        light_location_[i].color = glGetUniformLocation(program_id_, ("directionalLights" + index + ".color").c_str());
//    //        light_location_[i].diffuse_intensity = glGetUniformLocation(program_id_, ("directionalLights" + index + ".diffuse_intensity").c_str());
//    //        light_location_[i].ambient_intensity = glGetUniformLocation(program_id_, ("directionalLights" + index + ".ambient_intensity").c_str());
//    //    }
//    
//    CHECK_GL_ERROR();
//}

//void bounce::ShaderProgram::SetLightPosition(const float* light_position_data)
//{
//    glUniform3fv(light_position_id_, 1, light_position_data);
//}

void bounce::ShaderProgram::SetLightCount(unsigned int light_count)
{
    //    glUniform1i(light_count_location_, light_count);
}

void bounce::ShaderProgram::SetLight(unsigned int index, const struct DirectionalLight& light)
{
    //    glUniform3fv(light_location_[index].position, 1, &light.position[0]);
    //    glUniform3fv(light_location_[index].color, 1, &light.color[0]);
    //    glUniform1f(light_location_[index].ambient_intensity, light.ambient_intensity);
    //    glUniform1f(light_location_[index].diffuse_intensity, light.diffuse_intensity);
}



void bounce::ShaderProgram::SetMaterial(const bounce::Material &material)
{
    //    glUniform3fv(material_locations_.diffuse_id, 1, material.diffuse());
    //    glUniform3fv(material_locations_.ambient_id, 1, material.ambient());
    //    glUniform3fv(material_locations_.specular_id, 1, material.specular());
    //    glUniform3fv(material_locations_.emissive_id, 1, material.emissive());
    //    glUniform1f(material_locations_.shininess_id, material.shininess());
}
