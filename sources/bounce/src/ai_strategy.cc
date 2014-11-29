#include "ai_strategy.h"
#include "object_manager.h"
#include "ai_component.h"


bounce::AiStrategy::AiStrategy(ObjectManagerHandle<AiComponent> owner)
: owner_(owner)
{
    
}

bounce::AiStrategy::~AiStrategy()
{
    
}

void bounce::AiStrategy::SendMessage(const bounce::Message& message)
{
    owner_.Resolve().SendMessage(message);
}