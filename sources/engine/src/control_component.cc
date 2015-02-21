#include "control_component.h"

bounce::ControlComponent bounce::ControlComponent::Create(std::unique_ptr<ControlStrategy> control_strategy)
{
    return ControlComponent(std::move(control_strategy));
}

bounce::ControlComponent::ControlComponent(std::unique_ptr<ControlStrategy> control_strategy)
: GameComponent(CONTROL_COMPONENT), control_strategy_(std::move(control_strategy))
{
    
}

bounce::ControlComponent::ControlComponent(ControlComponent&& other) NOEXCEPT
    : GameComponent(std::move(other)), control_strategy_(std::move(other.control_strategy_))
{

}

void bounce::ControlComponent::Startup()
{
    
}

void bounce::ControlComponent::Shutdown()
{
    
}

void bounce::ControlComponent::Update()
{
    control_strategy_->Update();
}

std::shared_ptr<bounce::Message> bounce::ControlComponent::CreateMessage() const
{
    return control_strategy_->CreateMessage();
}
