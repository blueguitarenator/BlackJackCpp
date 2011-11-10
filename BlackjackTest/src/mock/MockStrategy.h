/*
 * MockStrategy.h
 *
 *  Created on: Nov 7, 2011
 *      Author: richardjohnson
 */

#ifndef MOCKSTRATEGY_H_
#define MOCKSTRATEGY_H_

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "strategy/IStrategy.h"
#include "Card.h"
#include <vector>

class MockStrategy: public IStrategy {
public:

  MOCK_METHOD2(Execute, IStrategy::Action(std::vector<Card*>&, Card*));
};


#endif /* MOCKSTRATEGY_H_ */
