#include "point_light_component.h"

bounce::PointLightComponent bounce::PointLightComponent::Create(GameEntityHandle owner)
{
    return PointLightComponent(owner);
}

bounce::PointLightComponent::PointLightComponent(GameEntityHandle owner)
: GameComponent(POINT_LIGHT_COMPONENT, owner), model_matrix_(glm::mat4(1.0f))
//,
//  ambient_intensity_(0.0f), diffuse_intensity_(0.0f),
//  constant_attenuation_(0.0f), linear_attenuation_(0.0f), exp_attenuation_(0.0f),
//  color_(glm::vec3(0.0f, 0.0f, 0.0f))
{
    
}

void bounce::PointLightComponent::Startup()
{

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
        light_.position = msg.position();
    }
}