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

TEST_F(PlayerTest, UpdateScore)
{
	player.UpdateScore(10);
	EXPECT_EQ(player.GetScore(), 10);

	player.UpdateScore(5);
	EXPECT_EQ(player.GetScore(), 5);
}

