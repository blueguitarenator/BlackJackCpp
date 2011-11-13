/*
 * MockDealer.h
 *
 *  Created on: Nov 10, 2011
 *      Author: richardjohnson
 */

#ifndef MOCKDEALER_H_
#define MOCKDEALER_H_

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "IDealer.h"

class MockDealer: public IDealer {
public:

	  MOCK_METHOD0(Deal, bool());
	  MOCK_METHOD1(DealHits, void(IPlayer* p));
	  MOCK_METHOD0(FinishUp, int());
	  MOCK_METHOD0(GetValue, int());
//	  MOCK_METHOD0(CheckBlackjack, bool());
};

#endif /* MOCKDEALER_H_ */
