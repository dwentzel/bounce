#include "ai_component.h"

bounce::AiComponent bounce::AiComponent::Create(std::unique_ptr<AiStrategy> ai_strategy)
{
    return AiComponent(std::move(ai_strategy));
}

bounce::AiComponent::AiComponent(std::unique_ptr<AiStrategy> ai_strategy)
: GameComponent(AI_COMPONENT), ai_strategy_(std::move(ai_strategy))
{

}

bounce::AiComponent::AiComponent(AiComponent&& other) NOEXCEPT
    : GameComponent(std::move(other)), ai_strategy_(std::move(other.ai_strategy_))
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
