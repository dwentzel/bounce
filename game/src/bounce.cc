#include <iostream>

#include "bounce_mac/bounce_mac.h"
#include "bounce/app.h"

int bounce_main(bounce::ApplicationContext* context)
{
    
    std::wcout << L"bounce_main" << std::endl;
    
    context->CreateWindow();
    
    bounce::App app(*context);
    
    //app.onInit();
    
    app.onExecute();
    
    return 0;
}