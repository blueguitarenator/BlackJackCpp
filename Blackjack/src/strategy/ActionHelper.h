/*
 * ActionHelper.h
 *
 *  Created on: Nov 9, 2011
 *      Author: richardjohnson
 */

#ifndef ACTIONHELPER_H_
#define ACTIONHELPER_H_

#include "IActionHelper.h"
#include <map>

class ActionHelper : public IActionHelper {
public:
	ActionHelper();
	virtual ~ActionHelper();

	virtual IStrategy::Action DoPair(std::vector<Card*>& playerCards, Card* dealerFaceCard);
	virtual IStrategy::Action DoSoft(std::vector<Card*>& playerCards, Card* dealerFaceCard);
	virtual IStrategy::Action DoHard(std::vector<Card*>& playerCards, Card* dealerFaceCard);
	virtual std::string GetHardKey(int val);
	virtual std::string GetSoftKey(int val);
	virtual std::string GetPairKey(int val);

private:
	void LoadMaps();
	std::map<std::string, std::map<int, IStrategy::Action> > m_hardTotals;
	std::map<std::string, std::map<int, IStrategy::Action> > m_softTotals;
	std::map<std::string, std::map<int, IStrategy::Action> > m_pairTotals;

};

#endif /* ACTIONHELPER_H_ */
