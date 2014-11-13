#include "render_component.h"

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

void bounce::RenderComponent::Startup()
{
    render_system_->AddModel(model_handle_);
}

void bounce::RenderComponent::Shutdown()
{
    render_system_->RemoveModel(model_handle_);
}

void bounce::RenderComponent::Update()
{
//    render_system_->RenderModel(model_handle_);
}
