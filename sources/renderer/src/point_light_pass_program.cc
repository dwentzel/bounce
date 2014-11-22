#include "point_light_pass_program.h"

bool bounce::PointLightPassProgram::Init()
{
    CreateProgram();
    
    LoadVertexShader("light_pass.vert.glsl");
    LoadFragmentShader("point_light_pass.frag.glsl");
    LinkProgram();
    
    point_light_location_.color = GetUniformLocation("gPointLight.Base.Color");
    point_light_location_.ambient_intensity = GetUniformLocation("gPointLight.Base.AmbientIntensity");
    point_light_location_.position = GetUniformLocation("gPointLight.Position");
    point_light_location_.diffuse_intensity = GetUniformLocation("gPointLight.Base.DiffuseIntensity");
    point_light_location_.attenuation.constant = GetUniformLocation("gPointLight.Atten.Constant");
    point_light_location_.attenuation.linear = GetUniformLocation("gPointLight.Atten.Linear");
    point_light_location_.attenuation.exp = GetUniformLocation("gPointLight.Atten.Exp");
    
//    if (point_light_location_.Color == INVALID_UNIFORM_LOCATION ||
//        point_light_location_.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
//        point_light_location_.Position == INVALID_UNIFORM_LOCATION ||
//        point_light_location_.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
//        point_light_location_.Atten.Constant == INVALID_UNIFORM_LOCATION ||
//        point_light_location_.Atten.Linear == INVALID_UNIFORM_LOCATION ||
//        point_light_location_.Atten.Exp == INVALID_UNIFORM_LOCATION) {
//        return false;
//    }
    
    return LightPassProgram::Init();
}


void bounce::PointLightPassProgram::SetPointLight(const PointLight& light)
{
    glUniform3f(point_light_location_.color, light.color.x, light.color.y, light.color.z);
    glUniform1f(point_light_location_.ambient_intensity, light.ambient_intensity);
    glUniform1f(point_light_location_.diffuse_intensity, light.diffuse_intensity);
    glUniform3f(point_light_location_.position, light.position.x, light.position.y, light.position.z);
    glUniform1f(point_light_location_.attenuation.constant, light.attenuation.constant);
    glUniform1f(point_light_location_.attenuation.linear, light.attenuation.linear);
    glUniform1f(point_light_location_.attenuation.exp, light.attenuation.exp);
}