#include "light_pass_program.h"

bool bounce::LightPassProgram::Init()
{
    WVP_location_ = GetUniformLocation("gWVP");
    position_texture_unit_location_ = GetUniformLocation("gPositionMap");
    color_texture_unit_location_ = GetUniformLocation("gColorMap");
    normal_texture_unit_location_ = GetUniformLocation("gNormalMap");
    eye_world_position_location_ = GetUniformLocation("gEyeWorldPos");
    material_specular_intensity_location_ = GetUniformLocation("gMatSpecularIntensity");
    material_specular_power_location_ = GetUniformLocation("gSpecularPower");
    screen_size_location_ = GetUniformLocation("gScreenSize");
    
//    if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
//        m_posTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
//        m_colorTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
//        m_normalTextureUnitLocation == INVALID_UNIFORM_LOCATION ||
//        m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
//        m_matSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
//        m_matSpecularPowerLocation == INVALID_UNIFORM_LOCATION ||
//        m_screenSizeLocation == INVALID_UNIFORM_LOCATION) {
//        return false;
//    }
    
    return true;
}


void bounce::LightPassProgram::SetWVP(const glm::mat4& WVP)
{
    glUniformMatrix4fv(WVP_location_, 1, GL_TRUE, &WVP[0][0]);
}


void bounce::LightPassProgram::SetPositionTextureUnit(unsigned int texture_unit)
{
    glUniform1i(position_texture_unit_location_, texture_unit);
}


void bounce::LightPassProgram::SetColorTextureUnit(unsigned int texture_unit)
{
    glUniform1i(color_texture_unit_location_, texture_unit);
}


void bounce::LightPassProgram::SetNormalTextureUnit(unsigned int texture_unit)
{
    glUniform1i(normal_texture_unit_location_, texture_unit);
}


void bounce::LightPassProgram::SetEyeWorldPos(const glm::vec3& eye_position)
{
    glUniform3f(eye_world_position_location_, eye_position.x, eye_position.y, eye_position.z);
}


void bounce::LightPassProgram::SetScreenSize(unsigned int width, unsigned int height)
{
    glUniform2f(screen_size_location_, (float)width, (float)height);
}