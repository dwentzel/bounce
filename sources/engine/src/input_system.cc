#include "input_system.h"

#include "ai_component.h"
#include "control_component.h"

bounce::InputSystem::InputSystem(const KeyboardState& keyboard_state, ObjectCache<GameEntity>& game_entities, GameComponentManager& component_manager)
: keyboard_state_(keyboard_state), game_entities_(game_entities), component_manager_(component_manager)
{
    
}

void bounce::InputSystem::Startup()
{
    
}

void bounce::InputSystem::Shutdown()
{
    
}

void bounce::InputSystem::Update(float)
{
    for (GameEntity& entity : game_entities_) {
        GameComponentHandle control_component_handle = entity.GetComponentOfType(CONTROL_COMPONENT);
        if (!control_component_handle.invalid()) {
            ControlComponent& component = component_manager_.ResolveHandleAs<ControlComponent>(control_component_handle);
            component.Update();
            
            std::shared_ptr<Message> message = component.CreateMessage();
            
//            AccelerationChangedMessage message(component.yaw_acceleration(), component.pitch_acceleration(), component.roll_acceleration(), glm::vec3(0.0f));
            entity.HandleMessage(*message);
        }
        
        GameComponentHandle ai_component_handle = entity.GetComponentOfType(AI_COMPONENT);
        if (!ai_component_handle.invalid()) {
            AiComponent& component = component_manager_.ResolveHandleAs<AiComponent>(ai_component_handle);
            component.Update();
        }
        
        //    AccelerationChangedMessage message(yaw_acceleration, pitch_acceleration, roll_acceleration, glm::vec3(0.0f));
        //
        //        SendMessage(message);
    }
}
