#include "g_buffer.h"

bounce::GBuffer::GBuffer()
{
    fbo_ = 0;
    depth_texture_ = 0;
}

bounce::GBuffer::~GBuffer()
{
    
}

bool bounce::GBuffer::Init(unsigned int window_width, unsigned int window_height)
{
    CHECK_GL_ERROR();
    
    glGenFramebuffers(1, &fbo_);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_);
    
    glGenTextures(GBUFFER_NUM_TEXTURES, textures_);
    glGenTextures(1, &depth_texture_);
    
    for (unsigned int i = 0; i < GBUFFER_NUM_TEXTURES; ++i) {
        glBindTexture(GL_TEXTURE_2D, textures_[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, window_width, window_height, 0, GL_RGB, GL_FLOAT, nullptr);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures_[i], 0);
    }
    
    glBindTexture(GL_TEXTURE_2D, depth_texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, window_width, window_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture_, 0);
    
    GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, draw_buffers);
    
    GLenum status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
    
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        LOG_ERROR << "Framebuffer error, status: 0x" << std::hex << status << std::endl;
        
        CHECK_GL_ERROR();
        return false;
    }
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    
    CHECK_GL_ERROR();
    return true;
}

void bounce::GBuffer::BindForWriting()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo_);
}

void bounce::GBuffer::BindForReading()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    
    for (unsigned int i = 0 ; i < GBUFFER_NUM_TEXTURES; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures_[GBUFFER_TEXTURE_TYPE_POSITION + i]);
    }
}

void bounce::GBuffer::SetReadBuffer(GBufferTextureType texture_type)
{
    glReadBuffer(GL_COLOR_ATTACHMENT0 + texture_type);
}

