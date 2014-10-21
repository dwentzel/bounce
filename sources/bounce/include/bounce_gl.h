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

#include <GL/glew.h>

#if defined (__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

namespace bounce {
    const float PI = 3.14159265358979f;
    const float PI2 = PI * 2.0f;
}


#endif
