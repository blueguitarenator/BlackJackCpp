/*
 * MockActionHelper.h
 *
 *  Created on: Nov 9, 2011
 *      Author: richardjohnson
 */

#ifndef MOCKACTIONHELPER_H_
#define MOCKACTIONHELPER_H_


#include "gmock/gmock.h"  // Brings in Google Mock.
#include "strategy/IActionHelper.h"

class MockActionHelper: public IActionHelper {
public:
	  MOCK_METHOD2(DoPair, IStrategy::Action(std::vector<Card*>& playerCards, Card* dealerFaceCard));
	  MOCK_METHOD2(DoSoft, IStrategy::Action(std::vector<Card*>& playerCards, Card* dealerFaceCard));
	  MOCK_METHOD2(DoHard, IStrategy::Action(std::vector<Card*>& playerCards, Card* dealerFaceCard));
	  MOCK_METHOD1(GetHardKey, std::string(int val));
	  MOCK_METHOD1(GetSoftKey, std::string(int val));
	  MOCK_METHOD1(GetPairKey, std::string(int val));
};

#endif /* MOCKACTIONHELPER_H_ */
