#include "opengl_renderer.h"

#include <vector>

#include "shader_manager.h"
#include "g_buffer.h"

#include "sphere_mesh.cc"


bounce::OpenGLRenderer::OpenGLRenderer(const ResourceLoader& resource_loader,
                                       const ModelManager& model_manager,
                                       const TextureManager& texture_manager,
                                       const MaterialManager& material_manager, const VertexBuffer& vertex_buffer)
: geometry_pass_program_(resource_loader), directional_light_pass_program_(resource_loader), point_light_pass_program_(resource_loader),
  mesh_loader_(resource_loader),
  model_manager_(model_manager), texture_manager_(texture_manager), material_manager_(material_manager), vertex_buffer_(vertex_buffer)
{
    
}


bounce::OpenGLRenderer::~OpenGLRenderer()
{
    delete sphere_;
    delete quad_;
}

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
    
//    m_dirLight.AmbientIntensity = 0.1f;
//    m_dirLight.Color = COLOR_CYAN;
//    m_dirLight.DiffuseIntensity = 0.5f;
//    m_dirLight.Direction = Vector3f(1.0f, 0.0f, 0.0f);
    
    DirectionalLight directional_light;
    directional_light.ambient_intensity = 0.1f;
    directional_light.color = glm::vec3(1.0f, 1.0f, 1.0f);
    directional_light.diffuse_intensity = 0.7f;
    directional_light.direction = glm::vec3(0.0f, -1.0f, 0.0f);
    
    
    directional_light_pass_program_.SetDirectionalLight(directional_light);
    
    point_light_pass_program_.Init();
    point_light_pass_program_.UseProgram();
    point_light_pass_program_.SetPositionTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
    point_light_pass_program_.SetColorTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
    point_light_pass_program_.SetNormalTextureUnit(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    point_light_pass_program_.SetScreenSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    point_lights_[0].diffuse_intensity = 3.7f;
    point_lights_[0].color = glm::vec3(0.0f, 1.0f, 0.0f);
    point_lights_[0].position = glm::vec3(0.0f, 1.0f, 0.5f);
    point_lights_[0].attenuation.constant = 0.0f;
    point_lights_[0].attenuation.linear = 0.0f;
    point_lights_[0].attenuation.exp = 0.3f;
    
    point_lights_[1].diffuse_intensity = 2.7f;
    point_lights_[1].color = glm::vec3(1.0f, 0.0f, 0.0f);
    point_lights_[1].position = glm::vec3(0.0f, 1.0f, 1.5f);
    point_lights_[1].attenuation.constant = 0.0f;
    point_lights_[1].attenuation.linear = 0.0f;
    point_lights_[1].attenuation.exp = 0.3f;
    
    point_lights_[2].diffuse_intensity = 0.7f;
    point_lights_[2].color = glm::vec3(0.0f, 0.0f, 1.0f);
    point_lights_[2].position = glm::vec3(0.5f, 0.0f, 0.5f);
    point_lights_[2].attenuation.constant = 0.0f;
    point_lights_[2].attenuation.linear = 0.0f;
    point_lights_[2].attenuation.exp = 0.3f;
    
    g_buffer_.Init(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    glGenVertexArrays(1, &model_vertex_array_);
    glBindVertexArray(model_vertex_array_);
    
    glGenBuffers(1, &model_vertex_buffer_);
    
    glBindBuffer(GL_ARRAY_BUFFER, model_vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_.current_size(), vertex_buffer_.buffer(), GL_STATIC_DRAW);
    
    // Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    // Texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // Normal vectors
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    
    glBindVertexArray(0);
    
//    glGenVertexArrays(1, &directional_vertex_array_);
//    glBindVertexArray(directional_vertex_array_);
//    
//    glGenBuffers(1, &directional_vertex_buffer_);
//    glBindBuffer(GL_ARRAY_BUFFER, directional_vertex_buffer_);
//    
//    GLfloat quad[] = {
//        1.0f, 1.0f, 0.0f,
//        -1.0f, 1.0f, 0.0f,
//        -1.0f, -1.0f, 0.0f,
//        -1.0f, -1.0f, 0.0f,
//        1.0f, -1.0f, 0.0f,
//        1.0f, 1.0f, 0.0f
//    };
//    
//    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), quad, GL_STATIC_DRAW);
//    
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    
//    glBindVertexArray(0);
    
    sphere_ = mesh_loader_.Load("sphere.dae");
    quad_ = mesh_loader_.Load("quad.dae");
    
    //sphere_.ImportFile("/Users/daniel/Repos/bounce/resources/models/sphere.dae");
    
    
    CHECK_GL_ERROR();
}

void bounce::OpenGLRenderer::Shutdown() {
    CHECK_GL_ERROR();
    glDeleteBuffers(1, &model_vertex_buffer_);
    glDeleteBuffers(1, &directional_vertex_buffer_);
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
    RunPointLightsPass();
    RunDirectionalLightPass();

    //RunLightPass();
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
    
    glBindVertexArray(model_vertex_array_);
    
    CHECK_GL_ERROR();
}

void bounce::OpenGLRenderer::EndGeometryPass()
{
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(1);
//    glDisableVertexAttribArray(2);
    
    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
}

void bounce::OpenGLRenderer::BeginLightPasses()
{
    glEnable(GL_BLEND);
   	glBlendEquation(GL_FUNC_ADD);
   	glBlendFunc(GL_ONE, GL_ONE);
    
    g_buffer_.BindForReading();
    glClear(GL_COLOR_BUFFER_BIT);
}

void bounce::OpenGLRenderer::RunDirectionalLightPass()
{
    directional_light_pass_program_.UseProgram();
    CHECK_GL_ERROR();
    directional_light_pass_program_.SetEyeWorldPos(glm::vec3(2.0f, 3.0f, 5.0f));
    
    glm::mat4 wvp_matrix = glm::mat4(1.0f);
    directional_light_pass_program_.SetWVP(wvp_matrix);
    

//    sphere_.Render();
    
//    glBindBuffer(GL_ARRAY_BUFFER, buffers_[1]);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

//    glBindVertexArray(directional_vertex_array_);
//    
//    glDrawArrays(GL_TRIANGLES, 0, 18);
//    
////    glDisableVertexAttribArray(0);
//    glBindVertexArray(0);
    quad_->Render();
}

void bounce::OpenGLRenderer::RunPointLightsPass()
{
    point_light_pass_program_.UseProgram();
    point_light_pass_program_.SetEyeWorldPos(glm::vec3(2.0f, 3.0f, 5.0f));
    
//    Pipeline p;
//    p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
//    p.SetPerspectiveProj(m_persProjInfo);

    point_light_pass_program_.SetWVP(wvp_matrix_);
    
   	for (unsigned int i = 1 ; i < 3; i++) {
        point_light_pass_program_.SetPointLight(point_lights_[i]);
        
//        point_light_pass_program_.SetWVP(glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 20.0f, 20.0f)));
//   	    p.WorldPos(m_pointLight[i].Position);
//   	    float BSphereScale = CalcPointLightBSphere(m_pointLight[i]);
//   	    p.Scale(BSphereScale, BSphereScale, BSphereScale);
//   	    m_DSPointLightPassTech.SetWVP(p.GetWVPTrans());
   	    sphere_->Render();
   	} 
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
    
    
//    g_buffer_.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_TEXCOORD);
//    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
//                      HalfWidth, 0, WINDOW_WIDTH, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
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
            
            glActiveTexture(GL_TEXTURE0);
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