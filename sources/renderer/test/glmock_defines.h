#ifndef BOUNCE_GLMOCK_DEFINES_H_
#define BOUNCE_GLMOCK_DEFINES_H_

#undef glGenFramebuffers
#define glGenFramebuffers openGLMock.GenFramebuffers
#undef glBindFramebuffer
#define glBindFramebuffer openGLMock.BindFramebuffer
#undef glGenTextures
#define glGenTextures openGLMock.GenTextures
#undef glBindTexture
#define glBindTexture openGLMock.BindTexture
#undef glTexStorage2D
#define glTexStorage2D openGLMock.TexStorage2D
#undef glTexParameterf
#define glTexParameterf openGLMock.TexParameterf
#undef glFramebufferTexture2D
#define glFramebufferTexture2D openGLMock.FramebufferTexture2D
#undef glDrawBuffers
#define glDrawBuffers openGLMock.DrawBuffers
#undef glCheckFramebufferStatus
#define glCheckFramebufferStatus openGLMock.CheckFramebufferStatus
#undef glGetError
#define glGetError openGLMock.GetError
#undef glDeleteTextures
#define glDeleteTextures openGLMock.DeleteTextures
#undef glDeleteFramebuffers
#define glDeleteFramebuffers openGLMock.DeleteFramebuffers

#endif // BOUNCE_GLMOCK_DEFINES_H_
