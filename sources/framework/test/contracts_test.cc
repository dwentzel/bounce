#include "contrib/disable_clang_warnings.h"
#include "gtest/gtest.h"
#include "contrib/enable_clang_warnings.h"
#include "contracts.h"

namespace bounce {
    namespace contracts {
        namespace tests {
            
            class ContractsTest : public ::testing::Test {
            protected:
                // You can remove any or all of the following functions if its body
                // is empty.
                
                ContractsTest() {
                    // You can do set-up work for each test here.
                }
                
                virtual ~ContractsTest() {
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
                
                // Objects declared here can be used by all tests in the test case for Foo.
            };
            
            class Class
            {
            public:
                void MethodWithPrecondition(bool ok)
                {
                    CONTRACT_REQUIRES(ok == true);
                }
                
                void MethodWithPostcondition(int x)
                {
                    CONTRACT_ENSURES(x == 10);
                    
                    x = x * 2;
                }
            };
            
            void FunctionWithPrecondition(bool ok)
            {
                CONTRACT_REQUIRES(ok == true);
            }
            
            void FuncitonWithPostCondition(int x)
            {
                CONTRACT_ENSURES(x == 10);
                CONTRACT_ENSURES(x == 10);
                
                x = x * 2;
            }
            
            TEST_F(ContractsTest, test1) {
                EXPECT_DEATH(FunctionWithPrecondition(false), "");
            }
            
            TEST_F(ContractsTest, test2)
            {
                EXPECT_NO_FATAL_FAILURE(FunctionWithPrecondition(true));
            }
            
            TEST_F(ContractsTest, test3)
            {
                EXPECT_DEATH(FuncitonWithPostCondition(10), "");
            }
            
            TEST_F(ContractsTest, test4)
            {
                Class c;
                
                EXPECT_DEATH(c.MethodWithPrecondition(false), "");
            }
            
            TEST_F(ContractsTest, test5)
            {
                Class c;
                
                EXPECT_DEATH(c.MethodWithPostcondition(10), "");
            }
        }
    }
}