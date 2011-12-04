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

	virtual IStrategy::Action DoPair(const std::vector<Card*>& playerCards, const Card* dealerFaceCard) const = 0;
	virtual IStrategy::Action DoSoft(const std::vector<Card*>& playerCards, const Card* dealerFaceCard) const = 0;
	virtual IStrategy::Action DoHard(const std::vector<Card*>& playerCards, const Card* dealerFaceCard) const = 0;
	virtual std::string GetHardKey(int val) const = 0;
	virtual std::string GetSoftKey(int val) const = 0;
	virtual std::string GetPairKey(int val) const = 0;

};

#endif /* IACTIONHELPER_H_ */
