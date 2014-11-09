#ifndef BOUNCE_GL_H_
#define BOUNCE_GL_H_

//#ifdef __APPLE__
//	//#ifndef GLUT_3_2_CORE_PROFILE
//		#define GLUT_3_2_CORE_PROFILE 0
//		#define glBindVertexArray		glBindVertexArrayAPPLE
//		#define glDeleteVertexArrays	glDeleteVertexArraysAPPLE
//		#define glIsVertexArray			glIsVertexArrayAPPLE
//		#define glGenVertexArrays  	glGenVertexArraysAPPLE
//	//#endif
//#endif
#include <string>

#include <GL/glew.h>

#if defined (__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <cstdio>
#include <cassert>

#include "logging/log.h"

#define CHECK_GL_ERROR() bounce::CheckOpenGlError(__FILE__,__LINE__)
#define ASSERT_NO_GL_ERROR() bounce::AssertNoGlError(__FILE__,__LINE__)

namespace bounce {
    const float PI = 3.1415926535897932384626433832795f;
    const float PI2 = PI * 2.0f;
    
    inline void CheckOpenGlError(std::string file, int line) {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            LOG_WARNING << "GL error in file " << file << " @ " << line << ": " << glewGetErrorString(error) << std::endl;
//            std::fprintf(stderr, "gl error in file %s @ %d: %s\n", file.c_str(), line, glewGetErrorString(error));
        }
    };
    
    inline void AssertNoGlError(std::string file, int line)
    {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::fprintf(stderr, "gl error in file %s @ %d: %s\n", file.c_str(), line, glewGetErrorString(error));
            exit(-1);
        }
    }

}


#endif
