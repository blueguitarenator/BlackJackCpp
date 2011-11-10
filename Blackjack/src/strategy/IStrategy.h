/*
 * IStrategy.h
 *
 *  Created on: Nov 7, 2011
 *      Author: richardjohnson
 */

#ifndef ISTRATEGY_H_
#define ISTRATEGY_H_

#include <vector>

class Card;

class IStrategy
{
public:
	enum Action
	{
		STAY,
		HIT,
		DOUBLE,
		SPLIT,
		BUST
	};

	virtual Action Execute(std::vector<Card*>& playerCards, Card* dealerFaceCard) = 0;
};

#endif /* ISTRATEGY_H_ */
