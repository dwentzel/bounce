#include "render_component.h"

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

void bounce::RenderComponent::Startup() {

}

void bounce::RenderComponent::Shutdown() {
    
}

void bounce::RenderComponent::Update()
{
    render_system_->RenderModel(model_handle_);
}
