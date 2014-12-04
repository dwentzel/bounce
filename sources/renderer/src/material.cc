#include "material.h"

#include <cstring>

bounce::Material bounce::Material::Create()
{
    return Material();
}

bounce::Material::Material()
: has_texture_(false)
{

}

bool bounce::Material::has_texture() const
{
    return has_texture_;
}

int bounce::Material::texture_handle() const
{
    return texture_handle_;
}

void bounce::Material::texture_handle(int handle)
{
    has_texture_ = true;
    texture_handle_ = handle;
}

const float* bounce::Material::diffuse() const
{
    return diffuse_;
}

void bounce::Material::diffuse(const float* data)
{
    memcpy(diffuse_, data, 3 * sizeof(float));
}

const float* bounce::Material::ambient() const
{
    return ambient_;
}

void bounce::Material::ambient(const float* data)
{
    memcpy(ambient_, data, 3 * sizeof(float));
}

const float* bounce::Material::specular() const
{
    return specular_;
}

void bounce::Material::specular(const float* data)
{
    memcpy(specular_, data, 3 * sizeof(float));
}

const float* bounce::Material::emissive() const
{
    return emissive_;
}

void bounce::Material::emissive(const float* data)
{
    memcpy(emissive_, data, 3 * sizeof(float));
}

float bounce::Material::shininess() const
{
    return shininess_;
}

void bounce::Material::shininess(float s)
{
    shininess_ = s;
}