/*
 * Table.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */
#include "Table.h"
#include "IPlayer.h"
#include <iostream>

Table::Table(IPlayer& p1, IPlayer& p2)
:m_p1(p1),
 m_p2(p2)
{

}

Table::~Table(){}

IPlayer* Table::P1()
{
	return &m_p1;
}

IPlayer* Table::P2()
{
	return &m_p2;
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
}
