#include "opengl_renderer.h"

#include <vector>

#include "shader_manager.h"
#include "g_buffer.h"



bounce::OpenGLRenderer::OpenGLRenderer(const ModelManager& model_manager,
                                       const TextureManager& texture_manager,
                                       const MaterialManager& material_manager, const VertexBuffer& vertex_buffer)
: model_manager_(model_manager), texture_manager_(texture_manager), material_manager_(material_manager), vertex_buffer_(vertex_buffer)
{
    
}



//void bounce::OpenGLRenderer::SetupNewFrame()
//{
//
//
//    //    float light_position0[3] = { 0.0, 2.0, 0.0 };
//    //    float light_color0[3] = { 0.0, 1.0, 0.0 };
//    //
//    //    DirectionalLight light0;
//    //    light0.position = &light_position0[0];
//    //    light0.color = &light_color0[0];
//    //    light0.ambient_intensity = 0.0f;
//    //    light0.diffuse_intensity = 20.0f;
//    //
//    //    current_program_->SetLight(0, light0);
//    //
//    //    float light_position1[3] = { 2.0, 0.0, 0.0 };
//    //    float light_color1[3] = { 1.0, 0.0, 0.0 };
//    //
//    //    DirectionalLight light1;
//    //    light1.position = &light_position1[0];
//    //    light1.color = &light_color1[0];
//    //    light1.ambient_intensity = 0.0f;
//    //    light1.diffuse_intensity = 20.0f;
//    //
//    //    current_program_->SetLight(1, light1);
//    //
//    //    float light_position2[3] = { 0.0, 0.0, 2.0 };
//    //    float light_color2[3] = { 0.0, 0.0, 1.0 };
//    //
//    //    DirectionalLight light2;
//    //    light2.position = &light_position2[0];
//    //    light2.color = &light_color2[0];
//    //    light2.ambient_intensity = 0.0f;
//    //    light2.diffuse_intensity = 20.0f;
//    //
//    //    current_program_->SetLight(2, light2);
//    //
//    //    current_program_->SetLightCount(3);
//}

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void bounce::OpenGLRenderer::Startup()
{
    CHECK_GL_ERROR();
    
    glewExperimental = true; // Needed in core profile
    
    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK) {
        std::cout << glewGetErrorString(glew_error) << std::endl;
        LOG_ERROR << L"Failed to initialize GLEW" << std::endl;
        
        exit(-1);
    }
    CHECK_GL_ERROR();
    
    const GLubyte* m = glGetString(GL_VENDOR);
    LOG_INFO << L"GL_VENDOR: " << m << std::endl;
    
    m = glGetString(GL_RENDERER);
    LOG_INFO << L"GL_RENDERER: " << m << std::endl;
    
    m = glGetString(GL_VERSION);
    LOG_INFO << L"GL_VERSION: " << m << std::endl;
    
    //    m = glGetString(GL_EXTENSIONS);
    //    LOG_INFO << L"GL_EXTENSIONS: " << m << std::endl;
    //    CHECK_GL_ERROR();
    
    geometry_pass_program_.Init();
    geometry_pass_program_.UseProgram();
    geometry_pass_program_.SetColorTextureUnit(0);
    
    directional_light_pass_program_.Init();
    directional_light_pass_program_.UseProgram();
    directional_light_pass_program_.SetPositionTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
    directional_light_pass_program_.SetColorTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
    directional_light_pass_program_.SetNormalTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    directional_light_pass_program_.SetScreenSize(WINDOW_WIDTH, WINDOW_HEIGHT);
//    glEnable(GL_DEPTH_TEST);
//    CHECK_GL_ERROR();
    
//    glDepthFunc(GL_LESS);
//    CHECK_GL_ERROR();
    
//    glClearDepth(1.0);
//    CHECK_GL_ERROR();
//    
//    glEnable(GL_CULL_FACE);
//    CHECK_GL_ERROR();
    
    g_buffer_.Init(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    
    //glGenBuffers(3, buffers_);
    glGenBuffers(2, buffers_);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers_[0]);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_.current_size(), vertex_buffer_.buffer(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers_[1]);
    
    GLfloat quad[] = {
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f
    };
    
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), quad, GL_STATIC_DRAW);
    
    CHECK_GL_ERROR();
}

void bounce::OpenGLRenderer::Shutdown() {
    CHECK_GL_ERROR();
    glDeleteBuffers(1, buffers_);
    CHECK_GL_ERROR();
}

void bounce::OpenGLRenderer::ClearModels()
{
    model_handles_.erase(model_handles_.begin(), model_handles_.end());
}

void bounce::OpenGLRenderer::AddModel(unsigned int model_handle)
{
    model_handles_.push_back(model_handle);
}


void bounce::OpenGLRenderer::BeginFrame()
{
    BeginGeometryPass();
}

void bounce::OpenGLRenderer::EndFrame()
{
    EndGeometryPass();
    BeginLightPasses();
    RunDirectionalLightPass();
    RunLightPass();
}

void bounce::OpenGLRenderer::BeginGeometryPass()
{
    CHECK_GL_ERROR();
    
    geometry_pass_program_.UseProgram();
    CHECK_GL_ERROR();
    
    g_buffer_.BindForWriting();
    
    glDepthMask(GL_TRUE);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
    
    glDisable(GL_BLEND);
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers_[0]);
    
    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    // Texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // Normal vectors
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    
    CHECK_GL_ERROR();
}

void bounce::OpenGLRenderer::EndGeometryPass()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
}

void bounce::OpenGLRenderer::BeginLightPasses()
{
    glEnable(GL_BLEND);
   	glBlendEquation(GL_FUNC_ADD);
   	glBlendFunc(GL_ONE, GL_ONE);
    
    g_buffer_.BindForReading();
//    glClear(GL_COLOR_BUFFER_BIT);
}

void bounce::OpenGLRenderer::RunDirectionalLightPass()
{
    directional_light_pass_program_.UseProgram();
    CHECK_GL_ERROR();
//    m_DSDirLightPassTech.SetEyeWorldPos(m_pGameCamera->GetPos());

    glm::mat4 wvp_matrix = glm::mat4(1.0f);
    directional_light_pass_program_.SetWVP(wvp_matrix);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers_[1]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 18);
    
    glDisableVertexAttribArray(0);
    
}

void bounce::OpenGLRenderer::RunLightPass()
{
    CHECK_GL_ERROR();
    
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    g_buffer_.BindForReading();
    
    GLsizei HalfWidth = (GLsizei)(WINDOW_WIDTH / 2.0f);
    GLsizei HalfHeight = (GLsizei)(WINDOW_HEIGHT / 2.0f);
    
    g_buffer_.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                      0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    
    g_buffer_.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                      0, HalfHeight, HalfWidth, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    
    g_buffer_.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                      HalfWidth, HalfHeight, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    
    
    g_buffer_.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_TEXCOORD);
    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
                      HalfWidth, 0, WINDOW_WIDTH, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    CHECK_GL_ERROR();
}

void bounce::OpenGLRenderer::RenderModel(unsigned int model_handle)
{
    CHECK_GL_ERROR();
    
    const Model& model = model_manager_.GetModel(model_handle);
    
    const std::vector<int>& start_indices = model.mesh_start_indices();
    const std::vector<int>& sizes = model.mesh_sizes();
    const std::vector<int>& material_indices = model.material_indices();
    
    for (std::vector<int>::size_type i = 0; i != start_indices.size(); ++i) {
        int start_index = start_indices[i];
        int size = sizes[i];
        int material_index = material_indices[i];
        
        const Material& material = material_manager_.GetMaterial(material_index);
        
        int texture_handle = material.texture_handle();
        
        GLuint texture_id;
        glGenTextures(1, &texture_id);
        
        if (texture_handle > -1) {
            const Texture& texture = texture_manager_.GetTexture(texture_handle);
            
            glBindTexture(GL_TEXTURE_2D, texture_id);
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width(), texture.height(),
                         0, GL_BGR, GL_UNSIGNED_BYTE, texture.data());
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        }
        
//        current_program_->SetMaterial(material);
        
        glDrawArrays(GL_TRIANGLES, start_index, size);
        
        glDeleteTextures(1, &texture_id);
        CHECK_GL_ERROR();
    }
    
}