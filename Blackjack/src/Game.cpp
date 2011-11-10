/*
 * Game.cpp
 *
 *  Created on: Nov 9, 2011
 *      Author: richardjohnson
 */

#include "Game.h"
using namespace std;

Game::Game()
: m_strategy(m_helper),
  m_p1(m_strategy),
  m_p2(m_strategy),
  m_table(m_p1, m_p2),
  m_dealer(m_deck, m_table)
{
	m_deck.Shuffle();

}

Game::~Game() {
}

void Game::Play()
{
	for (int i = 0; i < 200; ++i)
	{
		cout << "++++++++ROUND++++++++++: " << i << endl;
		m_table.Reset();
		m_dealer.Deal();
		PrintTable(m_table);
//		IStrategy::Action a1 = m_p1.Decision(m_table.GetDealerCard());
//		IStrategy::Action a2 = m_p2.Decision(m_table.GetDealerCard());
//		PrintDecisions(a1, a2);
		m_dealer.DoHits(&m_p1);
		m_dealer.DoHits(&m_p2);
		cout << "After Hits" << endl;
		PrintTable(m_table);
		cout << "Dealer Value: (" << m_dealer.FinishUp() << ")" << endl;
		Settle();
		cout << "P1 Bank $" << m_p1.GetBank() << endl;
		cout << "P2 Bank $" << m_p2.GetBank() << endl;
	}

}

void Game::Settle()
{
	int dealerVal = m_dealer.GetValue();
	int p1Val = m_p1.GetValue();
	int p2Val = m_p2.GetValue();
	if (dealerVal > 21)
	{
		m_p1.Wins();
		m_p2.Wins();
	}
	else
	{
		if (p1Val < 22 && p1Val > dealerVal)
		{
			m_p1.Wins();
		}
		else if (p2Val < 22 && p2Val > dealerVal)
		{
			m_p2.Wins();
		}
	}
}

void Game::PrintDecisions(IStrategy::Action a1, IStrategy::Action a2)
{
	cout << "P1 action: " << a1 << " " << GetActionString(a1) << endl;
	cout << "P2 action: " << a2 << " " << GetActionString(a2) << endl;
}

void Game::PrintTable(Table& t)
{
	cout << "P1(" << m_p1.GetValue() << ") :";
	t.P1()->ShowCards();
	cout << " Wage: " << t.GetP1Wager() << endl;
	cout << "P2(" << m_p2.GetValue() << ") :";
	t.P2()->ShowCards();
	cout << " Wage: " << t.GetP2Wager() << endl;
	cout << "UpCard: " << t.GetDealerCard()->Value() << "-" << t.GetDealerCard()->SuitString() << endl;
}

string Game::GetActionString(IStrategy::Action a)
{
	switch(a)
	{
	case IStrategy::STAY:
		return "Stay";
	case IStrategy::HIT:
		return "Hit";
	case IStrategy::SPLIT:
		return "Split";
	case IStrategy::DOUBLE:
		return "Double";
	case IStrategy::BUST:
		return "Bust";
	}
	return "UNK";
}
