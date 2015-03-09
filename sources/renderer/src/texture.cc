#include "texture.h"

#include "framework/contracts.h"

bounce::Texture bounce::Texture::Create(std::unique_ptr<ImageData> image_data)
{
    CONTRACT_REQUIRES(image_data != nullptr);
    
    return Texture(std::move(image_data));
}

bounce::Texture::Texture(std::unique_ptr<ImageData> image_data)
: image_data_(std::move(image_data))
{
    CONTRACT_REQUIRES(image_data_ != nullptr);
    
    glGenTextures(1, &texture_id_);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB32F, static_cast<GLsizei>(image_data_->width()), static_cast<GLsizei>(image_data_->height()));
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, static_cast<GLsizei>(image_data_->width()), static_cast<GLsizei>(image_data_->height()), GL_BGR, GL_UNSIGNED_BYTE, image_data_->data());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    CHECK_GL_ERROR();
}

bounce::Texture::Texture(Texture&& source)
: image_data_(std::move(source.image_data_)), texture_id_(source.texture_id_), name_(source.name_)
{
    source.texture_id_ = 0;
    source.image_data_ = nullptr;
}

bounce::Texture::~Texture()
{
    glDeleteTextures(1, &texture_id_);
}

//void bounce::Texture::Initialize()
//{
////    glGenTextures(1, &texture_id_);
////    
////    glActiveTexture(GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D, texture_id_);
////    
////    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_,
////                 0, GL_BGR, GL_UNSIGNED_BYTE, data_);
////    
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
////    
////    initialized_ = true;
//}

void bounce::Texture::UseTexture()
{
//    if (!initialized_)
//    {
//        Initialize();
//    }
    CHECK_GL_ERROR();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    CHECK_GL_ERROR();
}


unsigned int bounce::Texture::size() const
{
    return image_data_->size();
}

unsigned int bounce::Texture::width() const
{
    return image_data_->width();
}

unsigned int bounce::Texture::height() const
{
    return image_data_->height();
}

const std::string& bounce::Texture::name() const
{
    return name_;
}
