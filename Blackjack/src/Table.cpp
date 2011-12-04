/*
 * Table.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */
#include "Table.h"
#include "IPlayer.h"
#include <iostream>
#include "Card.h"


Table::Table(IPlayer& p1, IPlayer& p2)
:m_p1(p1),
 m_p2(p2)
{

}

Table::~Table(){}

void Table::Print()
{
	using namespace std;
	m_p1.ShowCards();
	cout << " " << endl;
	m_p2.ShowCards();
	cout << " " << endl;
	if (m_dealerCard != NULL)
	{
		cout << "UpCard: " << m_dealerCard->Value() << "-" << m_dealerCard->SuitString() << endl;
	}
	else
	{
		cout << " " << endl;
	}

}

IPlayer* Table::P1()
{
	return &m_p1;
}

IPlayer* Table::P2()
{
	return &m_p2;
}

void Table::CheckPlayerBlackJacks()
{
	m_p1.Blackjack();
	m_p2.Blackjack();
}

void Table::SetDealerCard(Card* c)
{
	m_dealerCard = c;
}

Card* Table::GetDealerCard()
{
	return m_dealerCard;
}

void Table::Reset()
{
	m_p1Wager = m_p1.Ante();
	m_p2Wager = m_p2.Ante();
	m_dealerCard = NULL;
}
