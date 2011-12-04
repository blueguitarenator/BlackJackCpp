/*
 * Player.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#include "Player.h"
#include <iostream>
#include <iomanip>
#include "Card.h"

using namespace std;

const int BET = 10;

Player::Player(IStrategy& s, std::string name)
: m_name(name),
  m_strategy(s),
  m_bank(0),
  m_bet(0)
{

}

Player::~Player() {
}

void Player::Push()
{
	cout << m_name << " PUSH " << endl;
	m_bank += m_bet;
	m_bet = 0;
	m_cards.clear();
}

bool Player::Blackjack()
{
	if (GetValue() == 21)
	{
		cout << m_name << " BLACKJACK " << endl;
		m_bank += m_bet;
		m_bank += m_bet * 1.5;
		m_bet = 0;
		m_cards.clear();
		return true;
	}
	return false;
}

bool Player::In()
{
	return m_cards.size() > 1;
}

void Player::Wins()
{
	cout << m_name << " WINS " << endl;
	m_bank += m_bet * 2;
	m_bet = 0;
	m_cards.clear();
}

void Player::TakeSplitsBank()
{
	vector<IPlayer*>::iterator iter;
	for (iter = m_splits.begin(); iter != m_splits.end(); ++iter)
	{
		IPlayer* split = *iter;
		int val = split->GetBank();
//		cout << "Taking splits: " << val << endl;
		m_bank += val;
	}
}

int Player::Ante()
{
	m_splits.clear();
	m_cards.clear();
	m_bank -= BET;
	m_bet = BET;
	return BET;
}

void Player::Lose()
{
	cout << m_name << " LOSER" << endl;
	m_cards.clear();
	m_bet = 0;
}

IStrategy::Action Player::Decision(Card* dealerFace)
{
	if (GetValue() > 21)
	{
		cout << m_name << " BUST" << endl;
		m_cards.clear();
		m_bet = 0;
		return IStrategy::BUST;
	}
	IStrategy::Action action = m_strategy.Execute(m_cards, dealerFace);
	if (action == IStrategy::DOUBLE)
	{
		cout << m_name << " DBL DOWN " << endl;
		m_bank -= BET;
		m_bet += BET;
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

IPlayer* Player::Split()
{
	IPlayer* split = new Player(m_strategy, " " + m_name + ".split");
	m_splits.push_back(split);
	Card* c = m_cards[1];
	split->Ante();
	split->TakeCard(c);
	m_cards.pop_back();
	return split;
}

std::vector<IPlayer*>* Player::GetSplits()
{
	return &m_splits;
}

int Player::GetValue()
{
	int val = 0;
	int aceCount = 0;
	vector<Card*>::const_iterator iter;
	for (iter = m_cards.begin(); iter != m_cards.end(); ++iter)
	{
		Card* c = *iter;
		val += c->Value();
		if (c->Value() == 11)
		{
			aceCount++;
		}
	}
	if (val > 21 && aceCount > 0)
	{
		while (aceCount > 0 && val > 21)
		{
			val -= 10;
			aceCount--;
		}
	}
	return val;
}

void Player::ShowCards()
{
	cout << m_name << "(" << GetValue() << ")" << setw(10) << "bank$" << m_bank << setw(10) << "bet$" << m_bet << setw(10);
	vector<Card*>::iterator iter;
	for (iter = m_cards.begin(); iter != m_cards.end(); ++iter)
	{
		cout << (*iter)->Value() << "-" << (*iter)->SuitString() << " ";
	}
	if (m_splits.size() > 0)
	{
		cout << "\n SPLITS " << endl;
		vector<IPlayer*>::iterator iter;
		for (iter = m_splits.begin(); iter != m_splits.end(); ++iter)
		{
			(*iter)->ShowCards();
		}

	}
}
