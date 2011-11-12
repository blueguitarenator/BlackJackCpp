/*
 * PlayerTest.cpp
 *
 *  Created on: Nov 7, 2011
 *      Author: richardjohnson
 */


#include <gtest/gtest.h>
#include "Player.h"
#include "mock/MockStrategy.h"

TEST(PlayerTest, PlayersAnteUp)
{
	MockStrategy s;
	Player p1(s);

	EXPECT_TRUE(p1.Ante() > 0);
}

TEST(PlayerTest, PlayerUsesStrategy)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	Card c(4, Card::HEART);
	Player p(s);
	EXPECT_CALL(s, Execute(_, _)).Times(1).WillOnce(Return(IStrategy::STAY));
	EXPECT_EQ(IStrategy::STAY, p.Decision(&c));
}

TEST(PlayerTest, PlayerSplits)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	Card c(4, Card::HEART);
	Player p(s);
	IPlayer* splitPlayer = p.Split();
	EXPECT_TRUE(splitPlayer != NULL);
	EXPECT_TRUE(splitPlayer->Ante() > 0);
}

TEST(PlayerTest, PlayerBankUpdatesDouble)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	Player p(s);
	EXPECT_CALL(s, Execute(_, _)).Times(1).WillOnce(Return(IStrategy::DOUBLE));
	EXPECT_EQ(100, p.GetBank());
	p.Ante();
	EXPECT_EQ(90, p.GetBank());
	EXPECT_EQ(10, p.GetBet());
	p.Decision(new Card(3, Card::HEART));
	EXPECT_EQ(80, p.GetBank());
	EXPECT_EQ(20, p.GetBet());
	p.Wins();
	EXPECT_EQ(120, p.GetBank());
}


TEST(PlayerTest, PlayerBankUpdatesBlackJack)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	Player p(s);
	EXPECT_EQ(100, p.GetBank());
	p.Ante();
	EXPECT_EQ(90, p.GetBank());
	EXPECT_EQ(10, p.GetBet());
	p.Blackjack();
	EXPECT_EQ(115, p.GetBank());
}

TEST(PlayerTest, PlayerBankUpdatesPush)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	Player p(s);
	EXPECT_EQ(100, p.GetBank());
	p.Ante();
	EXPECT_EQ(90, p.GetBank());
	EXPECT_EQ(10, p.GetBet());
	p.Push();
	EXPECT_EQ(100, p.GetBank());
}


