/*
 * DeckTest.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#include <gtest/gtest.h>
#include "Deck.h"
#include "Card.h"

TEST(DeckTest, NewDeckHas52Cards)
{
	Deck d;
	EXPECT_EQ(52, d.Count());
}

TEST(DeckTest, The52CardDeckShuffles)
{
	Deck d;
	d.Shuffle();
	Card* c1 = d.Next();
	Card* c2 = d.Next();
	Card* c3 = d.Next();
	Card* c4 = d.Next();
	d.Shuffle();
	EXPECT_FALSE(d.Next()->Value() == c1->Value() &&
			d.Next()->Value() == c2->Value() &&
			d.Next()->Value() == c3->Value() &&
			d.Next()->Value() == c4->Value());

}
