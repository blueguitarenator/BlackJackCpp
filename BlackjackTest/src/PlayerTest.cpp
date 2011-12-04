/*
 * PlayerTest.cpp
 *
 *  Created on: Nov 7, 2011
 *      Author: richardjohnson
 */


#include <gtest/gtest.h>
#include "Player.h"
#include "mock/MockStrategy.h"

class PlayerTestFriend
{
public:
	inline void AddCard(Card* c, Player& p)
	{
		p.m_cards.push_back(c);
	}
	inline int Count(Player& p){return p.m_cards.size();}
	inline std::vector<Card*>* GetCards(Player& p){return &p.m_cards;}
};

TEST(PlayerTest, PlayersAnteUp)
{
	MockStrategy s;
	Player p1(s, "Mock");

	EXPECT_TRUE(p1.Ante() > 0);
}

TEST(PlayerTest, PlayerUsesStrategy)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	Card c(4, Card::HEART);
	Player p(s, "Mock");
	EXPECT_CALL(s, Execute(_, _)).Times(1).WillOnce(Return(IStrategy::STAY));
	EXPECT_EQ(IStrategy::STAY, p.Decision(&c));
}

TEST(PlayerTest, PlayerSplits)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	PlayerTestFriend testFriend;
	Player p(s, "Mock");

	Card c1(4, Card::HEART);
	Card c2(4, Card::DIAMOND);
	testFriend.AddCard(&c1, p);
	testFriend.AddCard(&c2, p);
	IPlayer* splitPlayer = p.Split();
	EXPECT_EQ(1, testFriend.Count(p));
	EXPECT_TRUE(splitPlayer != NULL);
	EXPECT_EQ(4, p.GetValue());
	EXPECT_EQ(4, splitPlayer->GetValue());
	std::vector<Card*>* cards = testFriend.GetCards(p);
	Card* theCard = cards->at(0);
	EXPECT_EQ(Card::HEART, theCard->Suit());
	Player* splity = static_cast<Player*>(splitPlayer);
	cards = testFriend.GetCards(*splity);
	theCard = cards->at(0);
	EXPECT_EQ(Card::DIAMOND, theCard->Suit());
}

TEST(PlayerTest, PlayerBankUpdatesDouble)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	Player p(s, "Mock");
	EXPECT_CALL(s, Execute(_, _)).Times(1).WillOnce(Return(IStrategy::DOUBLE));
	EXPECT_EQ(0, p.GetBank());
	p.Ante();
	EXPECT_EQ(-10, p.GetBank());
	EXPECT_EQ(10, p.GetBet());
	p.Decision(new Card(3, Card::HEART));
	EXPECT_EQ(-20, p.GetBank());
	EXPECT_EQ(20, p.GetBet());
	p.Wins();
	EXPECT_EQ(20, p.GetBank());
}


TEST(PlayerTest, PlayerBankUpdatesBlackJack)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	PlayerTestFriend testFriend;
	Player p(s, "Mock");
	EXPECT_EQ(0, p.GetBank());
	p.Ante();
	testFriend.AddCard(new Card(10, Card::HEART), p);
	testFriend.AddCard(new Card(14, Card::HEART), p);
	EXPECT_EQ(21, p.GetValue());
	EXPECT_EQ(-10, p.GetBank());
	EXPECT_EQ(10, p.GetBet());
	p.Blackjack();
	EXPECT_EQ(15, p.GetBank());
	EXPECT_EQ(0, p.GetBet());
}

TEST(PlayerTest, PlayerBankUpdatesPush)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	Player p(s, "Mock");
	EXPECT_EQ(0, p.GetBank());
	p.Ante();
	EXPECT_EQ(-10, p.GetBank());
	EXPECT_EQ(10, p.GetBet());
	p.Push();
	EXPECT_EQ(0, p.GetBank());
}

TEST(PlayerTest, PlayerGetsSplitsBet)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	Player p(s, "Mock");
	PlayerTestFriend testFriend;
	p.Ante();
	testFriend.AddCard(new Card(10, Card::HEART), p);
	testFriend.AddCard(new Card(14, Card::HEART), p);
	IPlayer* split = p.Split();
	p.Wins();
	split->Wins();
	p.TakeSplitsBank();

	EXPECT_EQ(20, p.GetBank());
}

TEST(PlayerTest, PlayerLosesWhenSplitsLoses)
{
	using ::testing::_;
	using ::testing::Return;
	MockStrategy s;
	Player p(s, "Mock");
	PlayerTestFriend testFriend;
	p.Ante();
	testFriend.AddCard(new Card(10, Card::HEART), p);
	testFriend.AddCard(new Card(14, Card::HEART), p);
	IPlayer* split = p.Split();
	p.TakeSplitsBank();
	EXPECT_EQ(-10, split->GetBank());
	EXPECT_EQ(-20, p.GetBank());
}

TEST(PlayerTest, PlayerBust)
{
	MockStrategy s;
	Player p(s, "Mock");
	PlayerTestFriend testFriend;
	p.Ante();
	testFriend.AddCard(new Card(10, Card::HEART), p);
	testFriend.AddCard(new Card(5, Card::HEART), p);
	testFriend.AddCard(new Card(8, Card::HEART), p);
	IStrategy::Action action = p.Decision(new Card(5, Card::HEART));
	EXPECT_EQ(-10, p.GetBank());
	EXPECT_FALSE(p.In());
	EXPECT_EQ(IStrategy::BUST, action);
}

TEST(PlayerTest, PlayerGetValue)
{
	MockStrategy s;
	Player p(s, "Mock");
	PlayerTestFriend testFriend;
	testFriend.AddCard(new Card(14, Card::HEART), p);
	testFriend.AddCard(new Card(14, Card::HEART), p);

	EXPECT_EQ(12, p.GetValue());
	testFriend.AddCard(new Card(2, Card::HEART), p);
	EXPECT_EQ(14, p.GetValue());
	testFriend.AddCard(new Card(14, Card::HEART), p);
	EXPECT_EQ(15, p.GetValue());
	testFriend.AddCard(new Card(7, Card::HEART), p);
	EXPECT_EQ(12, p.GetValue());


}
