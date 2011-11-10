/*
 * DealerTest.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */


#include <gtest/gtest.h>
#include "Dealer.h"
#include "Table.h"
#include "mock/MockPlayer.h"
#include "mock/MockDeck.h"

class TableFixture : public ::testing::Test {
public:
	MockPlayer p1;
	MockPlayer p2;
	MockDeck deck;
	Table* table;
	Dealer* dealer;

	TableFixture( ) {
       // initialization code here
   }

   void SetUp( ) {
       // code here will execute just before the test ensues
		table = new Table(p1, p2);
		dealer = new Dealer(deck, *table);
   }

   void TearDown( ) {
       // code here will be called just after the test completes
       // ok to through exceptions from here if need be
	   delete table;
	   delete dealer;
   }

   ~TableFixture( )  {
       // cleanup any pending stuff, but no exceptions allowed
   }

   // put in any custom data members that you need
};

TEST_F(TableFixture, DealsToPlayersAndDealer)
{
	using ::testing::_;
	EXPECT_CALL(p1, TakeCard(_)).Times(2);
	EXPECT_CALL(p2, TakeCard(_)).Times(2);
	EXPECT_CALL(deck, Next()).Times(6);
	dealer->Deal();
	EXPECT_EQ(2, dealer->Count());
}

TEST_F(TableFixture, DealerShowingTopCard)
{
	using ::testing::_;
	using ::testing::Return;
	EXPECT_CALL(p1, TakeCard(_)).Times(2);
	EXPECT_CALL(p2, TakeCard(_)).Times(2);
	EXPECT_CALL(deck, Next())
		.Times(6)
		.WillRepeatedly(Return(new Card(3, Card::DIAMOND)));
	dealer->Deal();
	EXPECT_TRUE(table->GetDealerCard()->Value() == 3);
	EXPECT_TRUE(table->GetDealerCard()->Suit() == Card::DIAMOND);
}

class DealerTestFriend
{
public:
	inline void AddCard(Card* c, Dealer* d)
	{
		d->m_cards.push_back(c);
	}

};

TEST_F(TableFixture, DealerDrawsCardsUnder17)
{
	using ::testing::_;
	using ::testing::Return;
	DealerTestFriend f;
	EXPECT_CALL(deck, Next())
		.Times(2)
		.WillRepeatedly(Return(new Card(3, Card::DIAMOND)));

	f.AddCard(new Card(6, Card::HEART), dealer);
	f.AddCard(new Card(6, Card::HEART), dealer);

	EXPECT_EQ(18, dealer->FinishUp());
}

TEST_F(TableFixture, DealerHits16)
{
	using ::testing::_;
	using ::testing::Return;
	DealerTestFriend f;
	EXPECT_CALL(deck, Next())
		.Times(1)
		.WillRepeatedly(Return(new Card(6, Card::DIAMOND)));

	f.AddCard(new Card(10, Card::HEART), dealer);
	f.AddCard(new Card(6, Card::HEART), dealer);

	EXPECT_EQ(22, dealer->FinishUp());
}

TEST_F(TableFixture, DealerStandsOn17)
{
	using ::testing::_;
	using ::testing::Return;
	DealerTestFriend f;

	f.AddCard(new Card(10, Card::HEART), dealer);
	f.AddCard(new Card(7, Card::HEART), dealer);

	EXPECT_EQ(17, dealer->FinishUp());
}

TEST_F(TableFixture, DealerDoubleDownsPlayer)
{
	using ::testing::_;
	using ::testing::Return;

	EXPECT_CALL(p1, Decision(_))
		.Times(1)
		.WillOnce(Return(IStrategy::DOUBLE));
	EXPECT_CALL(deck, Next())
		.Times(1)
		.WillRepeatedly(Return(new Card(6, Card::DIAMOND)));
	EXPECT_CALL(p1, TakeCard(_)).Times(1);

	dealer->DoHits(&p1);
}

TEST_F(TableFixture, DealerHitsUntilStay)
{
	using ::testing::_;
	using ::testing::Return;

	EXPECT_CALL(p1, Decision(_))
		.Times(3)
		.WillOnce(Return(IStrategy::HIT))
		.WillOnce(Return(IStrategy::HIT))
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_CALL(deck, Next())
		.Times(2)
		.WillRepeatedly(Return(new Card(6, Card::DIAMOND)));
	EXPECT_CALL(p1, TakeCard(_))
		.Times(2);

	dealer->DoHits(&p1);
}

TEST_F(TableFixture, DealerAllowsStay)
{
	using ::testing::_;
	using ::testing::Return;

	EXPECT_CALL(p1, Decision(_))
		.Times(1)
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_CALL(p1, TakeCard(_)).Times(0);

	dealer->DoHits(&p1);
}

TEST_F(TableFixture, DealerWhenPlaySplitsOnce)
{
	using ::testing::_;
	using ::testing::Return;

	MockPlayer pSplit;
	EXPECT_CALL(deck, Next())
		.Times(2)
		.WillRepeatedly(Return(new Card(6, Card::DIAMOND)));
	EXPECT_CALL(p1, Decision(_))
		.Times(2)
		.WillOnce(Return(IStrategy::SPLIT))
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_CALL(pSplit, Decision(_))
		.Times(1)
		.WillOnce(Return(IStrategy::STAY));
	EXPECT_CALL(p1, Split())
		.Times(1)
		.WillOnce(Return(&pSplit));
	EXPECT_CALL(p1, TakeCard(_)).Times(1);
	EXPECT_CALL(pSplit, TakeCard(_)).Times(1);

	dealer->DoHits(&p1);
}
