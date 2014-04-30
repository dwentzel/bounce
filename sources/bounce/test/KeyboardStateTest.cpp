#include "gtest/gtest.h"
#include "KeyboardState.hpp"

namespace bounce {
namespace tests {

class KeyboardStateTest : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	KeyboardStateTest() {
		// You can do set-up work for each test here.
	}

	virtual ~KeyboardStateTest() {
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

	KeyboardState subject;
};

TEST_F(KeyboardStateTest, Key_A_is_up_by_default) {
	EXPECT_FALSE(subject.isDown(Key::A));
}

TEST_F(KeyboardStateTest, Key_A_is_down_after_keydown_event) {
	Keysym keySym;
	keySym.sym = Key::A;

	KeydownEvent event(keySym);
	subject.processEvent(event);
	EXPECT_TRUE(subject.isDown(Key::A));
}


}
}
