/*
 * Game.h
 *
 *  Created on: Nov 9, 2011
 *      Author: richardjohnson
 */

#ifndef GAME_H_
#define GAME_H_


#include "IDeck.h"
#include "Card.h"
#include "ITable.h"
#include "IDealer.h"
#include <iostream>
#include <string>
#include "strategy/IStrategy.h"

class Game {
public:
	Game(ITable& table, IDealer& dealer);
	virtual ~Game();

	void Play(int rounds);

private:
	void PrintTable();
//	void PrintDecisions(IStrategy::Action a1, IStrategy::Action a2);
	std::string GetActionString(IStrategy::Action a);
	void Settle();
	void DoSettle(IPlayer* p);

	ITable& m_table;
	IDealer& m_dealer;

};

#endif /* GAME_H_ */
