#include "Player.h"

#include <gtest/gtest.h>


class PlayerTest : public ::testing::Test
{
protected:
	Player player{ "Alice" };
};

TEST_F(PlayerTest, PlayerName)
{
	EXPECT_EQ(player.GetName(), "Alice");
}

