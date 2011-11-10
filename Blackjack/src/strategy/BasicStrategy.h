/*
 * BasicStrategy.h
 *
 *  Created on: Nov 7, 2011
 *      Author: richardjohnson
 */

#ifndef BASICSTRATEGY_H_
#define BASICSTRATEGY_H_

#include "IStrategy.h"
#include "IActionHelper.h"
#include <vector>

class BasicStrategy: public IStrategy {
public:
	BasicStrategy(IActionHelper&);
	virtual ~BasicStrategy();

	Action Execute(std::vector<Card*>& playerCards, Card* dealerFaceCard);
private:
	IActionHelper& m_helper;
	int Total(std::vector<Card*>& cards);
};

#endif /* BASICSTRATEGY_H_ */
