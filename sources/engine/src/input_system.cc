#include "input_system.h"

bounce::InputSystem::InputSystem(const KeyboardState& keyboard_state, GameEntityCache& game_entities)
: keyboard_state_(keyboard_state), game_entities_(game_entities)
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
        if (control_component_handle.index() > -1) {
            ControlComponent& component = control_component_handle.ResolveAs<ControlComponent>();
            component.Update();
        }

        GameComponentHandle ai_component_handle = entity.GetComponentOfType(AI_COMPONENT);
        if (ai_component_handle.index() > -1) {
            AiComponent& component = ai_component_handle.ResolveAs<AiComponent>();
            component.Update();
        }
    }
    
//    for (ControlComponent& component : control_components_) {
//        component.Update();
//    }
//    
//    for (AiComponent& component : ai_components_) {
//        component.Update();
//    }
}
