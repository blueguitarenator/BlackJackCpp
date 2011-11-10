/*
 * Deck.h
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#ifndef DECK_H_
#define DECK_H_

#include <vector>
#include "IDeck.h"

class Deck : public IDeck {
public:
	Deck();
	virtual ~Deck();

	Card* Next();
	void Shuffle();

	int Count();
	void Print();

private:
	std::vector<Card*> m_deck;
	std::vector<Card*>::iterator iter;
};

#endif /* DECK_H_ */
