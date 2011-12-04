/*
 * Dealer.h
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#ifndef DEALER_H_
#define DEALER_H_

#include "IDealer.h"
#include <vector>
class IDeck;
class Card;
class ITable;
class IPlayer;

class Dealer : public IDealer {
public:
	Dealer(IDeck& d, ITable& t);
	virtual ~Dealer();

	bool Deal();
	void DealHits(IPlayer* p);
	int FinishUp();
	int GetValue();

	friend class DealerTestFriend;
private:
	ITable& m_table;
	IDeck& m_deck;
	std::vector<Card*> m_cards;

	bool CheckBlackjack();
	int Count();
	bool IsSoft17();

};

#endif /* DEALER_H_ */
