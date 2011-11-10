/*
 * TableTest.cpp
 *
 *  Created on: Nov 7, 2011
 *      Author: richardjohnson
 */


#include <gtest/gtest.h>
//#include "gmock/gmock.h"
#include "Dealer.h"
#include "Table.h"
#include "mock/MockPlayer.h"
#include "mock/MockDeck.h"

class TableFixture : public ::testing::Test {
public:
	MockPlayer p1;
	MockPlayer p2;
	MockDeck deck;
	Table* t;
	Dealer* d;

	TableFixture( ) {
       // initialization code here
   }

   void SetUp( ) {
       // code here will execute just before the test ensues
		t = new Table(p1, p2);
		d = new Dealer(deck, *t);
   }

   void TearDown( ) {
       // code here will be called just after the test completes
       // ok to through exceptions from here if need be
	   delete t;
	   delete d;
   }

   ~TableFixture( )  {
       // cleanup any pending stuff, but no exceptions allowed
   }

   // put in any custom data members that you need
};

TEST_F(TableFixture, ResetTableCallsForAnteAndResetsPlayerWager)
{
	using ::testing::Return;
	EXPECT_CALL(p1, Ante()).Times(2)
			.WillOnce(Return(10))
			.WillOnce(Return(10));
	EXPECT_CALL(p2, Ante()).Times(2)
			.WillOnce(Return(20))
			.WillOnce(Return(20));
	t->Reset();
	EXPECT_EQ(10, t->GetP1Wager());
	EXPECT_EQ(20, t->GetP2Wager());
	t->Reset();
	EXPECT_EQ(10, t->GetP1Wager());
	EXPECT_EQ(20, t->GetP2Wager());
}
