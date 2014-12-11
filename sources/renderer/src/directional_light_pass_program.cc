#include "directional_light_pass_program.h"

bounce::DirectionalLightPassProgram::DirectionalLightPassProgram(const ResourceLoader& resource_loader)
: LightPassProgram(resource_loader)
{
    
}

void bounce::DirectionalLightPassProgram::Init()
{
    CreateProgram();
    
    LoadVertexShader("light_pass.vert.glsl");
    LoadFragmentShader("directional_light_pass.frag.glsl");
    LinkProgram();
    
    directional_light_location_.color = GetUniformLocation("gDirectionalLight.Base.Color");
    directional_light_location_.ambient_intensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
    directional_light_location_.direction = GetUniformLocation("gDirectionalLight.Direction");
    directional_light_location_.diffuse_intensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
    
    LightPassProgram::Init();
}



void bounce::DirectionalLightPassProgram::SetDirectionalLight(const DirectionalLight& light)
{
    glUniform3f(directional_light_location_.color, light.color.x, light.color.y, light.color.z);
    glUniform1f(directional_light_location_.ambient_intensity, light.ambient_intensity);
    glm::vec3 direction = glm::normalize(light.direction);
    glUniform3fv(directional_light_location_.direction, 1, &direction[0]);
    glUniform1f(directional_light_location_.diffuse_intensity, light.diffuse_intensity);
}
