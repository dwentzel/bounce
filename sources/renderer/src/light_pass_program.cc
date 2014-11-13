#include "light_pass_program.h"


void bounce::LightPassProgram::Init()
{
    WVP_location_ = GetUniformLocation("WVP");
    position_texture_unit_location_ = GetUniformLocation("gPositionMap");
    color_texture_unit_location_ = GetUniformLocation("gColorMap");
    normal_texture_unit_location_ = GetUniformLocation("gNormalMap");
    eye_world_position_location_ = GetUniformLocation("gEyeWorldPos");
    mat_specular_intensity_location_ = GetUniformLocation("gMatSpecularIntensity");
    mat_specular_power_location_ = GetUniformLocation("gSpecularPower");
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
    
//    return true;
}


void bounce::LightPassProgram::SetWVP(const float* WVP)
{
    glUniformMatrix4fv(WVP_location_, 1, GL_TRUE, (const GLfloat*)WVP);
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


void bounce::LightPassProgram::SetEyeWorldPos(const float* eye_position)
{
    glUniform3fv(eye_world_position_location_, 1, (const GLfloat*)eye_position);
}


void bounce::LightPassProgram::SetScreenSize(unsigned int width, unsigned int height)
{
    glUniform2f(screen_size_location_, (float)width, (float)height);
}