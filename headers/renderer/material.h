#ifndef BOUNCE_RENDERER_MATERIAL_H_
#define BOUNCE_RENDERER_MATERIAL_H_

namespace bounce {
    
    class Material {
    private:
        float diffuse_[3];
        float ambient_[3];
        float specular_[3];
        float emissive_[3];
        float shininess_;
        
        bool has_texture_;
        unsigned int texture_handle_;
        
        Material();
    public:
        static Material Create();
        
        bool has_texture() const;
        
        unsigned int texture_handle() const;
        void texture_handle(unsigned int handle);
        
        const float* diffuse() const;
        void diffuse(const float* data);
        
        const float* ambient() const;
        void ambient(const float* data);
        
        const float* specular() const;
        void specular(const float* data);
        
        const float* emissive() const;
        void emissive(const float* data);
        
        float shininess() const;
        void shininess(float s);
    };
    
}

#endif // BOUNCE_RENDERER_MATERIAL_H_
