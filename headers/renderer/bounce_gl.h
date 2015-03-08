#ifndef BOUNCE_RENDERER_BOUNCE_GL_H_
#define BOUNCE_RENDERER_BOUNCE_GL_H_

#define GLEW_STATIC
#include <GL/glew.h>

#if defined(MOCK_OPENGL)
#   include "glmock.h"
#elif defined(__APPLE__) && defined(__MACH__)
#   include <OpenGL/gl.h>
#else
#   include <GL/gl.h>
#endif

#ifdef __PRETTY_FUNCTION__
#   define CHECK_GL_ERROR() bounce::CheckOpenGlError(__FILE__,__LINE__,__PRETTY_FUNCTION__)
#   define ASSERT_NO_GL_ERROR() bounce::AssertNoGlError(__FILE__,__LINE__,__PRETTY_FUNCTION__)
#else
#   define CHECK_GL_ERROR() bounce::CheckOpenGlError(__FILE__,__LINE__,__FUNCTION__)
#   define ASSERT_NO_GL_ERROR() bounce::AssertNoGlError(__FILE__,__LINE__,__FUNCTION__)
#endif

#include <string>

namespace bounce {

    const float PI = 3.1415926535897932384626433832795f;
    const float PI2 = PI * 2.0f;
    
    void CheckOpenGlError(const std::string& file, int line, const std::string& function);
    void AssertNoGlError(const std::string& file, int line, const std::string& function);

}

#endif // BOUNCE_RENDERER_BOUNCE_GL_H_
