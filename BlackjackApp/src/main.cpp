/*
 * main.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

/*
 * export DYLD_LIBRARY_PATH=/Users/richardjohnson/code/cpp/BlackjackCode/Blackjack/Debug
 */

#include "Game.h"
#include "Player.h"
#include "Deck.h"
#include "Table.h"
#include "Dealer.h"
#include "strategy/BasicStrategy.h"
#include "strategy/ActionHelper.h"
#include <cstdlib>

int main(int argc, char* argv[])
{
	ActionHelper helper;
	BasicStrategy strategy(helper);
	Player p1(strategy);
	Player p2(strategy);
	Deck deck;
	Table table(p1, p2);
	Dealer dealer(deck, table);

	Game game(table, dealer);
	if (argc == 2)
	{
		int numberOfPlays = atoi(argv[1]);
		game.Play(numberOfPlays);
	}
	else
	{
		game.Play(1);
	}
	return 0;
}
