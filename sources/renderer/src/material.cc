#include "material.h"

bounce::Material::Material()
: texture_handle_(-1)
{

}

int bounce::Material::texture_handle() const
{
    return texture_handle_;
}

void bounce::Material::texture_handle(int handle)
{
    texture_handle_ = handle;
}