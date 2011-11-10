/*
 * Dealer.h
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#ifndef DEALER_H_
#define DEALER_H_

#include <vector>
class IDeck;
class Card;
class Table;
class IPlayer;

class Dealer {
public:
	Dealer(IDeck& d, Table& t);
	virtual ~Dealer();

	void Deal();
	int Count();
	void DoHits(IPlayer* p);
	int FinishUp();
	int GetValue();

	friend class DealerTestFriend;
private:
	Table& m_table;
	IDeck& m_deck;
	std::vector<Card*> m_cards;
};

#endif /* DEALER_H_ */
