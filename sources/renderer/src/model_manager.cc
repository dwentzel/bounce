#include "model_manager.h"

bounce::Model& bounce::ModelManager::CreateModel()
{
    //Model model;
    models_.push_back(Model());
    return *models_.rbegin();
}