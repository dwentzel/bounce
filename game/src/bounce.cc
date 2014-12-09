#include <iostream>

#include "engine/window_context.h"

#include "app.h"

int bounce_main(bounce::ApplicationContext* context)
{
    
    //std::wcout << L"bounce_main" << std::endl;
    
    bounce::WindowContext window_context(800, 600);
    
    context->CreateApplicationWindow(window_context);
    
    bounce::App app(*context, window_context);
    
    //app.onInit();
    
    app.onExecute();
    
    return 0;
}