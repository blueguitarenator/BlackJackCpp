/*
 * NoStrategy.h
 *
 *  Created on: Nov 7, 2011
 *      Author: richardjohnson
 */

#ifndef NOSTRATEGY_H_
#define NOSTRATEGY_H_

#include "IStrategy.h"

class NoStrategy: public IStrategy {
public:
	NoStrategy();
	virtual ~NoStrategy();

	Action Execute(std::vector<Card*>& playerCards, Card* dealerFaceCard);
};

#endif /* NOSTRATEGY_H_ */
