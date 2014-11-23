#include "light_manager.h"

//void bounce::LightManager::AddPointLight(const PointLight& point_light)
//{
//    point_lights_.push_back(point_light);
//}

unsigned int bounce::LightManager::GenerateLight()
{
    unsigned int handle = point_lights_.size();
    
    PointLight point_light;
    
    point_lights_.push_back(point_light);
    
    return handle;
}

bounce::PointLight& bounce::LightManager::GetLight(unsigned int handle)
{
    return point_lights_[handle];
}

const std::vector<bounce::PointLight> bounce::LightManager::point_lights() const
{
    return point_lights_;
}