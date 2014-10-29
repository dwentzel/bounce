#ifndef BOUNCE_MATERIAL_H_
#define BOUNCE_MATERIAL_H_

#include <vector>
//#include

namespace bounce {
    
    class Material {
    private:
        float diffuse_[3];
        float ambient_[3];
        float specular_[3];
        float emissive_[3];
        float shininess_;
        
    public:
        const float* diffuse() const;
        void diffuse(void* data);
        
        const float* ambient() const;
        void ambient(void* data);
        
        const float* specular() const;
        void specular(void* data);
        
        const float* emissive() const;
        void emissive(void* data);
        
        float shininess() const;
        void shininess(float s);
    };
    
    inline const float* Material::diffuse() const
    {
        return diffuse_;
    }
    
    inline void Material::diffuse(void* data)
    {
        memcpy(diffuse_, data, 3 * sizeof(float));
    }
    
    inline const float* Material::ambient() const
    {
        return ambient_;
    }
    
    inline void Material::ambient(void* data)
    {
        memcpy(ambient_, data, 3 * sizeof(float));
    }
    
    inline const float* Material::specular() const
    {
        return specular_;
    }
    
    inline void Material::specular(void* data)
    {
        memcpy(specular_, data, 3 * sizeof(float));
    }
    
    inline const float* Material::emissive() const
    {
        return emissive_;
    }
    
    inline void Material::emissive(void* data)
    {
        memcpy(emissive_, data, 3 * sizeof(float));
    }
    
    inline float Material::shininess() const
    {
        return shininess_;
    }
    
    inline void Material::shininess(float s)
    {
        shininess_ = s;
    }

    
    class MaterialManager {
    private:
        std::vector<Material> materials_;
        
    public:
        Material& CreateMaterial();
        
        const Material& GetMaterial(int index) const;
        
        int size() const;
        int next_index() const;
    };
    
    inline Material& MaterialManager::CreateMaterial()
    {
        materials_.push_back(Material());
        return *materials_.rbegin();
    }
    
    inline int MaterialManager::size() const
    {
        return materials_.size();
    }
    
    inline int MaterialManager::next_index() const
    {
        return materials_.size();
    }
    
    inline const Material& MaterialManager::GetMaterial(int index) const
    {
        return materials_[index];
    }
}

#endif // BOUNCE_MATERIAL_H_