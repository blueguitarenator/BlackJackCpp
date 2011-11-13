/*
 * GameTest.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: richardjohnson
 */



#include <gtest/gtest.h>
#include "Game.h"
#include "gmock/gmock.h"
#include "mock/MockPlayer.h"
#include "mock/MockDeck.h"
#include "mock/MockTable.h"
#include "mock/MockDealer.h"


TEST(GameFixture, OneRoundDealerBlackjack)
{
	using ::testing::NiceMock;

	NiceMock<MockPlayer> mock_player;
	NiceMock<MockTable> mock_table;
	NiceMock<MockDealer> mock_dealer;
	MockDeck deck;

	using ::testing::Return;
	using ::testing::AnyNumber;
	using ::testing::_;
	std::vector<IPlayer*> splits;
	EXPECT_CALL(mock_table, Reset()).Times(1);
	EXPECT_CALL(mock_dealer, Deal()).Times(1).WillOnce(Return(true));
	EXPECT_CALL(mock_dealer, DealHits(_)).Times(0);
//	EXPECT_CALL(mock_dealer, GetValue())
//		.Times(2)
//		.WillRepeatedly(Return(21));
	EXPECT_CALL(mock_player, Wins()).Times(0);
//	ON_CALL(mock_player, GetSplits()).WillByDefault(Return(&splits));
//	ON_CALL(mock_player, GetValue()).WillByDefault(Return(10));
//	ON_CALL(mock_player, GetValue()).WillByDefault(Return(10));
	EXPECT_CALL(mock_table, P1()).Times(AnyNumber()).WillRepeatedly(Return(&mock_player));
	EXPECT_CALL(mock_table, P2()).Times(AnyNumber()).WillRepeatedly(Return(&mock_player));
	EXPECT_CALL(mock_table, GetDealerCard()).Times(2).WillRepeatedly(Return(new Card(4, Card::HEART)));
	Game game(mock_table, mock_dealer);
	game.Play(1);
}

TEST(GameFixture, OneRoundDealerBusts)
{
	using ::testing::NiceMock;

	NiceMock<MockPlayer> mock_player;
	NiceMock<MockTable> mock_table;
	NiceMock<MockDealer> mock_dealer;
	MockDeck deck;

	using ::testing::Return;
	using ::testing::AnyNumber;
	using ::testing::_;
	std::vector<IPlayer*> splits;
	EXPECT_CALL(mock_table, Reset()).Times(1);
	EXPECT_CALL(mock_dealer, Deal()).Times(1);
	EXPECT_CALL(mock_dealer, DealHits(_)).Times(2);
	EXPECT_CALL(mock_dealer, GetValue())
		.Times(2)
		.WillRepeatedly(Return(22));
	EXPECT_CALL(mock_player, Wins()).Times(2);
	ON_CALL(mock_player, GetSplits()).WillByDefault(Return(&splits));
	ON_CALL(mock_player, GetValue()).WillByDefault(Return(10));
	ON_CALL(mock_player, GetValue()).WillByDefault(Return(10));
	EXPECT_CALL(mock_table, P1()).Times(AnyNumber()).WillRepeatedly(Return(&mock_player));
	EXPECT_CALL(mock_table, P2()).Times(AnyNumber()).WillRepeatedly(Return(&mock_player));
	EXPECT_CALL(mock_table, GetDealerCard()).Times(4).WillRepeatedly(Return(new Card(4, Card::HEART)));
	Game game(mock_table, mock_dealer);
	game.Play(1);
}
