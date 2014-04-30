#include "gtest/gtest.h"
#include "LockFreeQueue.h"

namespace bounce {
namespace tests {

class LockFreeQueueTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	LockFreeQueueTest() {
		// You can do set-up work for each test here.
	}

	virtual ~LockFreeQueueTest() {
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

TEST_F(LockFreeQueueTest, consume_from_empty_queue_returns_false) {
	bounce::LockFreeQueue<int> queue;
	int item;
	bool result = queue.consume(item);

	EXPECT_FALSE(result);
}

TEST_F(LockFreeQueueTest, consume_from_queue_with_one_item_returns_true) {
	bounce::LockFreeQueue<int> queue;
	queue.produce(1);
	int item;
	bool result = queue.consume(item);

	EXPECT_TRUE(result);
}

}
}
