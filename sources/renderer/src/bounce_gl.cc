#include "bounce_gl.h"

#include <cstdio>
#include <cassert>

void bounce::CheckOpenGlError(const std::string& file, int line, const std::string& function)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        LOG_WARNING << "GL error in " << file << " @ " << line << ", " << function << ": " << glewGetErrorString(error);
    }
}

void bounce::AssertNoGlError(const std::string& file, int line, const std::string& function)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        LOG_ERROR << "GL error in " << file << " @ " << line << ", " << function << ": " << glewGetErrorString(error);
        exit(-1);
    }
}