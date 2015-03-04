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
                    REQUIRES(ok == true);
                }
                
                void MethodWithPostcondition(int x)
                {
                    ENSURES(x == 10);
                    
                    x = x * 2;
                }
            };
            
            void FunctionWithPrecondition(bool ok)
            {
                REQUIRES(ok == true);
            }
            
            void FuncitonWithPostCondition(int x)
            {
                ENSURES(x == 10);
                ENSURES(x == 10);
                
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
            
            //        TEST_F(LockFreeQueueTest, consume_from_empty_queue_returns_false) {
            //            bounce::LockFreeQueue<int> queue;
            //            int item;
            //            bool result = queue.consume(item);
            //
            //            EXPECT_FALSE(result);
            //        }
            //
            //        TEST_F(LockFreeQueueTest, consume_from_queue_with_one_item_returns_true) {
            //            bounce::LockFreeQueue<int> queue;
            //            queue.produce(1);
            //            int item;
            //            bool result = queue.consume(item);
            //
            //            EXPECT_TRUE(result);
            //        }
            //
            //        TEST_F(LockFreeQueueTest, consume_from_empty_unique_ptr_queue_returns_false) {
            //            bounce::LockFreeQueue<std::unique_ptr<int>> queue;
            //            std::unique_ptr<int> item;
            //            bool result = queue.consume(item);
            //
            //            EXPECT_FALSE(result);
            //        }

            
            
            //        TEST_F(CompositeCacheTest, test_1) {
            //            bounce::CompositeCache<ObjectBase, Object1, Object2> cache;
            //
            //            ObjectCacheHandle<ObjectBase> x = cache.Generate<0>();
            //
            //
            //            //EXPECT_TRUE(result);
            //        }
            //
            //        TEST_F(CompositeCacheTest, test_2) {
            //            bounce::CompositeCache<ObjectBase, Object1, Object2> cache;
            //
            //            ObjectCacheHandle<ObjectBase> x = cache.Generate<0>();
            //
            //            cache.Resolve<0>(x);
            //
            //            //EXPECT_TRUE(result);
            //        }
            
            
            
            //        TEST_F(LockFreeQueueTest, consume_from_queue_with_one_item_returns_true) {
            //            bounce::LockFreeQueue<int> queue;
            //            queue.produce(1);
            //            int item;
            //            bool result = queue.consume(item);
            //            
            //            EXPECT_TRUE(result);
            //        }
        }
    }
}