#include <gtest/gtest.h>


#include "hello.h"

TEST(HelloTest, Hello) {
	EXPECT_STREQ("hello world", hello());
}

int main()
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
