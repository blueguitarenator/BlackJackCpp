/*
 * Card.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#include "Card.h"

Card::Card(int value, SuitEnum suit) :
	m_value(value), m_suit(suit) {

}

Card::~Card() {
}

int Card::Value() const
{
	if (m_value < 11)
	{
		return m_value;
	}
	if (m_value == 14)
	{
		return 11;
	}
	return 10;
}

std::string Card::SuitString() {
	switch (m_suit) {
		case Card::HEART:
			return "Heart";
		case Card::DIAMOND:
			return "Diamond";
		case Card::CLUB:
			return "Club";
		case Card::SPADE:
			return "Spade";
	}
	return "UNK";
}
