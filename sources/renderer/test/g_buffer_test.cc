#include "g_buffer.h"
#include "glmock.h"
#include "gmock/gmock.h"

namespace bounce {
    namespace tests {
        
        using ::testing::_;
        using ::testing::InSequence;
        using ::testing::Return;
        using ::testing::SetArgPointee;
        
        class GBufferTest : public ::testing::Test {
        protected:
            // You can remove any or all of the following functions if its body
            // is empty.
            
            GBufferTest() {
                // You can do set-up work for each test here.
            }
            
            virtual ~GBufferTest() {
                // You can do clean-up work that doesn't throw exceptions here.
            }
            
            // If the constructor and destructor are not enough for setting up
            // and cleaning up each test, you can define the following methods:
            
            virtual void SetUp() {
                // Code here will be called immediately after the constructor (right
                // before each test).
                
                mock_ = new OpenGLMock();
                GLFacade::Mock(mock_);
                
//                ON_CALL(*mock_, CheckFramebufferStatus(_))
//                .WillByDefault(Return(GL_FRAMEBUFFER_COMPLETE));
            }
            
            virtual void TearDown() {
                // Code here will be called immediately after each test (right
                // before the destructor).
                
                delete mock_;
            }
            
            OpenGLMock* mock_;
            
            // Objects declared here can be used by all tests in the test case for Foo.
        };
        
        
        
        TEST_F(GBufferTest, Test1)
        {
            InSequence s;
            
            EXPECT_CALL(*mock_, GenFramebuffers(_, _))
            .Times(1)
            .WillOnce(SetArgPointee<1>(135));
            
            EXPECT_CALL(*mock_, BindFramebuffer(GL_DRAW_FRAMEBUFFER, 135)).Times(1);
            EXPECT_CALL(*mock_, BindFramebuffer(GL_DRAW_FRAMEBUFFER, 0)).Times(1);
            
            bounce::GBuffer g_buffer;
            g_buffer.Init(0, 0);
        }
        
//        TEST_F(GBufferTest, Test2)
//        {
//            EXPECT_CALL(*mock_, GenFramebuffers(_, _));
//            
//            bounce::GBuffer g_buffer;
//            
//            g_buffer.Init(0, 0);
//        }
        
    }
}
