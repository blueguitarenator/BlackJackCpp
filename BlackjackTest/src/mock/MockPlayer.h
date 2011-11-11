/*
 * MockPlayer.h
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#ifndef MOCKPLAYER_H_
#define MOCKPLAYER_H_

#include "gmock/gmock.h"  // Brings in Google Mock.
#include "IPlayer.h"
#include "Card.h"
#include "strategy/IStrategy.h"

class MockPlayer: public IPlayer {
public:

  MOCK_METHOD1(TakeCard, void(Card* c));
  MOCK_METHOD0(Count, int());
  MOCK_METHOD0(Ante, int());
  MOCK_METHOD1(Decision, IStrategy::Action(Card* dealerFace));
  MOCK_METHOD0(Split, IPlayer*());
  MOCK_METHOD0(Wins, void());
  MOCK_METHOD0(Push, void());
  MOCK_METHOD0(GetBank, int());
  MOCK_METHOD0(GetValue, int());
};
#endif /* MOCKPLAYER_H_ */
