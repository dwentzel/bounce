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

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif



#endif
