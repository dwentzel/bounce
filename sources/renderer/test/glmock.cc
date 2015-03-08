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

using ::testing::_;
using ::testing::Return;

OpenGLMock::OpenGLMock()
{
    ON_CALL(*this, CheckFramebufferStatus(_))
    .WillByDefault(Return(GL_FRAMEBUFFER_COMPLETE));
}

OpenGLMock::~OpenGLMock()
{
    
}
