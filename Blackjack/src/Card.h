/*
 * Card.h
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#ifndef CARD_H_
#define CARD_H_

#include <string>

class Card {
public:

	enum SuitEnum
	{
		HEART,
		DIAMOND,
		SPADE,
		CLUB
	};

	Card(int value, SuitEnum suit);
	virtual ~Card();

	int Value() const;
	SuitEnum Suit(){return m_suit;}
	std::string SuitString();
	bool IsAce(){ return m_value == 14;}
private:
	int m_value;
	SuitEnum m_suit;
};

#endif /* CARD_H_ */
