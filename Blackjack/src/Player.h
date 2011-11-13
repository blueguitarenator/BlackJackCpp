/*
 * Player.h
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <string>
#include "IPlayer.h"

class IStrategy;

class Player : public IPlayer {
public:
	Player(IStrategy&, std::string name);
	virtual ~Player();

	void TakeCard(Card* c);
	int Count();
	int Ante();
	IStrategy::Action Decision(Card* dealerFace);
	IPlayer* Split();

	void ShowCards();
	int GetBank(){return m_bank;}
	int GetBet(){return m_bet;}
	void Wins();
	void Push();
	bool Blackjack();
	int GetValue();
	std::vector<IPlayer*>* GetSplits();
	int TakeSplitsBank();

	friend class PlayerTestFriend;
private:
	std::string m_name;
	std::vector<Card*> m_cards;
	IStrategy& m_strategy;
	std::vector<IPlayer*> m_splits;
	int m_bank;
	int m_bet;
};

#endif /* PLAYER_H_ */
