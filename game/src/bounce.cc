#include <iostream>

#include "bounce/window_context.h"

#include "app.h"

int bounce_main(bounce::ApplicationContext* context)
{
    
    std::wcout << L"bounce_main" << std::endl;
    
    bounce::WindowContext window_context(400, 300);
    
    context->CreateWindow(window_context);
    
    bounce::App app(*context, window_context);
    
    //app.onInit();
    
    app.onExecute();
    
    return 0;
}