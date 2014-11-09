#include "opengl_renderer.h"

#include <vector>

#include "shader_manager.h"



bounce::OpenGLRenderer::OpenGLRenderer(const std::string& vertex_shader_file_path, const std::string& fragment_shader_file_path,
                                       const ModelManager& model_manager,
                                       const TextureManager& texture_manager,
                                       const MaterialManager& material_manager, const VertexBuffer& vertex_buffer)
: vertex_shader_file_path_(vertex_shader_file_path), fragment_shader_file_path_(fragment_shader_file_path),
model_manager_(model_manager), texture_manager_(texture_manager), material_manager_(material_manager), vertex_buffer_(vertex_buffer)
{
    
}

void bounce::OpenGLRenderer::SetupNewFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CHECK_GL_ERROR();
    
    glUseProgram(program_id_);
    CHECK_GL_ERROR();
    
    glUniform3f(light_id_, 0, 3, 2);
}

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
    
    m = glGetString(GL_EXTENSIONS);
    LOG_INFO << L"GL_EXTENSIONS: " << m << std::endl;
    CHECK_GL_ERROR();
    
    glEnable(GL_DEPTH_TEST);
    CHECK_GL_ERROR();
    
    glDepthFunc(GL_LESS);
    CHECK_GL_ERROR();
    
    glClearDepth(1.0);
    CHECK_GL_ERROR();
    
    glEnable(GL_CULL_FACE);
    CHECK_GL_ERROR();
    
    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    CHECK_GL_ERROR();
    
    //glGenBuffers(3, buffers_);
    glGenBuffers(1, buffers_);
    
    CHECK_GL_ERROR();
    
    GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stdout, "framebuffer not complete\n");
    }
    CHECK_GL_ERROR();
    
    glBindBuffer(GL_ARRAY_BUFFER, buffers_[0]);
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
    
    program_id_ = glCreateProgram();
    
    shader_manager_.program_id(program_id_);

    shader_manager_.LoadVertexShader(vertex_shader_file_path_);
    shader_manager_.LoadFragmentShader(fragment_shader_file_path_);
    shader_manager_.LinkProgram();
    
//    program_id_ = shader_manager_.LoadShaders(
//                                             "shaders/triangleShader.vert.glsl",
//                                             "shaders/triangleShader.frag.glsl");
    
    mvp_matrix_id_ = glGetUniformLocation(program_id_, "MVP");
    view_matrix_id_ = glGetUniformLocation(program_id_, "V");
    model_matrix_id_ = glGetUniformLocation(program_id_, "M");
    
    light_id_ = glGetUniformLocation(program_id_, "LightPosition_worldspace");
    
    CHECK_GL_ERROR();
}

void bounce::OpenGLRenderer::Shutdown() {
    glDeleteBuffers(1, buffers_);
}

//void bounce::OpenGLRenderer::LoadVertexShader(const std::string& shader_code_file_path)
//{
//    shader_manager_.LoadVertexShader(shader_code_file_path);
//}
//
//void bounce::OpenGLRenderer::LoadFragmentShader(const std::string& shader_code_file_path)
//{
//    shader_manager_.LoadFragmentShader(shader_code_file_path);
//}
//
//void bounce::OpenGLRenderer::LinkProgram()
//{
//    shader_manager_.LinkProgram();
//}

void bounce::OpenGLRenderer::RenderModel(unsigned int model_handle)
{
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
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width(), texture.height()
                         , 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data());
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            
        }
        
        GLuint diffuse_index = glGetUniformLocation(program_id_, "Material_diffuse");
        GLuint ambient_index = glGetUniformLocation(program_id_, "Material_ambient");
        GLuint specular_index = glGetUniformLocation(program_id_, "Material_specular");
        GLuint emissive_index = glGetUniformLocation(program_id_, "Material_emissive");
        GLuint shininess_index = glGetUniformLocation(program_id_, "Material_shininess");
        
        glUniform3fv(diffuse_index, 1, material.diffuse());
        glUniform3fv(ambient_index, 1, material.ambient());
        glUniform3fv(specular_index, 1, material.specular());
        glUniform3fv(emissive_index, 1, material.emissive());
        glUniform1f(shininess_index, material.shininess());
        
        glDrawArrays(GL_TRIANGLES, start_index, size);
        CHECK_GL_ERROR();
        
        glDeleteTextures(1, &texture_id);
    }
    
}