#include "gtest/gtest.h"
#include "event.h"

namespace bounce {
    namespace tests {
        
        class EventManagerTest : public ::testing::Test {
        protected:
            // You can remove any or all of the following functions if its body
            // is empty.
            
            EventManagerTest() {
                // You can do set-up work for each test here.
            }
            
            virtual ~EventManagerTest() {
                // You can do clean-up work that doesn't throw exceptions here.
            }
            
            // If the constructor and destructor are not enough for setting up
            // and cleaning up each test, you can define the following methods:
            
            virtual void SetUp() {
                // Code here will be called immediately after the constructor (right
                // before each test).
            }
            
            virtual void TearDown() {
                // Code here will be called immediately after each test (right
                // before the destructor).
            }
            
            EventManager subject;
        };
        
        TEST_F(EventManagerTest, poll_event_on_new_manager_returns_nullptr) {
            EventPtr event = subject.PollEvent();
            
            EXPECT_TRUE(event == nullptr);
        }
        
//        TEST_F(EventManagerTest, Key_A_is_down_after_keydown_event) {
//            Keysym keySym;
//            keySym.sym = Key::A;
//            
//            KeydownEvent event(keySym);
//            subject.ProcessEvent(event);
//            EXPECT_TRUE(subject.IsDown(Key::A));
//        }
        
        
    }
}
