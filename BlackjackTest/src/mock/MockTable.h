/*
 * MockTable.h
 *
 *  Created on: Nov 10, 2011
 *      Author: richardjohnson
 */

#ifndef MOCKTABLE_H_
#define MOCKTABLE_H_

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "ITable.h"

class MockTable: public ITable {
public:

	  MOCK_METHOD0(P1, IPlayer*());
	  MOCK_METHOD0(P2, IPlayer*());
	  MOCK_METHOD1(SetDealerCard, void(Card*));
	  MOCK_METHOD0(GetDealerCard, Card*());
	  MOCK_METHOD0(Reset, void());
	  MOCK_METHOD0(GetP1Wager, int());
	  MOCK_METHOD0(GetP2Wager, int());
	  MOCK_METHOD0(CheckPlayerBlackJacks, void());
	  MOCK_METHOD0(Print, void());
};

#endif /* MOCKTABLE_H_ */
