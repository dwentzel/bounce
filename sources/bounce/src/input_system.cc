#include "input_system.h"

bounce::InputSystem::InputSystem(const KeyboardState& keyboard_state, ControlComponentCache& control_components, AiComponentCache& ai_components)
: keyboard_state_(keyboard_state), control_components_(control_components), ai_components_(ai_components)
{
    
}

void bounce::InputSystem::Startup()
{
    
}

void bounce::InputSystem::Shutdown()
{
    
}

void bounce::InputSystem::Update(float delta_time)
{
    for (ControlComponent& component : control_components_) {
        component.Update();
    }
    
    for (AiComponent& component : ai_components_) {
        component.Update();
    }
}