#include "model_manager.h"

bounce::ModelManager::ModelManager()
{
}

bounce::ModelManager::~ModelManager()
{
}

unsigned int bounce::ModelManager::GenerateModel()
{
    unsigned int index = models_.GenerateObject();
    return index;
}

bounce::Model& bounce::ModelManager::GetModel(unsigned int handle)
{
    return models_.GetObject(handle);
}

const bounce::Model& bounce::ModelManager::GetModel(unsigned int handle) const
{
    return models_.GetObject(handle);
}
