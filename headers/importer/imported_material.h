#ifndef BOUNCE_IMPORTER_IMPORTED_MATERIAL_H_
#define BOUNCE_IMPORTER_IMPORTED_MATERIAL_H_

#include <string>

namespace bounce {

    class ImportedMaterial {
    private:
        float diffuse_[3];
        float ambient_[3];
        float specular_[3];
        float emissive_[3];
        float shininess_;
        
        std::string texture_path_;
        
    public:
        ImportedMaterial();
        
        const std::string& texture_path() const;
        void texture_path(const std::string& value);
        
        const float* diffuse() const;
        void diffuse(float r, float g, float b);
        
        const float* specular() const;
        void specular(float r, float g, float b);
        
        const float* ambient() const;
        void ambient(float r, float g, float b);
        
        const float* emissive() const;
        void emissive(float r, float g, float b);
        
        float shininess() const;
        void shininess(float value);

    };

}

#endif // BOUNCE_IMPORTER_IMPORTED_MATERIAL_H_
