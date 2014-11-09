#include "texture.h"

bounce::Texture::Texture(unsigned int size, unsigned int width, unsigned int height, std::uint8_t* data)
: size_(size), width_(width), height_(height), data_(data)
{
    
}

bounce::Texture::~Texture()
{
    delete[] data_;
}