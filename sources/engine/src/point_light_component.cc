#include "point_light_component.h"

#include <algorithm>

bounce::PointLightComponent bounce::PointLightComponent::Create()
{
    return PointLightComponent();
}

bounce::PointLightComponent::PointLightComponent()
: GameComponent(POINT_LIGHT_COMPONENT), model_matrix_(glm::mat4(1.0f))
{
    
}

bounce::PointLightComponent::PointLightComponent(PointLightComponent&& other) NOEXCEPT
    : GameComponent(std::move(other)), light_(std::move(other.light_)), model_matrix_(std::move(other.model_matrix_))
{

}

bounce::PointLightComponent::~PointLightComponent()
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
