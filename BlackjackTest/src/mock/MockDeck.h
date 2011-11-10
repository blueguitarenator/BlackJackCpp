/*
 * MockDeck.h
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#ifndef MOCKDECK_H_
#define MOCKDECK_H_

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "IDeck.h"

class MockDeck: public IDeck {
public:

	  MOCK_METHOD0(Next, Card*());
	  MOCK_METHOD0(Shuffle, void());
};

#endif /* MOCKDECK_H_ */
