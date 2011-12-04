/*
 * ITable.h
 *
 *  Created on: Nov 10, 2011
 *      Author: richardjohnson
 */

#ifndef ITABLE_H_
#define ITABLE_H_

class IPlayer;
class Card;

class ITable
{
public:
	virtual IPlayer* P1() = 0;
	virtual IPlayer* P2() = 0;
	virtual void SetDealerCard(Card* c) = 0;
	virtual Card* GetDealerCard() = 0;
	virtual void Reset() = 0;
	virtual int GetP1Wager() = 0;
	virtual int GetP2Wager() = 0;
	virtual void CheckPlayerBlackJacks() = 0;

	virtual void Print() = 0;
};


#endif /* ITABLE_H_ */
