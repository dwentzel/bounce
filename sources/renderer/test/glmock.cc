#include "glmock.h"

OpenGLMock* GLFacade::mock_;

void GLFacade::Mock(OpenGLMock* value)
{
    mock_ = value;
}

OpenGLMock& GLFacade::Mock()
{
    return *mock_;
}