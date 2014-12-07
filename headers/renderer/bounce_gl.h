#ifndef BOUNCE_RENDERER_BOUNCE_GL_H_
#define BOUNCE_RENDERER_BOUNCE_GL_H_

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>

#if defined (__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include "logging/log.h"
#ifdef __PRETTY_FUNCTION__
#define CHECK_GL_ERROR() bounce::CheckOpenGlError(__FILE__,__LINE__,__PRETTY_FUNCTION__)
#define ASSERT_NO_GL_ERROR() bounce::AssertNoGlError(__FILE__,__LINE__,__PRETTY_FUNCTION__)
#else
#define CHECK_GL_ERROR() bounce::CheckOpenGlError(__FILE__,__LINE__,__FUNCTION__)
#define ASSERT_NO_GL_ERROR() bounce::AssertNoGlError(__FILE__,__LINE__,__FUNCTION__)
#endif

//#define CHECK_UNIFORM_LOCATION_AND_LOG_ERROR(uniform_location) bounce::CheckUniformLocationAndLogError(uniform_location, #uniform_location)

namespace bounce {

    const float PI = 3.1415926535897932384626433832795f;
    const float PI2 = PI * 2.0f;
    
    void CheckOpenGlError(const std::string& file, int line, const std::string& function);
    void AssertNoGlError(const std::string& file, int line, const std::string& function);
//    void CheckUniformLocationAndLogError(GLuint location, const std::string& uniform);

}

#endif // BOUNCE_RENDERER_BOUNCE_GL_H_
