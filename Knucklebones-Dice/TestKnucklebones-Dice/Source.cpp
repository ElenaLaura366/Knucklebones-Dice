#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Board.h"

TEST(BoardTest, Constructor)
{
	Board board;
	EXPECT_EQ(board.getPlayer(), "");
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}