#include "point_light_component.h"

bounce::PointLightComponent::PointLightComponent(LightManager& light_manager,
                                                 float ambient_intensity,
                                                 float diffuse_intensity,
                                                 float constant_attenuation,
                                                 float linear_attenuation,
                                                 float exp_attenuation,
                                                 glm::vec3 color)
: GameComponent(POINT_LIGHT_COMPONENT), light_manager_(light_manager),
  ambient_intensity_(ambient_intensity), diffuse_intensity_(diffuse_intensity),
  constant_attenuation_(constant_attenuation), linear_attenuation_(linear_attenuation), exp_attenuation_(exp_attenuation),
  color_(color)
{
    
    
}

void bounce::PointLightComponent::Startup()
{
    handle_ = light_manager_.GenerateLight();

    PointLight& light = light_manager_.GetLight(handle_);
    
    light.position = glm::vec3(0.0f);
    light.ambient_intensity = ambient_intensity_;
    light.diffuse_intensity = diffuse_intensity_;
    light.color = glm::vec3(color_);
    light.attenuation.constant = constant_attenuation_;
    light.attenuation.linear = linear_attenuation_;
    light.attenuation.exp = exp_attenuation_;
}

void bounce::PointLightComponent::Shutdown()
{
    
}

void bounce::PointLightComponent::Update()
{

}

void bounce::PointLightComponent::HandleMessage(const Message& message)
{
    if (message.message_type() == POSITION_CHANGED_MESSAGE) {
        const PositionChangedMessage& msg = static_cast<const PositionChangedMessage&>(message);
        PointLight& light = light_manager_.GetLight(handle_);
        light.position = msg.position();
    }
}