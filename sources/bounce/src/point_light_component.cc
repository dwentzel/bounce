#include "point_light_component.h"

bounce::PointLightComponent bounce::PointLightComponent::Create()
{
    return PointLightComponent();
}

bounce::PointLightComponent::PointLightComponent()
: GameComponent(POINT_LIGHT_COMPONENT), model_matrix_(glm::mat4(1.0f))
//,
//  ambient_intensity_(0.0f), diffuse_intensity_(0.0f),
//  constant_attenuation_(0.0f), linear_attenuation_(0.0f), exp_attenuation_(0.0f),
//  color_(glm::vec3(0.0f, 0.0f, 0.0f))
{
    
}

void bounce::PointLightComponent::Startup()
{

//    PointLight& light = light_manager_.GetLight(handle_);
//    
//    light.position = glm::vec3(0.0f);
//    light.ambient_intensity = ambient_intensity_;
//    light.diffuse_intensity = diffuse_intensity_;
//    light.color = glm::vec3(color_);
//    light.attenuation.constant = constant_attenuation_;
//    light.attenuation.linear = linear_attenuation_;
//    light.attenuation.exp = exp_attenuation_;
}

void bounce::PointLightComponent::Shutdown()
{
    
}

void bounce::PointLightComponent::Update()
{

}

void bounce::PointLightComponent::HandleMessage(const Message& message)
{
//    if (message.message_type() == POSITION_CHANGED_MESSAGE) {
//        const PositionChangedMessage& msg = static_cast<const PositionChangedMessage&>(message);
//        PointLight& light = light_manager_.GetLight(handle_);
//        light.position = msg.position();
//    }
}