/*
 * IActionHelper.h
 *
 *  Created on: Nov 9, 2011
 *      Author: richardjohnson
 */

#ifndef IACTIONHELPER_H_
#define IACTIONHELPER_H_

#include "IStrategy.h"
#include <vector>
#include <string>

class Card;

class IActionHelper {
public:
	virtual ~IActionHelper(){};

	virtual IStrategy::Action DoPair(std::vector<Card*>& playerCards, Card* dealerFaceCard) = 0;
	virtual IStrategy::Action DoSoft(std::vector<Card*>& playerCards, Card* dealerFaceCard) = 0;
	virtual IStrategy::Action DoHard(std::vector<Card*>& playerCards, Card* dealerFaceCard) = 0;
	virtual std::string GetHardKey(int val) = 0;
	virtual std::string GetSoftKey(int val) = 0;
	virtual std::string GetPairKey(int val) = 0;

};

#endif /* IACTIONHELPER_H_ */
