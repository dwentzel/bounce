#ifndef BOUNCE_RENDERER_MATERIAL_H_
#define BOUNCE_RENDERER_MATERIAL_H_

#include <vector>
//#include <string>

namespace bounce {
    
    class Material {
    private:
        float diffuse_[3];
        float ambient_[3];
        float specular_[3];
        float emissive_[3];
        float shininess_;
        
        int texture_handle_;
        
//        std::string name_;
        
    public:
        Material();
        
        int texture_handle() const;
        void texture_handle(int handle);
        
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
}

#endif // BOUNCE_RENDERER_MATERIAL_H_