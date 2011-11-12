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
		bool dealerBlackjack = m_dealer.Deal();
		if (dealerBlackjack)
		{
			cout << "==== DEALER BLACKJACK ==== " << endl;
			PrintTable();
			cout << "P1 Bank $" << m_table.P1()->GetBank() << endl;
			cout << "P2 Bank $" << m_table.P2()->GetBank() << endl;

			continue;
		}
		PrintTable();
//		IStrategy::Action a1 = m_p1.Decision(m_table.GetDealerCard());
//		IStrategy::Action a2 = m_p2.Decision(m_table.GetDealerCard());
//		PrintDecisions(a1, a2);
		m_dealer.DealHits(m_table.P1());
		m_dealer.DealHits(m_table.P2());
		cout << "After Hits" << endl;
		PrintTable();
		cout << "Dealer Value: (" << m_dealer.FinishUp() << ")" << endl;
		Settle();
		cout << "P1 Bank $" << m_table.P1()->GetBank() << endl;
		cout << "P2 Bank $" << m_table.P2()->GetBank() << endl;
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
	}
}

void Game::Settle()
{
	IPlayer* p1 = m_table.P1();
	IPlayer* p2 = m_table.P2();
	std::vector<IPlayer*>::iterator iter;
	DoSettle(p1);
	std::vector<IPlayer*>* splits = p1->GetSplits();
	for (iter = splits->begin(); iter != splits->end(); ++iter)
	{
		IPlayer* split = *iter;
		DoSettle(split);
	}
	p1->TakeSplitsBank();

	DoSettle(p2);
	splits = p2->GetSplits();
	for (iter = splits->begin(); iter != splits->end(); ++iter)
	{
		IPlayer* split = *iter;
		DoSettle(split);
	}
	p1->TakeSplitsBank();
}

void Game::PrintDecisions(IStrategy::Action a1, IStrategy::Action a2)
{
	cout << "P1 action: " << a1 << " " << GetActionString(a1) << endl;
	cout << "P2 action: " << a2 << " " << GetActionString(a2) << endl;
}

void Game::PrintTable()
{
	cout << "P1(" << m_table.P1()->GetValue() << ") :";
	m_table.P1()->ShowCards();
	cout << "P2(" << m_table.P2()->GetValue() << ") :";
	m_table.P2()->ShowCards();
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
