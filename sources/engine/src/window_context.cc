#include "window_context.h"

bounce::WindowContext::WindowContext(unsigned int width, unsigned int height)
: width_(width), height_(height)
{
    
}

unsigned int bounce::WindowContext::width() const
{
    return width_;
}

unsigned int bounce::WindowContext::height() const
{
    return height_;
}
