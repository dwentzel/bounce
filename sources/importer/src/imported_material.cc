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

const float* bounce::ImportedMaterial::diffuse() const
{
    return diffuse_;
}

void bounce::ImportedMaterial::diffuse(float r, float g, float b)
{
    diffuse_[0] = r;
    diffuse_[1] = g;
    diffuse_[2] = b;
}

const float* bounce::ImportedMaterial::specular() const
{
    return specular_;
}

void bounce::ImportedMaterial::specular(float r, float g, float b)
{
    specular_[0] = r;
    specular_[1] = g;
    specular_[2] = b;
    
}

const float* bounce::ImportedMaterial::ambient() const
{
    return ambient_;
}

void bounce::ImportedMaterial::ambient(float r, float g, float b)
{
    ambient_[0] = r;
    ambient_[1] = g;
    ambient_[2] = b;
}

const float* bounce::ImportedMaterial::emissive() const
{
    return emissive_;
}

void bounce::ImportedMaterial::emissive(float r, float g, float b)
{
    emissive_[0] = r;
    emissive_[1] = g;
    emissive_[2] = b;
}

float bounce::ImportedMaterial::shininess() const
{
    return shininess_;
}

void bounce::ImportedMaterial::shininess(float value)
{
    shininess_ = value;
}
