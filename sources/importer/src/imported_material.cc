#include "imported_material.h"

bounce::ImportedMaterial::ImportedMaterial()
{
    
}

const std::string& bounce::ImportedMaterial::texture_path() const
{
    return texture_path_;
}

void bounce::ImportedMaterial::texture_path(const std::string& value)
{
    texture_path_ = value;
}

void bounce::ImportedMaterial::diffuse(float r, float g, float b)
{
    diffuse_[0] = r;
    diffuse_[1] = g;
    diffuse_[2] = b;
}

void bounce::ImportedMaterial::specular(float r, float g, float b)
{
    specular_[0] = r;
    specular_[1] = g;
    specular_[2] = b;
    
}

void bounce::ImportedMaterial::ambient(float r, float g, float b)
{
    ambient_[0] = r;
    ambient_[1] = g;
    ambient_[2] = b;
}

void bounce::ImportedMaterial::emissive(float r, float g, float b)
{
    emissive_[0] = r;
    emissive_[1] = g;
    emissive_[2] = b;
}

void bounce::ImportedMaterial::shininess(float value)
{
    shininess_ = value;
}
