#include "g_buffer.h"

bounce::GBuffer::GBuffer()
{
    
}

bounce::GBuffer::~GBuffer()
{
    
}

bool bounce::GBuffer::Init(unsigned int window_width, unsigned int window_height)
{
    glGenFramebuffers(1, &fbo_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_);
    
    glGenTextures(GBUFFER_NUM_TEXTURES, textures_);
    glGenTextures(1, &depth_texture_);
    
    CHECK_GL_ERROR();
    
    for (int i = 0; i < GBUFFER_NUM_TEXTURES; ++i) {
        glBindTexture(GL_TEXTURE_2D, textures_[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, window_width, window_height, 0, GL_RGB, GL_FLOAT, NULL);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures_[i], 0);
    }
    CHECK_GL_ERROR();
    
    glBindTexture(GL_TEXTURE_2D, depth_texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, window_width, window_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture_, 0);
    
    GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };

//    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    
    glDrawBuffers(4, (GLenum*)draw_buffers);
    CHECK_GL_ERROR();
    
    GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
    
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        LOG_ERROR << "Framebuffer error, status: 0x" << std::hex << status << std::endl;
        return false;
    }
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    
    return true;
}

void bounce::GBuffer::BindForWriting()
{
    CHECK_GL_ERROR();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_);
    CHECK_GL_ERROR();
}

void bounce::GBuffer::BindForReading()
{
    CHECK_GL_ERROR();
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo_);
    CHECK_GL_ERROR();
}

void bounce::GBuffer::SetReadBuffer(GBufferTextureType texture_type)
{
    CHECK_GL_ERROR();
//    glReadBuffer(GL_COLOR_ATTACHMENT0 + (int)texture_type);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + texture_type);
    GLenum result = glGetError();
    
    if (result == GL_INVALID_ENUM) {
        LOG_ERROR << "Invalid enum" << std::endl;
    }
    else if (result == GL_INVALID_OPERATION) {
        LOG_ERROR << "INVALID OPERAITON" << std::endl;
    }
    CHECK_GL_ERROR();
}

