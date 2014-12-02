#include "ai_strategy.h"
#include "object_manager.h"
#include "ai_component.h"

//bounce::AiStrategy::AiStrategy()
//{
//    
//}

bounce::AiStrategy::~AiStrategy()
{
    
}

void bounce::AiStrategy::SendMessage(const AiComponent& owner, const bounce::Message& message)
{
    owner.SendMessage(message);
}