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

void bounce::RenderComponent::HandleMessage(const Message& message)
{
//    if (message.message_type() == POSITION_CHANGED_MESSAGE) {
//        const PositionChangedMessage& msg = static_cast<const PositionChangedMessage&>(message);
//        light_.position = msg.position();
//    }
    
    if (message.message_type() == ORIENTATION_CHANGED_MESSAGE) {
        const OrientationChangedMessage& orientation_changed_message = static_cast<const OrientationChangedMessage&>(message);
        model_matrix_ = glm::mat4_cast(orientation_changed_message.orientation());
    }
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
