/*
 * Game.h
 *
 *  Created on: Nov 9, 2011
 *      Author: richardjohnson
 */

#ifndef GAME_H_
#define GAME_H_


#include "Deck.h"
#include "Card.h"
#include "Table.h"
#include "Player.h"
#include "Dealer.h"
#include "strategy/BasicStrategy.h"
#include "strategy/ActionHelper.h"
#include <iostream>
#include <string>

class Game {
public:
	Game();
	virtual ~Game();

	void Play();

private:
	void PrintTable(Table& t);
	void PrintDecisions(IStrategy::Action a1, IStrategy::Action a2);
	std::string GetActionString(IStrategy::Action a);
	void Settle();

	Deck m_deck;
	ActionHelper m_helper;
	BasicStrategy m_strategy;
	Player m_p1;
	Player m_p2;
	Table m_table;
	Dealer m_dealer;

};

#endif /* GAME_H_ */
