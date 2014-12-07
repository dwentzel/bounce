#include "material_manager.h"

unsigned int bounce::MaterialManager::GenerateMaterial()
{
    unsigned int index = materials_.GenerateObject();
    return index;
}

bounce::Material& bounce::MaterialManager::GetMaterial(unsigned int index)
{
    return materials_.GetObject(index);
}

const bounce::Material& bounce::MaterialManager::GetMaterial(unsigned int index) const
{
    return materials_.GetObject(index);
}