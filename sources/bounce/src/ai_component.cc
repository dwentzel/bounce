#include "ai_component.h"

bounce::AiComponent bounce::AiComponent::Create(GameEntityHandle owner)
{
    return AiComponent(owner);
}

bounce::AiComponent::AiComponent(GameEntityHandle owner)
: GameComponent(AI_COMPONENT, owner)
{

}

void bounce::AiComponent::Startup()
{
    
}

void bounce::AiComponent::Shutdown()
{
    
}

void bounce::AiComponent::Update()
{
    ai_strategy_->Update();
}

void bounce::AiComponent::SetStrategy(std::unique_ptr<AiStrategy> ai_strategy)
{
    ai_strategy_ = std::move(ai_strategy);
}

void bounce::AiComponent::HandleMessage(const Message& message)
{
    ai_strategy_->HandleMessage(message);
}