/*
 * Dealer.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#include "Dealer.h"
#include "ITable.h"
#include "IDeck.h"
#include "IPlayer.h"
#include <iostream>
#include "Card.h"
#include <vector>

Dealer::Dealer(IDeck& deck, ITable& t)
:m_table(t),
 m_deck(deck)
{
	m_deck.Shuffle();
}

Dealer::~Dealer() {
}

void Dealer::DealHits(IPlayer* p)
{
	if (p->GetValue() == 0)
	{
		return;
	}
	Card* dealerCard = m_table.GetDealerCard();

	IStrategy::Action a1 = p->Decision(dealerCard);

	if (a1 == IStrategy::DOUBLE)
	{
		p->TakeCard(m_deck.Next());
	}
	else if (a1 == IStrategy::HIT)
	{
		while (a1 == IStrategy::HIT)
		{
			p->TakeCard(m_deck.Next());
			a1 = p->Decision(dealerCard);
		}
	}
	else if (a1 == IStrategy::SPLIT)
	{
		IPlayer* splitPlayer = p->Split();
		p->TakeCard(m_deck.Next());
		splitPlayer->TakeCard(m_deck.Next());
		DealHits(splitPlayer);
		DealHits(p);
	}
}

bool Dealer::Deal()
{
	m_cards.clear();
	m_table.P1()->TakeCard(m_deck.Next());
	m_table.P2()->TakeCard(m_deck.Next());
	m_cards.push_back(m_deck.Next());
	m_table.P1()->TakeCard(m_deck.Next());
	m_table.P2()->TakeCard(m_deck.Next());
	Card* dealerCard = m_deck.Next();
	m_cards.push_back(dealerCard);
	m_table.SetDealerCard(dealerCard);
	return CheckBlackjack();
}

bool Dealer::CheckBlackjack()
{
	if (GetValue() == 21)
		return true;
	return false;
}

int Dealer::Count()
{
	return m_cards.size();
}

int Dealer::FinishUp()
{
	int sum = m_cards[0]->Value() + m_cards[1]->Value();

	while (sum < 17 || IsSoft17())
	{
		Card* c = m_deck.Next();
		sum += c->Value();
		m_cards.push_back(c);
	}
	return sum;
}

bool Dealer::IsSoft17()
{
	using namespace std;
	bool ace = false;
	int val = 0;
	vector<Card*>::const_iterator iter;
	for (iter = m_cards.begin(); iter != m_cards.end(); ++iter)
	{
		Card* c = *iter;
		val += c->Value();
		if (c->IsAce())
		{
			ace = true;
		}
	}
	return val == 17 && ace;
}

int Dealer::GetValue()
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
