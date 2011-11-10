/*
 * Deck.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#include "Deck.h"
#include <iostream>
#include <algorithm>
#include "Card.h"

Deck::Deck()
{
	m_deck.push_back(new Card(2, Card::HEART));
	m_deck.push_back(new Card(3, Card::HEART));
	m_deck.push_back(new Card(4, Card::HEART));
	m_deck.push_back(new Card(5, Card::HEART));
	m_deck.push_back(new Card(6, Card::HEART));
	m_deck.push_back(new Card(7, Card::HEART));
	m_deck.push_back(new Card(8, Card::HEART));
	m_deck.push_back(new Card(9, Card::HEART));
	m_deck.push_back(new Card(10, Card::HEART));
	m_deck.push_back(new Card(11, Card::HEART));
	m_deck.push_back(new Card(12, Card::HEART));
	m_deck.push_back(new Card(13, Card::HEART));
	m_deck.push_back(new Card(14, Card::HEART));
	m_deck.push_back(new Card(2, Card::CLUB));
	m_deck.push_back(new Card(3, Card::CLUB));
	m_deck.push_back(new Card(4, Card::CLUB));
	m_deck.push_back(new Card(5, Card::CLUB));
	m_deck.push_back(new Card(6, Card::CLUB));
	m_deck.push_back(new Card(7, Card::CLUB));
	m_deck.push_back(new Card(8, Card::CLUB));
	m_deck.push_back(new Card(9, Card::CLUB));
	m_deck.push_back(new Card(10, Card::CLUB));
	m_deck.push_back(new Card(11, Card::CLUB));
	m_deck.push_back(new Card(12, Card::CLUB));
	m_deck.push_back(new Card(13, Card::CLUB));
	m_deck.push_back(new Card(14, Card::CLUB));
	m_deck.push_back(new Card(2, Card::DIAMOND));
	m_deck.push_back(new Card(3, Card::DIAMOND));
	m_deck.push_back(new Card(4, Card::DIAMOND));
	m_deck.push_back(new Card(5, Card::DIAMOND));
	m_deck.push_back(new Card(6, Card::DIAMOND));
	m_deck.push_back(new Card(7, Card::DIAMOND));
	m_deck.push_back(new Card(8, Card::DIAMOND));
	m_deck.push_back(new Card(9, Card::DIAMOND));
	m_deck.push_back(new Card(10, Card::DIAMOND));
	m_deck.push_back(new Card(11, Card::DIAMOND));
	m_deck.push_back(new Card(12, Card::DIAMOND));
	m_deck.push_back(new Card(13, Card::DIAMOND));
	m_deck.push_back(new Card(14, Card::DIAMOND));
	m_deck.push_back(new Card(2, Card::SPADE));
	m_deck.push_back(new Card(3, Card::SPADE));
	m_deck.push_back(new Card(4, Card::SPADE));
	m_deck.push_back(new Card(5, Card::SPADE));
	m_deck.push_back(new Card(6, Card::SPADE));
	m_deck.push_back(new Card(7, Card::SPADE));
	m_deck.push_back(new Card(8, Card::SPADE));
	m_deck.push_back(new Card(9, Card::SPADE));
	m_deck.push_back(new Card(10, Card::SPADE));
	m_deck.push_back(new Card(11, Card::SPADE));
	m_deck.push_back(new Card(12, Card::SPADE));
	m_deck.push_back(new Card(13, Card::SPADE));
	m_deck.push_back(new Card(14, Card::SPADE));
}

Deck::~Deck()
{
}

int Deck::Count()
{
	return m_deck.size();
}

Card* Deck::Next()
{
	Card* c = *iter;
	if (iter++ == m_deck.end())
	{
		Shuffle();
		c = *iter;
	}
	return c;
}

void Deck::Shuffle()
{
	srand ( unsigned ( time (NULL) ) );
	std::random_shuffle(m_deck.begin(), m_deck.end());
	iter = m_deck.begin();
}

void Deck::Print()
{
	std::vector<Card*>::iterator it;
	int i = 0;
	for (it = iter; it != m_deck.end(); it++)
	{
		Card* c = *it;
		std::cout << i++ << " " << "Left: " << c->Value() << " " << c->Suit() << std::endl;
	}
}
