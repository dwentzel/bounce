#include "material_manager.h"

bounce::Material& bounce::MaterialManager::CreateMaterial()
{
    materials_.push_back(Material());
    return *materials_.rbegin();
}

unsigned int bounce::MaterialManager::size() const
{
    return materials_.size();
}

unsigned int bounce::MaterialManager::next_index() const
{
    return materials_.size();
}

const bounce::Material& bounce::MaterialManager::GetMaterial(unsigned int index) const
{
    return materials_[index];
}