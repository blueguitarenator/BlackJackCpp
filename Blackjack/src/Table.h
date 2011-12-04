/*
 * Table.h
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */


#ifndef TABLE_H_
#define TABLE_H_

#include "ITable.h"

class Card;
class IPlayer;

class Table : public ITable {
public:
	Table(IPlayer& p1, IPlayer& p2);
	~Table();
	IPlayer* P1();
	IPlayer* P2();
	void SetDealerCard(Card* c);
	Card* GetDealerCard();
	void Reset();
	void CheckPlayerBlackJacks();

	void Print();

	inline int GetP1Wager(){return m_p1Wager;}
	inline int GetP2Wager(){return m_p2Wager;}

private:
	IPlayer& m_p1;
	IPlayer& m_p2;
	Card* m_dealerCard;
	int m_p1Wager;
	int m_p2Wager;
};

#endif /* TABLE_H_ */
