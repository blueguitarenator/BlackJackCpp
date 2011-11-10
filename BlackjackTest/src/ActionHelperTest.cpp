/*
 * ActionHelperTest.cpp
 *
 *  Created on: Nov 9, 2011
 *      Author: richardjohnson
 */


#include <gtest/gtest.h>
#include "strategy/ActionHelper.h"
#include <vector>
#include "Card.h"

TEST(ActionHelperTest, HardShouldStandOn21)
{
	std::vector<Card*> cards;
	cards.push_back(new Card(10, Card::HEART));
	cards.push_back(new Card(14, Card::HEART));
	Card* dealerFace = new Card(3, Card::HEART);
	ActionHelper helper;
	EXPECT_EQ(IStrategy::STAY, helper.DoHard(cards, dealerFace));
}

TEST(ActionHelperTest, HardShouldDoubleOn9ToDealer5)
{
	std::vector<Card*> cards;
	cards.push_back(new Card(6, Card::HEART));
	cards.push_back(new Card(3, Card::HEART));
	Card* dealerFace = new Card(5, Card::HEART);
	ActionHelper helper;
	EXPECT_EQ(IStrategy::DOUBLE, helper.DoHard(cards, dealerFace));
}

TEST(ActionHelperTest, HardShouldHitOn16ToDealer7)
{
	std::vector<Card*> cards;
	cards.push_back(new Card(10, Card::HEART));
	cards.push_back(new Card(6, Card::HEART));
	Card* dealerFace = new Card(7, Card::HEART);
	ActionHelper helper;
	EXPECT_EQ(IStrategy::HIT, helper.DoHard(cards, dealerFace));
}

TEST(ActionHelperTest, SplitOnAA)
{
	std::vector<Card*> cards;
	cards.push_back(new Card(14, Card::HEART));
	cards.push_back(new Card(14, Card::HEART));
	Card* dealerFace = new Card(10, Card::HEART);
	ActionHelper helper;
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, dealerFace));
}

TEST(ActionHelperTest, SplitOn88)
{
	std::vector<Card*> cards;
	cards.push_back(new Card(8, Card::HEART));
	cards.push_back(new Card(8, Card::HEART));
	Card* dealerFace = new Card(10, Card::HEART);
	ActionHelper helper;
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, dealerFace));
}

TEST(ActionHelperTest, DoNotSplitOn55)
{
	std::vector<Card*> cards;
	cards.push_back(new Card(5, Card::HEART));
	cards.push_back(new Card(5, Card::HEART));
	Card* dealerFace = new Card(2, Card::HEART);
	ActionHelper helper;
	EXPECT_EQ(IStrategy::DOUBLE, helper.DoPair(cards, dealerFace));
}

TEST(ActionHelperTest, Split22_33_77_vs_2thru7)
{
	std::vector<Card*> cards;
	cards.push_back(new Card(2, Card::HEART));
	cards.push_back(new Card(2, Card::HEART));
	ActionHelper helper;
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(2, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(3, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(4, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(5, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(6, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(7, Card::HEART)));
	cards.clear();
	cards.push_back(new Card(3, Card::HEART));
	cards.push_back(new Card(3, Card::HEART));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(2, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(3, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(4, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(5, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(6, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(7, Card::HEART)));
	cards.clear();
	cards.push_back(new Card(7, Card::HEART));
	cards.push_back(new Card(7, Card::HEART));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(2, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(3, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(4, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(5, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(6, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(7, Card::HEART)));
}

TEST(ActionHelperTest, Split44versus5and6)
{
	std::vector<Card*> cards;
	cards.push_back(new Card(4, Card::HEART));
	cards.push_back(new Card(4, Card::HEART));
	ActionHelper helper;
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(5, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(6, Card::HEART)));
}

TEST(ActionHelperTest, Split66versus3thru6)
{
	std::vector<Card*> cards;
	cards.push_back(new Card(6, Card::HEART));
	cards.push_back(new Card(6, Card::HEART));
	ActionHelper helper;
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(3, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(4, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(5, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(6, Card::HEART)));
}

TEST(ActionHelperTest, Split99versus2thru9butNot7)
{
	std::vector<Card*> cards;
	cards.push_back(new Card(9, Card::HEART));
	cards.push_back(new Card(9, Card::HEART));
	ActionHelper helper;
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(2, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(3, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(4, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(5, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(6, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(8, Card::HEART)));
	EXPECT_EQ(IStrategy::SPLIT, helper.DoPair(cards, new Card(9, Card::HEART)));
}

TEST(ActionHelperTest, Soft13ShouldDoubleVersus6)
{
	std::vector<Card*> cards;
	cards.push_back(new Card(14, Card::HEART));
	cards.push_back(new Card(2, Card::HEART));
	Card* dealerFace = new Card(6, Card::HEART);
	ActionHelper helper;
	EXPECT_EQ(IStrategy::DOUBLE, helper.DoSoft(cards, dealerFace));
}


