#include "render_component.h"
#include "render_system.h"

bounce::RenderComponent bounce::RenderComponent::Create(unsigned int model_handle)
{
    return RenderComponent(model_handle);
}

bounce::RenderComponent::RenderComponent(unsigned int model_handle)
: GameComponent(RENDER_COMPONENT), model_handle_(model_handle), model_matrix_(glm::mat4(1.0f))
{
}

bounce::RenderComponent::RenderComponent(RenderComponent&& source)
: GameComponent(std::move(source)),
  model_handle_(std::move(source.model_handle_)), model_matrix_(std::move(source.model_matrix_))
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

void bounce::RenderComponent::HandleMessage(const Message&)
{
}

void bounce::RenderComponent::Startup()
{
}

void bounce::RenderComponent::Shutdown()
{
}

void bounce::RenderComponent::Update()
{
}
