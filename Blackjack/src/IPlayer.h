/*
 * IPlayer.h
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#ifndef IPLAYER_H_
#define IPLAYER_H_

#include "strategy/IStrategy.h"
class Card;

class IPlayer
{
public:
	virtual ~IPlayer() {}
	virtual void TakeCard(Card* c) = 0;
	virtual int Count() = 0;
	virtual int Ante() = 0;
	virtual IStrategy::Action Decision(Card* dealerFace) = 0;
	virtual IPlayer* Split() = 0;
	virtual void ShowCards(){};
	virtual void Wins() = 0;
	virtual void Push() = 0;
	virtual bool Blackjack() = 0;
	virtual int GetBank() = 0;
	virtual int GetValue() = 0;
	virtual std::vector<IPlayer*>* GetSplits() = 0;
	virtual void TakeSplitsBank() = 0;
	virtual bool In() = 0;
	virtual void Lose() = 0;
};

#endif /* IPLAYER_H_ */
