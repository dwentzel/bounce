#include "render_component.h"
#include "render_system.h"

bounce::RenderComponent bounce::RenderComponent::Create(unsigned int model_handle)
{
    return RenderComponent(model_handle);
}

bounce::RenderComponent::RenderComponent(unsigned int model_handle)
: GameComponent(RENDER_COMPONENT), model_handle_(model_handle), model_matrix_(glm::mat4(1.f))
{
}

unsigned int bounce::RenderComponent::model_handle() const
{
    return model_handle_;
}

const glm::mat4& bounce::RenderComponent::model_matrix() const
{
    return model_matrix_;
}

void bounce::RenderComponent::HandleMessage(const bounce::Message& message)
{
    
}

void bounce::RenderComponent::Startup()
{
    //render_system_.AddModel(model_handle_);
}

void bounce::RenderComponent::Shutdown()
{
    //render_system_.RemoveModel(model_handle_);
}

void bounce::RenderComponent::Update()
{
    //render_system_.RenderModel(model_handle_);
}
