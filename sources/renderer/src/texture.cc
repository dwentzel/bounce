#include "texture.h"

bounce::Texture::Texture(unsigned int size, unsigned int width, unsigned int height, std::uint8_t* data)
: size_(size), width_(width), height_(height), data_(data)
{
    glGenTextures(1, &texture_id_);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
        
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, width_, height_);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GL_BGR, GL_UNSIGNED_BYTE, data_);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    CHECK_GL_ERROR();
}

bounce::Texture::~Texture()
{
    glDeleteTextures(1, &texture_id_);
    delete[] data_;
}

void bounce::Texture::Initialize()
{
//    glGenTextures(1, &texture_id_);
//    
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture_id_);
//    
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_,
//                 0, GL_BGR, GL_UNSIGNED_BYTE, data_);
//    
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    
//    initialized_ = true;
}

void bounce::Texture::UseTexture()
{
//    if (!initialized_)
//    {
//        Initialize();
//    }
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    CHECK_GL_ERROR();
}


unsigned int bounce::Texture::size() const
{
    return size_;
}

unsigned int bounce::Texture::width() const
{
    return width_;
}

unsigned int bounce::Texture::height() const
{
    return height_;
}

//const std::uint8_t* bounce::Texture::data() const
//{
//    return data_;
//}
