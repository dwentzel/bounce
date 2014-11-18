#ifndef BOUNCE_RENDERER_GEOMETRY_PASS_PROGRAM_
#define BOUNCE_RENDERER_GEOMETRY_PASS_PROGRAM_

#include "shader_program.h"

namespace bounce {

    class GeometryPassProgram : public ShaderProgram {
    private:
        GLint mwvp_matrix_id_;
        GLint wvp_matrix_id_;
        GLint view_matrix_id_;
        GLint world_matrix_id_;
        GLint model_matrix_id_;

    public:
        GeometryPassProgram();
        ~GeometryPassProgram();
        
        bool Init();
        
        void SetModelMatrix(const float* model_matrix);
        void SetWorldMatrix(const float* world_matrix);
        void SetViewMatrix(const float* view_matrix);
        void SetWVPMatrix(const float* wvp_matrix);
        void SetMWVPMatrix(const float* mwvp_matrix);
    };

}

#endif // BOUNCE_RENDERER_GEOMETRY_PASS_PROGRAM_
