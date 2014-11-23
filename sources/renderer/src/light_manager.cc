#include "light_manager.h"

void bounce::LightManager::AddPointLight(const PointLight& point_light)
{
    point_lights_.push_back(point_light);
}

const std::vector<std::reference_wrapper<const bounce::PointLight>> bounce::LightManager::point_lights() const
{
    return point_lights_;
}