#include "ai_component.h"

bounce::AiComponent bounce::AiComponent::Create(GameEntityHandle owner, std::unique_ptr<AiStrategy> ai_strategy)
{
    return AiComponent(owner, std::move(ai_strategy));
}

bounce::AiComponent::AiComponent(GameEntityHandle owner, std::unique_ptr<AiStrategy> ai_strategy)
: GameComponent(AI_COMPONENT, owner), ai_strategy_(std::move(ai_strategy))
{

}

bounce::AiComponent::AiComponent(AiComponent&& source)
    : GameComponent(std::move(source)), ai_strategy_(std::move(source.ai_strategy_))
{

}

bounce::AiComponent::~AiComponent()  
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
    ai_strategy_->Update(*this);
}

void bounce::AiComponent::HandleMessage(const Message& message)
{
    ai_strategy_->HandleMessage(message);
}