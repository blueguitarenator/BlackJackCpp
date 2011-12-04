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

	virtual IStrategy::Action DoPair(const std::vector<Card*>& playerCards, const Card* dealerFaceCard) const;
	virtual IStrategy::Action DoSoft(const std::vector<Card*>& playerCards, const Card* dealerFaceCard) const;
	virtual IStrategy::Action DoHard(const std::vector<Card*>& playerCards, const Card* dealerFaceCard) const;
	virtual std::string GetHardKey(int val) const;
	virtual std::string GetSoftKey(int val) const;
	virtual std::string GetPairKey(int val) const;

private:
	void LoadMaps();
	std::map<std::string, std::map<int, IStrategy::Action> > m_hardTotals;
	std::map<std::string, std::map<int, IStrategy::Action> > m_softTotals;
	std::map<std::string, std::map<int, IStrategy::Action> > m_pairTotals;

};

#endif /* ACTIONHELPER_H_ */
