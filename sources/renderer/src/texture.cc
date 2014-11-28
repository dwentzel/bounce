#include "texture.h"

bounce::Texture::Texture(unsigned int size, unsigned int width, unsigned int height, std::uint8_t* data)
: initialized_(false), size_(size), width_(width), height_(height), data_(data)
{
    
}

bounce::Texture::~Texture()
{
    glDeleteTextures(1, &texture_id_);
    delete[] data_;
}

void bounce::Texture::Initialize()
{
    glGenTextures(1, &texture_id_);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_,
                 0, GL_BGR, GL_UNSIGNED_BYTE, data_);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    initialized_ = true;
}

void bounce::Texture::UseTexture()
{
    if (!initialized_)
    {
        Initialize();
    }
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
}