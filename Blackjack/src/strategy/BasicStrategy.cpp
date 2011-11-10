/*
 * BasicStrategy.cpp
 *
 *  Created on: Nov 7, 2011
 *      Author: richardjohnson
 */

#include "BasicStrategy.h"
#include "../Card.h"
#include <iostream>

BasicStrategy::BasicStrategy(IActionHelper& helper)
: m_helper(helper)
{
}

BasicStrategy::~BasicStrategy() {
}

// 1. pair (only for 2 cards)
// 2. soft (only for 2 cards)
// 3. hard
IStrategy::Action BasicStrategy::Execute(std::vector<Card*>& playerCards, Card* dealerFaceCard)
{
//	using namespace std;
//	cout << "size: " << playerCards.size() << " " << playerCards[0] << " " << playerCards[1] << endl;
	IStrategy::Action action;
	if (Total(playerCards) > 18)
	{
		action = IStrategy::STAY;
	}
	else if (playerCards.size() == 2 && (playerCards[0]->Value() == playerCards[1]->Value()))
	{
		action = m_helper.DoPair(playerCards, dealerFaceCard);
	}
	else if (playerCards.size() == 2 && (playerCards[0]->Value() == 11 || playerCards[1]->Value() == 11))
	{
		action = m_helper.DoSoft(playerCards, dealerFaceCard);
	}
	else
	{
		action = m_helper.DoHard(playerCards, dealerFaceCard);
	}
	return action;
}

int BasicStrategy::Total(std::vector<Card*>& cards)
{
	int playerValue = 0;
	std::vector<Card*>::const_iterator iter;
	for (iter = cards.begin(); iter != cards.end(); ++iter)
	{
		Card* c = *iter;
		playerValue += c->Value();
	}
	return playerValue;
}
