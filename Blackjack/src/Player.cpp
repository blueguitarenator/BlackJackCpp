/*
 * Player.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#include "Player.h"
#include <iostream>
#include "Card.h"

Player::Player(IStrategy& s)
: m_strategy(s),
  m_pSplit(NULL),
  m_bank(100),
  m_bet(0)
{

}

Player::~Player() {
}

void Player::Wins()
{
	m_bank += m_bet * 2;
}

int Player::Ante()
{
	m_cards.clear();
	m_bank -= 5;
	m_bet = 5;
	return 5;
}

IStrategy::Action Player::Decision(Card* dealerFace)
{
	IStrategy::Action action = m_strategy.Execute(m_cards, dealerFace);
	if (action == IStrategy::DOUBLE)
	{
//		using namespace std;
//		cout << "DOUBLE" << endl;
		m_bank -= 5;
		m_bet += 5;
	}
	return action;
}

void Player::TakeCard(Card* c)
{
	m_cards.push_back(c);
}

int Player::Count()
{
	return m_cards.size();
}

void Player::ShowCards()
{
	using namespace std;
	vector<Card*>::iterator iter;
	for (iter = m_cards.begin(); iter != m_cards.end(); ++iter)
	{
		cout << (*iter)->Value() << "-" << (*iter)->SuitString() << " ";
	}
}

IPlayer* Player::Split()
{
	m_pSplit = new Player(m_strategy);

	return m_pSplit;
}

int Player::GetValue()
{
	int val = 0;
	std::vector<Card*>::const_iterator iter;
	for (iter = m_cards.begin(); iter != m_cards.end(); ++iter)
	{
		Card* c = *iter;
		val += c->Value();
	}
	return val;
}
