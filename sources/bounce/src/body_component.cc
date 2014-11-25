#include "body_component.h"

bounce::BodyComponent::BodyComponent()
: GameComponent(BODY_COMPONENT),
  yaw_acceleration_direction_(0), pitch_acceleration_direction_(0), roll_acceleration_direction_(0),
  rotation_acceleration_(0.0002f), max_speed_(0.1f), yaw_speed_(0.0f), pitch_speed_(0.0f), roll_speed_(0.0f),
  orientation_(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
{
    
}

bounce::BodyComponent bounce::BodyComponent::Create()
{
    return BodyComponent();
}


void bounce::BodyComponent::Startup()
{
    
}

void bounce::BodyComponent::Shutdown()
{
    
}

void bounce::BodyComponent::Update()
{
    
}