#include "assertions.h"


#include "gtest/gtest.h"


namespace bounce {
    namespace tests {
        
        TEST(InRangeTest, IntInShortRangeCauseNoErrors)
        {
            int x = 123;
            
            EXPECT_NO_FATAL_FAILURE(ASSERT_IN_RANGE(x, short));
        }

        TEST(InRangeTest, IntAboveShortRangeCausesFailure)
        {
            int x = std::numeric_limits<short>::max() + 1;
            
            EXPECT_DEATH(ASSERT_IN_RANGE(x, short), "");
        }
        
        TEST(InRangeTest, IntBelowShortRangeCausesFailure)
        {
            int x = std::numeric_limits<short>::min() - 1;
            
            EXPECT_DEATH(ASSERT_IN_RANGE(x, short), "");
        }
        
        TEST(InRangeTest, NegativeIntCausesFailureWithUnsignedInt)
        {
            int x = -1;
            
            EXPECT_DEATH(ASSERT_IN_RANGE(x, unsigned int), "");
        }
    }
}
