#ifndef BOUNCE_SHADERMANAGER_H_
#define BOUNCE_SHADERMANAGER_H_

#include <string>
#include "bounce_gl.h"
#include "shader_program.h"

namespace bounce {
    
    class ShaderManager {
    private:
        std::vector<ShaderProgram> shader_programs_;

    public:
        ShaderProgram& CreateProgram();
        
        ShaderProgram& GetShaderProgram(unsigned int program_handle);
        
        unsigned int next_handle() const;
        
    };
    
}

#endif // BOUNCE_SHADERMANAGER_H_
