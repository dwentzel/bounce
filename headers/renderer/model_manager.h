#ifndef BOUNCE_RENDERER_MODEL_MANAGER_
#define BOUNCE_RENDERER_MODEL_MANAGER_

#include <vector>
#include "model.h"

namespace bounce {

    class ModelManager {
    private:
        std::vector<Model> models_;
        
        ModelManager(const ModelManager&) = delete;
        ModelManager& operator=(const ModelManager&) = delete;
        
    public:
        ModelManager() {}
        
        Model& CreateModel();
        
        const Model& GetModel(unsigned int model_handle) const;
        
        unsigned int next_handle() const;
    };
    
    inline unsigned int ModelManager::next_handle() const
    {
        return models_.size();
    }
    
    inline const Model& ModelManager::GetModel(unsigned int model_handle) const
    {
        return models_[model_handle];
    }

}

#endif // BOUNCE_RENDERER_MODEL_MANAGER_
