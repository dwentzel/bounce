#ifndef BOUNCE_GLMOCK_H_
#define BOUNCE_GLMOCK_H_

#include "contrib/disable_clang_warnings.h"
#include "gmock/gmock.h"
#include "contrib/enable_clang_warnings.h"
#include "bounce_gl.h"

class OpenGLMock {
public:
    MOCK_METHOD2(GenFramebuffers, void(GLsizei n, GLuint* buffers));
    MOCK_METHOD2(BindFramebuffer, void(GLenum target, GLuint framebuffer));
    
    MOCK_METHOD2(GenTextures, void(GLsizei n, GLuint *textures));
    MOCK_METHOD2(BindTexture, void(GLenum target, GLuint texture));
    MOCK_METHOD5(TexStorage2D, void(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height));
    MOCK_METHOD3(TexParameterf, void(GLenum target, GLenum pname, GLfloat param));
    MOCK_METHOD5(FramebufferTexture2D, void(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level));
    MOCK_METHOD2(DrawBuffers, void(GLsizei n, const GLenum* bufs));
    MOCK_METHOD1(CheckFramebufferStatus, GLenum(GLenum target));
    MOCK_METHOD0(GetError, GLenum());
    MOCK_METHOD2(DeleteTextures, void(GLsizei n, const GLuint *textures));
    MOCK_METHOD2(DeleteFramebuffers, void(GLsizei n, const GLuint* framebuffers));
};

class GLFacade
{
public:
    static void Mock(OpenGLMock* value);
    static OpenGLMock& Mock();

private:
    static OpenGLMock* mock_;
};

#undef glGenFramebuffers
#define glGenFramebuffers GLFacade::Mock().GenFramebuffers
#undef glBindFramebuffer
#define glBindFramebuffer GLFacade::Mock().BindFramebuffer
#undef glGenTextures
#define glGenTextures GLFacade::Mock().GenTextures
#undef glBindTexture
#define glBindTexture GLFacade::Mock().BindTexture
#undef glTexStorage2D
#define glTexStorage2D GLFacade::Mock().TexStorage2D
#undef glTexParameterf
#define glTexParameterf GLFacade::Mock().TexParameterf
#undef glFramebufferTexture2D
#define glFramebufferTexture2D GLFacade::Mock().FramebufferTexture2D
#undef glDrawBuffers
#define glDrawBuffers GLFacade::Mock().DrawBuffers
#undef glCheckFramebufferStatus
#define glCheckFramebufferStatus GLFacade::Mock().CheckFramebufferStatus
#undef glGetError
#define glGetError GLFacade::Mock().GetError
#undef glDeleteTextures
#define glDeleteTextures GLFacade::Mock().DeleteTextures
#undef glDeleteFramebuffers
#define glDeleteFramebuffers GLFacade::Mock().DeleteFramebuffers


#endif // BOUNCE_GLMOCK_H_
