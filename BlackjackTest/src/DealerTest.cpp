/*
 * DealerTest.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */


#include <gtest/gtest.h>
#include "Dealer.h"
#include "mock/MockTable.h"
#include "mock/MockPlayer.h"
#include "mock/MockDeck.h"
#include "Card.h"

class DealerTestFriend
{
public:
	inline void AddCard(Card* c, Dealer& d)
	{
		d.m_cards.push_back(c);
	}
	int Count(Dealer& d){return d.Count();}

};


class DealerFixture : public ::testing::Test {
public:
//	MockPlayer p1;
	MockPlayer player;
	MockDeck deck;
	MockTable table;
//	Dealer* dealer;
	DealerTestFriend dealerFriend;
	Card* sixDiamonds;
	DealerFixture( ) {
       // initialization code here
   }

   void SetUp( ) {
       // code here will execute just before the test ensues
//		table = new Table(p1, p2);
//		dealer = new Dealer(deck, table);
	   sixDiamonds  = new Card(6, Card::DIAMOND);
   }

   void TearDown( ) {
       // code here will be called just after the test completes
       // ok to through exceptions from here if need be
//	   delete table;
//	   delete dealer;
   }

   ~DealerFixture( )  {
       // cleanup any pending stuff, but no exceptions allowed
   }

   // put in any custom data members that you need
};

TEST_F(DealerFixture, DealsToPlayersAndDealer)
{
	using ::testing::Return;
	using ::testing::_;
	EXPECT_CALL(table, P1()).Times(2).WillRepeatedly(Return(&player));
	EXPECT_CALL(table, P2()).Times(2).WillRepeatedly(Return(&player));
	EXPECT_CALL(table, SetDealerCard(_));
	EXPECT_CALL(player, TakeCard(_)).Times(4);
	EXPECT_CALL(deck, Next()).Times(6).WillRepeatedly(Return(new Card(5, Card::DIAMOND)));
	EXPECT_CALL(deck, Shuffle()).Times(1);
	Dealer dealer(deck, table);
	dealer.Deal();
	EXPECT_EQ(2, dealerFriend.Count(dealer));
}

TEST_F(DealerFixture, DealerShowingTopCard)
{
	using ::testing::_;
	using ::testing::Return;
	EXPECT_CALL(table, P1()).Times(2).WillRepeatedly(Return(&player));
	EXPECT_CALL(table, P2()).Times(2).WillRepeatedly(Return(&player));
	EXPECT_CALL(table, SetDealerCard(_));
	EXPECT_CALL(player, TakeCard(_)).Times(4);
	EXPECT_CALL(deck, Shuffle()).Times(1);
	EXPECT_CALL(deck, Next())
		.Times(6)
		.WillRepeatedly(Return(new Card(3, Card::DIAMOND)));
//	EXPECT_CALL(table, GetDealerCard()).Times(2);
	Dealer dealer(deck, table);
	dealer.Deal();
}

TEST_F(DealerFixture, DealerDrawsCardsUnder17)
{
	using ::testing::_;
	using ::testing::Return;
	DealerTestFriend f;
	EXPECT_CALL(deck, Shuffle()).Times(1);
	EXPECT_CALL(deck, Next())
		.Times(2)
		.WillRepeatedly(Return(new Card(3, Card::DIAMOND)));

	Dealer dealer(deck, table);
	f.AddCard(new Card(6, Card::HEART), dealer);
	f.AddCard(new Card(6, Card::HEART), dealer);

	EXPECT_EQ(18, dealer.FinishUp());
}

TEST_F(DealerFixture, DealerHits16)
{
	using ::testing::_;
	using ::testing::Return;
	DealerTestFriend f;
	EXPECT_CALL(deck, Shuffle()).Times(1);
	EXPECT_CALL(deck, Next())
		.Times(1)
		.WillRepeatedly(Return(new Card(6, Card::DIAMOND)));

	Dealer dealer(deck, table);
	f.AddCard(new Card(10, Card::HEART), dealer);
	f.AddCard(new Card(6, Card::HEART), dealer);
	EXPECT_EQ(22, dealer.FinishUp());
}

TEST_F(DealerFixture, DealerStandsOn17)
{
	using ::testing::_;
	using ::testing::Return;
	DealerTestFriend f;

	EXPECT_CALL(deck, Shuffle()).Times(1);
	Dealer dealer(deck, table);
	f.AddCard(new Card(10, Card::HEART), dealer);
	f.AddCard(new Card(7, Card::HEART), dealer);
	EXPECT_EQ(17, dealer.FinishUp());
}

TEST_F(DealerFixture, DealerDoubleDownsPlayer)
{
	using ::testing::_;
	using ::testing::Return;
	using ::testing::AnyNumber;

	EXPECT_CALL(player, GetValue()).Times(AnyNumber()).WillRepeatedly(Return(17));
	EXPECT_CALL(table, GetDealerCard());
	EXPECT_CALL(player, Decision(_))
		.Times(1)
		.WillOnce(Return(IStrategy::DOUBLE));
	EXPECT_CALL(deck, Shuffle()).Times(1);
	EXPECT_CALL(deck, Next())
		.Times(1)
		.WillRepeatedly(Return(new Card(6, Card::DIAMOND)));
	EXPECT_CALL(player, TakeCard(_)).Times(1);
	Dealer dealer(deck, table);
	dealer.DealHits(&player);
}

TEST_F(DealerFixture, DealerHitsUntilStay)
{
	using ::testing::_;
	using ::testing::Return;
	using ::testing::AnyNumber;

	EXPECT_CALL(player, GetValue()).Times(AnyNumber()).WillRepeatedly(Return(17));
	EXPECT_CALL(table, GetDealerCard());
	EXPECT_CALL(player, Decision(_))
		.Times(3)
		.WillOnce(Return(IStrategy::HIT))
		.WillOnce(Return(IStrategy::HIT))
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_CALL(deck, Shuffle()).Times(1);
	EXPECT_CALL(deck, Next())
		.Times(2)
		.WillRepeatedly(Return(new Card(6, Card::DIAMOND)));
	EXPECT_CALL(player, TakeCard(_))
		.Times(2);
	Dealer dealer(deck, table);
	dealer.DealHits(&player);
}

TEST_F(DealerFixture, DealerAllowsStay)
{
	using ::testing::_;
	using ::testing::Return;
	using ::testing::AnyNumber;

	EXPECT_CALL(player, GetValue()).Times(AnyNumber()).WillRepeatedly(Return(17));
	EXPECT_CALL(table, GetDealerCard());
	EXPECT_CALL(player, Decision(_))
		.Times(1)
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_CALL(deck, Shuffle()).Times(1);
	EXPECT_CALL(player, TakeCard(_)).Times(0);
	Dealer dealer(deck, table);
	dealer.DealHits(&player);
}

TEST_F(DealerFixture, DealerWhenPlaySplitsOnce)
{
	using ::testing::_;
	using ::testing::Return;
	using ::testing::AnyNumber;

	MockPlayer pSplit;
	EXPECT_CALL(player, GetValue()).Times(AnyNumber()).WillRepeatedly(Return(1));
	EXPECT_CALL(pSplit, GetValue()).Times(AnyNumber()).WillRepeatedly(Return(1));
	EXPECT_CALL(table, GetDealerCard()).Times(AnyNumber());
	EXPECT_CALL(deck, Shuffle()).Times(1);
	EXPECT_CALL(deck, Next())
		.Times(2)
		.WillRepeatedly(Return(sixDiamonds));
	EXPECT_CALL(player, Decision(_))
		.Times(2)
		.WillOnce(Return(IStrategy::SPLIT))
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_CALL(pSplit, Decision(_))
		.Times(1)
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_CALL(player, Split())
		.Times(1)
		.WillOnce(Return(&pSplit));
	EXPECT_CALL(player, TakeCard(_)).Times(1);
	EXPECT_CALL(pSplit, TakeCard(_)).Times(1);
	Dealer dealer(deck, table);
	dealer.DealHits(&player);
}

TEST_F(DealerFixture, DealerWhenPlaySplitsTwice)
{
	using ::testing::_;
	using ::testing::Return;
	using ::testing::AnyNumber;

	MockPlayer pSplit;
	MockPlayer pSplit2;
	EXPECT_CALL(player, GetValue()).Times(AnyNumber()).WillRepeatedly(Return(1));
	EXPECT_CALL(pSplit, GetValue()).Times(AnyNumber()).WillRepeatedly(Return(1));
	EXPECT_CALL(table, GetDealerCard()).Times(AnyNumber()).WillRepeatedly(Return(sixDiamonds));
	EXPECT_CALL(deck, Shuffle()).Times(1);
	EXPECT_CALL(deck, Next())
		.Times(4)
		.WillRepeatedly(Return(sixDiamonds));
	EXPECT_CALL(player, Decision(_))
		.Times(2)
		.WillOnce(Return(IStrategy::SPLIT))
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_CALL(pSplit, Decision(_))
		.Times(2)
		.WillOnce(Return(IStrategy::SPLIT))
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_CALL(player, Split())
		.Times(1)
		.WillOnce(Return(&pSplit));
	EXPECT_CALL(pSplit, Split())
		.Times(1)
		.WillOnce(Return(&pSplit2));
	EXPECT_CALL(player, TakeCard(_)).Times(1);
	EXPECT_CALL(pSplit, TakeCard(_)).Times(2);
	EXPECT_CALL(pSplit2, TakeCard(_)).Times(1);
	Dealer dealer(deck, table);
	dealer.DealHits(&player);
}
