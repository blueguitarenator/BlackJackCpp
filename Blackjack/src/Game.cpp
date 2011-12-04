/*
 * Game.cpp
 *
 *  Created on: Nov 9, 2011
 *      Author: richardjohnson
 */

#include "Game.h"
#include "ITable.h"
#include "IDealer.h"
#include "IPlayer.h"

using namespace std;

Game::Game(ITable& table, IDealer& dealer)
: m_table(table),
  m_dealer(dealer)
{
}

Game::~Game() {
}

void Game::Play(int rounds)
{
	for (int i = 0; i < rounds; ++i)
	{
		cout << "++++++++ROUND++++++++++: " << i << endl;
		m_table.Reset();

		m_table.Print();

		bool dealerBlackjack = m_dealer.Deal();
		if (dealerBlackjack)
		{
			PrintTable();
			cout << "==== DEALER BLACKJACK ==== " << endl;
			continue;
		}
		m_table.Print();
		m_table.CheckPlayerBlackJacks();
		cout << "Do Hits" << endl;
		if (m_table.P1()->In())
		{
			m_dealer.DealHits(m_table.P1());
		}
		if (m_table.P2()->In())
		{
			m_dealer.DealHits(m_table.P2());
		}

		m_table.Print();
		if (m_table.P1()->In() || m_table.P2()->In())
		{
			cout << "Dealer Value: (" << m_dealer.FinishUp() << ")" << endl;
			Settle();
		}
		m_table.SetDealerCard(NULL);
		m_table.Print();
	}

}

void Game::DoSettle(IPlayer* p)
{
	int dealerVal = m_dealer.GetValue();
	int pVal = p->GetValue();
	if (dealerVal > 21)
	{
		p->Wins();
	}
	else
	{
		if (pVal < 22 && pVal > dealerVal)
		{
			p->Wins();
		}
		else if (pVal == dealerVal)
		{
			p->Push();
		}
		else
		{
			p->Lose();
		}
	}
}

void Game::Settle()
{
	IPlayer* p1 = m_table.P1();
	IPlayer* p2 = m_table.P2();
	std::vector<IPlayer*>::iterator iter;
	if (p1->In())
	{
		DoSettle(p1);
		std::vector<IPlayer*>* splits = p1->GetSplits();
		for (iter = splits->begin(); iter != splits->end(); ++iter)
		{
			IPlayer* split = *iter;
			DoSettle(split);
		}
		p1->TakeSplitsBank();
	}
	if (p2->In())
	{
		DoSettle(p2);
		std::vector<IPlayer*>* splits = p2->GetSplits();
		for (iter = splits->begin(); iter != splits->end(); ++iter)
		{
			IPlayer* split = *iter;
			DoSettle(split);
		}
		p1->TakeSplitsBank();
	}
}

void Game::PrintTable()
{
	m_table.P1()->ShowCards();
	cout << " " << endl;
	m_table.P2()->ShowCards();
	cout << " " << endl;
	cout << "UpCard: " << m_table.GetDealerCard()->Value() << "-" << m_table.GetDealerCard()->SuitString() << endl;
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
