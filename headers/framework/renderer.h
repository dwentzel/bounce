#ifndef BOUNCE_RENDERER_H_
#define BOUNCE_RENDERER_H_



namespace bounce {
    
    class Renderer {
    private:
    protected:
        Renderer();
    public:
        virtual ~Renderer() = 0;
    
        virtual void Startup() = 0;
        virtual void Shutdown() = 0;
        
        virtual void SetupNewFrame() = 0;
        virtual void SetViewMatrix(const float* view_matrix) = 0;
        virtual void SetModelMatrix(const float* model_matrix) = 0;
        virtual void SetMVPMatrix(const float* mvp_matrix) = 0;
        
        virtual void RenderModel(unsigned int model_handle) = 0;
    };
    
}

#endif // BOUNCE_RENDERER_H_