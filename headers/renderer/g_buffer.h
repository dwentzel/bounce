#ifndef BOUNCE_RENDERER_G_BUFFER_
#define BOUNCE_RENDERER_G_BUFFER_

#include "bounce_gl.h"

namespace bounce {

    class GBuffer {
    public:
        
        enum GBufferTextureType {
            GBUFFER_TEXTURE_TYPE_POSITION = 0,
            GBUFFER_TEXTURE_TYPE_DIFFUSE = 1,
            GBUFFER_TEXTURE_TYPE_NORMAL = 2,
            GBUFFER_TEXTURE_TYPE_TEXCOORD = 3,
            GBUFFER_NUM_TEXTURES = 4
        };
        
    private:
        GLuint fbo_;
        GLuint textures_[GBUFFER_NUM_TEXTURES];
        GLuint depth_texture_;
        
    public:
        GBuffer();
        ~GBuffer();
        
        bool Init(unsigned int window_width, unsigned int window_height);
        
        void BindForWriting();
        
        void BindForReading();
        
        void SetReadBuffer(GBufferTextureType TextureType);

    };

}

#endif // BOUNCE_RENDERER_G_BUFFER_
