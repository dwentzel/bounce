#include <fstream>
#include <iostream>
#include "bounce_gl.h"
#include "shader_manager.h"

bounce::ShaderProgram& bounce::ShaderManager::CreateProgram()
{
    GLuint program_id = glCreateProgram();
    
//    shader_programs_.emplace_back(program_id);
//    shader_programs_.emplace_back();
    return (*shader_programs_.rbegin());
}

unsigned int bounce::ShaderManager::next_handle() const
{
    return shader_programs_.size();
}