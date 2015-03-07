#include "input_system.h"

#include "control_component.h"

bounce::InputSystem::InputSystem(const KeyboardState& keyboard_state,
                                 ObjectCache<GameEntity>& game_entities,
                                 GameComponentManager& component_manager)
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
        
        if (control_component_handle.is_valid()) {
            ControlComponent& component = component_manager_.ResolveHandleAs<ControlComponent>(control_component_handle);
            component.Update();
            
            std::unique_ptr<Message> message = component.CreateMessage();
            
            entity.HandleMessage(*message);
        }
    }
}
