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
	  MOCK_CONST_METHOD2(DoPair, IStrategy::Action(const std::vector<Card*>& playerCards, const Card* dealerFaceCard));
	  MOCK_CONST_METHOD2(DoSoft, IStrategy::Action(const std::vector<Card*>& playerCards, const Card* dealerFaceCard));
	  MOCK_CONST_METHOD2(DoHard, IStrategy::Action(const std::vector<Card*>& playerCards, const Card* dealerFaceCard));
	  MOCK_CONST_METHOD1(GetHardKey, std::string(int val));
	  MOCK_CONST_METHOD1(GetSoftKey, std::string(int val));
	  MOCK_CONST_METHOD1(GetPairKey, std::string(int val));
};

#endif /* MOCKACTIONHELPER_H_ */
