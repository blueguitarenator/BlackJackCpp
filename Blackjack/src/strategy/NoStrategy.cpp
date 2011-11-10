/*
 * NoStrategy.cpp
 *
 *  Created on: Nov 7, 2011
 *      Author: richardjohnson
 */

#include "NoStrategy.h"
#include "../Card.h"

NoStrategy::NoStrategy() {

}

NoStrategy::~NoStrategy() {
}

IStrategy::Action NoStrategy::Execute(std::vector<Card*>& playerCards, Card* dealerFaceCard)
{
	return IStrategy::STAY;
}
