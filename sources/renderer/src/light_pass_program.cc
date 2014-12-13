#include "light_pass_program.h"

bounce::LightPassProgram::LightPassProgram(const ResourceLoader& resource_loader)
: ShaderProgram(resource_loader)
{
    
}

void bounce::LightPassProgram::Init()
{
    VP_location_ = GetUniformLocation("VP");
    position_texture_unit_location_ = GetUniformLocation("gPositionMap");
    color_texture_unit_location_ = GetUniformLocation("gColorMap");
    normal_texture_unit_location_ = GetUniformLocation("gNormalMap");
    eye_world_position_location_ = GetUniformLocation("gEyeWorldPos");
    material_specular_intensity_location_ = GetUniformLocation("gMatSpecularIntensity");
    material_specular_power_location_ = GetUniformLocation("gSpecularPower");
    screen_size_location_ = GetUniformLocation("gScreenSize");
    
}

void bounce::LightPassProgram::SetVP(const glm::mat4& VP)
{
    glUniformMatrix4fv(VP_location_, 1, GL_TRUE, &VP[0][0]);
}

void bounce::LightPassProgram::SetPositionTextureUnit(int texture_unit)
{
    glUniform1i(position_texture_unit_location_, texture_unit);
}

void bounce::LightPassProgram::SetColorTextureUnit(int texture_unit)
{
    glUniform1i(color_texture_unit_location_, texture_unit);
}

void bounce::LightPassProgram::SetNormalTextureUnit(int texture_unit)
{
    glUniform1i(normal_texture_unit_location_, texture_unit);
}

void bounce::LightPassProgram::SetEyeWorldPos(const glm::vec3& eye_position)
{
    glUniform3f(eye_world_position_location_, eye_position.x, eye_position.y, eye_position.z);
}

void bounce::LightPassProgram::SetScreenSize(unsigned int width, unsigned int height)
{
    glUniform2f(screen_size_location_, static_cast<float>(width), static_cast<float>(height));
}
