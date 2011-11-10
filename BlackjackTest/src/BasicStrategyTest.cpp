/*
 * StrategyTest.cpp
 *
 *  Created on: Nov 7, 2011
 *      Author: richardjohnson
 */


#include <gtest/gtest.h>
#include "strategy/BasicStrategy.h"
#include <vector>
#include "Card.h"
#include "mock/MockActionHelper.h"

TEST(BasicStrategyTest, PairShouldCallDoPair)
{
	using ::testing::_;
	using ::testing::Return;

	MockActionHelper helper;
	std::vector<Card*> cards;
	cards.push_back(new Card(3, Card::HEART));
	cards.push_back(new Card(3, Card::HEART));
	Card* dealerFace = new Card(3, Card::HEART);
	BasicStrategy bs(helper);
	EXPECT_CALL(helper, DoPair(cards, dealerFace))
		.Times(1)
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_EQ(IStrategy::STAY, bs.Execute(cards, dealerFace));
}

TEST(BasicStrategyTest, Soft13ShouldCallDoSoft)
{
	using ::testing::_;
	using ::testing::Return;

	MockActionHelper helper;
	std::vector<Card*> cards;
	cards.push_back(new Card(14, Card::HEART));
	cards.push_back(new Card(2, Card::HEART));
	Card* dealerFace = new Card(3, Card::HEART);
	BasicStrategy bs(helper);
	EXPECT_CALL(helper, DoSoft(cards, dealerFace))
		.Times(1)
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_EQ(IStrategy::STAY, bs.Execute(cards, dealerFace));
}

TEST(BasicStrategyTest, Soft19ShouldStay)
{
	using ::testing::_;
	using ::testing::Return;

	MockActionHelper helper;
	std::vector<Card*> cards;
	cards.push_back(new Card(14, Card::HEART));
	cards.push_back(new Card(8, Card::HEART));
	Card* dealerFace = new Card(3, Card::HEART);
	BasicStrategy bs(helper);

	EXPECT_EQ(IStrategy::STAY, bs.Execute(cards, dealerFace));
}

TEST(BasicStrategyTest, 9ShouldHit)
{
	using ::testing::_;
	using ::testing::Return;

	MockActionHelper helper;
	std::vector<Card*> cards;
	cards.push_back(new Card(3, Card::HEART));
	cards.push_back(new Card(6, Card::HEART));
	Card* dealerFace = new Card(3, Card::HEART);
	BasicStrategy bs(helper);
	EXPECT_CALL(helper, DoHard(cards, dealerFace))
		.Times(1)
		.WillOnce(Return(IStrategy::HIT));

	EXPECT_EQ(IStrategy::HIT, bs.Execute(cards, dealerFace));
}

