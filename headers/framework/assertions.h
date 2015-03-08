#ifndef BOUNCE_FRAMEWORK_ASSERTIONS_H_
#define BOUNCE_FRAMEWORK_ASSERTIONS_H_

#include <limits>
#include <cassert>

namespace bounce {
    
    template <class TargetType, class ValueType>
    void AssertInRange(ValueType value)
    {
        assert(value >= 0 || std::numeric_limits<TargetType>::is_signed);
        assert(value >= std::numeric_limits<TargetType>::min());
        assert(value <= std::numeric_limits<TargetType>::max());
    }
    
}

#define ASSERT_IN_RANGE(val, type) ::bounce::AssertInRange<type>(val)

#endif // BOUNCE_FRAMEWORK_ASSERTIONS_H_
