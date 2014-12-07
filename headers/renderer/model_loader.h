#ifndef BOUNCE_RENDERER_MODEL_LOADER_H_
#define BOUNCE_RENDERER_MODEL_LOADER_H_

#include <vector>

#include "importer/imported_model.h"

#include "texture_manager.h"
#include "material_manager.h"
#include "model_manager.h"

namespace bounce {

    class ModelLoader {
    private:
        TextureManager& texture_manager_;
        MaterialManager& material_manager_;
        ModelManager& model_manager_;
        
        unsigned int base_vertex_;
        unsigned short index_offset_;
        
        std::vector<float> vertex_data_;
        std::vector<unsigned short> index_data_;
        
        int LoadMaterial(const ImportedMaterial& imported_material);
        
        ModelLoader& operator=(const ModelLoader&) = delete;
    public:
        ModelLoader(TextureManager& texture_manager, MaterialManager& material_manager, ModelManager& model_manager);
        
        void Begin();
        int LoadModel(const ImportedModel& imported_model);
        void End();
        
        const std::vector<float> vertex_data() const {
            return vertex_data_;
        }
        
        const std::vector<unsigned short> index_data() const {
            return index_data_;
        }
    };

}

#endif // BOUNCE_RENDERER_MODEL_LOADER_H_
