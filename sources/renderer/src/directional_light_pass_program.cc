#include "directional_light_pass_program.h"

void bounce::DirectionalLightPassProgram::Init()
{
    ShaderProgram::Init();
    
    LoadVertexShader("light_pass.vert.glsl");
    LoadFragmentShader("dir_light_pass.frag.glsl");
    LinkProgram();
    
    directional_light_location_.color = GetUniformLocation("gDirectionalLight.Base.Color");
    directional_light_location_.ambient_intensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
    directional_light_location_.direction = GetUniformLocation("gDirectionalLight.Direction");
    
    directional_light_location_.diffuse_intensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
    
//    if (directional_light_location_.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
//        directional_light_location_.Color == INVALID_UNIFORM_LOCATION ||
//        directional_light_location_.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
//        directional_light_location_.Direction == INVALID_UNIFORM_LOCATION) {
//        return false;
//    }
//    
//    return DSLightPassTech::Init();
    
    LightPassProgram::Init();
}



void bounce::DirectionalLightPassProgram::SetDirectionalLight(const DirectionalLight& light)
{
    glUniform3f(directional_light_location_.color, light.color.x, light.color.y, light.color.z);
    glUniform1f(directional_light_location_.ambient_intensity, light.ambient_intensity);
    glm::vec3 direction = light.direction;
    
    glm::normalize(direction);
    glUniform3f(directional_light_location_.direction, direction.x, direction.y, direction.z);
    glUniform1f(directional_light_location_.diffuse_intensity, light.diffuse_intensity);
}