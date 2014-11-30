#include <iostream>
#include "renderer_test.h"

#include "renderer/g_buffer.h"
#include "renderer/geometry_pass_program.h"

#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 728

using namespace bounce;

GBuffer g_buffer_;
GeometryPassProgram* geometry_pass_program_;

void InitGL() {
    
    glewExperimental = true; // Needed in core profile
    
    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK) {
        std::cout << glewGetErrorString(glew_error) << std::endl;
        std::cerr << L"Failed to initialize GLEW" << std::endl;
        
        exit(-1);
    }
    

    
    const GLubyte* m = glGetString(GL_VENDOR);
    std::cerr << "GL_VENDOR: " << m << std::endl;
    
    m = glGetString(GL_RENDERER);
    std::cerr << "GL_RENDERER: " << m << std::endl;
    
    m = glGetString(GL_VERSION);
    std::cerr << "GL_VERSION: " << m << std::endl;
    
//    m = glGetString(GL_EXTENSIONS);
//    std::cerr << "GL_EXTENSIONS: " << m << std::endl;
    
    glEnable(GL_DEPTH_TEST);
    
    glDepthFunc(GL_LESS);
    
    glClearDepth(1.0);
    
    glEnable(GL_CULL_FACE);

}

void RunGeometryPass()
{
//    current_program_ = &geometry_pass_program_;
    //geometry_pass_program_->UseProgram();
    
    g_buffer_.BindForWriting();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
//    for (std::vector<unsigned int>::iterator i = model_handles_.begin(); i != model_handles_.end() ; ++i) {
//        RenderModel(*i);
//    }
}

void RunLightPass()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    g_buffer_.BindForReading();
    
    GLsizei HalfWidth = (GLsizei)(WINDOW_WIDTH / 2.0f);
    GLsizei HalfHeight = (GLsizei)(WINDOW_HEIGHT / 2.0f);
    
//    g_buffer_.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
//    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
//                      0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
//    CHECK_GL_ERROR();
//    
//    g_buffer_.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_DIFFUSE);
//    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
//                      0, HalfHeight, HalfWidth, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);
//    CHECK_GL_ERROR();
//    
//    g_buffer_.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
//    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
//                      HalfWidth, HalfHeight, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);
//    CHECK_GL_ERROR();
//    
//    g_buffer_.SetReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_TEXCOORD);
//    glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
//                      HalfWidth, 0, WINDOW_WIDTH, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
//    CHECK_GL_ERROR();

}

int main(int argc, char** argv)
{
    LogManager::instance().Startup();
    
    if( !glfwInit() )
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }
    
    glfwWindowHint(GLFW_SAMPLES, 0); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
    
    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global)
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tutorial 01", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    
    InitGL();
    
    g_buffer_.Init(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    std::string root_path = "/Users/daniel/XCode/Bounce/build/Debug";
    
//    bounce::GeometryPassProgram geometry_program;
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    do{
        // Draw nothing, see you in tutorial 2 !
        
        RunGeometryPass();
        RunLightPass();
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
}