#include "Player.h"

#include <gtest/gtest.h>


namespace test
{
	class PlayerTest : public ::testing::Test
	{
	protected:
		game::Player player{ "Alice" };
	};

	TEST_F(PlayerTest, PlayerName)
	{
		EXPECT_EQ(player.GetName(), "Alice");
	}
}

