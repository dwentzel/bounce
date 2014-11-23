#include "point_light_component.h"

bounce::PointLightComponent::PointLightComponent(LightManager& light_manager, const PointLight& point_light)
: GameComponent(POINT_LIGHT_COMPONENT), light_manager_(light_manager)
{
    point_light_.color = glm::vec3(point_light.color);
    point_light_.ambient_intensity = point_light.ambient_intensity;
    point_light_.diffuse_intensity = point_light.diffuse_intensity;
    
    point_light_.position = glm::vec3(point_light.position);
    point_light_.attenuation.constant = point_light.attenuation.constant;
    point_light_.attenuation.linear = point_light.attenuation.linear;
    point_light_.attenuation.exp = point_light.attenuation.exp;
}

void bounce::PointLightComponent::Startup()
{
    light_manager_.AddPointLight(point_light_);
}

void bounce::PointLightComponent::Shutdown()
{
    
}

void bounce::PointLightComponent::Update()
{
    
}