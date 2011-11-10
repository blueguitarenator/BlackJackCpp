/*
 * ActionHelper.cpp
 *
 *  Created on: Nov 9, 2011
 *      Author: richardjohnson
 */

#include "ActionHelper.h"
#include "../Card.h"
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;

ActionHelper::ActionHelper() {
	LoadMaps();
}

ActionHelper::~ActionHelper() {
}

IStrategy::Action ActionHelper::DoHard(std::vector<Card*>& playerCards, Card* dealerFaceCard)
{
	int playerValue = 0;
	std::vector<Card*>::const_iterator iter;
	for (iter = playerCards.begin(); iter != playerCards.end(); ++iter)
	{
		Card* c = *iter;
		playerValue += c->Value();
	}

	if (playerValue > 18)
	{
		return IStrategy::STAY;
	}
	std::map<int, IStrategy::Action> x = m_hardTotals.find(GetHardKey(playerValue))->second;
	return x.find(dealerFaceCard->Value())->second;
}

IStrategy::Action ActionHelper::DoPair(std::vector<Card*>& playerCards, Card* dealerFaceCard)
{
	std::map<int, IStrategy::Action> x = m_pairTotals.find(GetPairKey(playerCards[0]->Value()))->second;
	return x.find(dealerFaceCard->Value())->second;
}

IStrategy::Action ActionHelper::DoSoft(std::vector<Card*>& playerCards, Card* dealerFaceCard)
{
	std::map<int, IStrategy::Action> x = m_softTotals.find(GetSoftKey(playerCards[0]->Value() + playerCards[1]->Value()))->second;
	return x.find(dealerFaceCard->Value())->second;
}

std::string ActionHelper::GetHardKey(int val)
{
	std::string keyValue = "UNK";
	if (val > 4 && val < 9)
	{
		keyValue = "5-8";
	}
	else if (val > 12 && val < 17)
	{
		keyValue = "13-16";
	}
	else if (val > 16 && val < 22)
	{
		keyValue = "17-21";
	}
	else
	{
		keyValue = boost::lexical_cast<std::string>( val );
	}
	return keyValue;
}

std::string ActionHelper::GetSoftKey(int val)
{
	std::string keyValue = "UNK";
	if (val == 13)
	{
		keyValue = "13";
	}
	else if (val > 13 && val < 18)
	{
		keyValue = "14-17";
	}
	else if (val == 18)
	{
		keyValue = "18";
	}
	return keyValue;
}

std::string ActionHelper::GetPairKey(int val)
{
	std::string keyValue = "UNK";
	if (val == 11 || val == 8)
	{
		keyValue = "AA,88";
	}
	else if (val == 2 || val == 3)
	{
		keyValue = "22,33";
	}
	else if (val == 4)
	{
		keyValue = "44";
	}
	else if (val == 5)
	{
		keyValue = "55";
	}
	else if (val == 6)
	{
		keyValue = "66";
	}
	else if (val == 7)
	{
		keyValue = "77";
	}
	else if (val == 8)
	{
		keyValue = "88";
	}
	else if (val == 9)
	{
		keyValue = "99";
	}
	else if (val == 10)
	{
		keyValue = "TT";
	}
	return keyValue;
}

void ActionHelper::LoadMaps()
{
	// Hard
	std::map<int, IStrategy::Action> hard5_8;
	hard5_8.insert(std::pair<int, IStrategy::Action>(2, IStrategy::HIT));
	hard5_8.insert(std::pair<int, IStrategy::Action>(3, IStrategy::HIT));
	hard5_8.insert(std::pair<int, IStrategy::Action>(4, IStrategy::HIT));
	hard5_8.insert(std::pair<int, IStrategy::Action>(5, IStrategy::HIT));
	hard5_8.insert(std::pair<int, IStrategy::Action>(6, IStrategy::HIT));
	hard5_8.insert(std::pair<int, IStrategy::Action>(7, IStrategy::HIT));
	hard5_8.insert(std::pair<int, IStrategy::Action>(8, IStrategy::HIT));
	hard5_8.insert(std::pair<int, IStrategy::Action>(9, IStrategy::HIT));
	hard5_8.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	hard5_8.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_hardTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("5-8", hard5_8));
	std::map<int, IStrategy::Action> hard9;
	hard9.insert(std::pair<int, IStrategy::Action>(2, IStrategy::HIT));
	hard9.insert(std::pair<int, IStrategy::Action>(3, IStrategy::HIT));
	hard9.insert(std::pair<int, IStrategy::Action>(4, IStrategy::DOUBLE));
	hard9.insert(std::pair<int, IStrategy::Action>(5, IStrategy::DOUBLE));
	hard9.insert(std::pair<int, IStrategy::Action>(6, IStrategy::DOUBLE));
	hard9.insert(std::pair<int, IStrategy::Action>(7, IStrategy::HIT));
	hard9.insert(std::pair<int, IStrategy::Action>(8, IStrategy::HIT));
	hard9.insert(std::pair<int, IStrategy::Action>(9, IStrategy::HIT));
	hard9.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	hard9.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_hardTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("9", hard9));
	std::map<int, IStrategy::Action> hard10;
	hard10.insert(std::pair<int, IStrategy::Action>(2, IStrategy::DOUBLE));
	hard10.insert(std::pair<int, IStrategy::Action>(3, IStrategy::DOUBLE));
	hard10.insert(std::pair<int, IStrategy::Action>(4, IStrategy::DOUBLE));
	hard10.insert(std::pair<int, IStrategy::Action>(5, IStrategy::DOUBLE));
	hard10.insert(std::pair<int, IStrategy::Action>(6, IStrategy::DOUBLE));
	hard10.insert(std::pair<int, IStrategy::Action>(7, IStrategy::DOUBLE));
	hard10.insert(std::pair<int, IStrategy::Action>(8, IStrategy::DOUBLE));
	hard10.insert(std::pair<int, IStrategy::Action>(9, IStrategy::DOUBLE));
	hard10.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	hard10.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_hardTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("10", hard10));
	std::map<int, IStrategy::Action> hard11;
	hard11.insert(std::pair<int, IStrategy::Action>(2, IStrategy::DOUBLE));
	hard11.insert(std::pair<int, IStrategy::Action>(3, IStrategy::DOUBLE));
	hard11.insert(std::pair<int, IStrategy::Action>(4, IStrategy::DOUBLE));
	hard11.insert(std::pair<int, IStrategy::Action>(5, IStrategy::DOUBLE));
	hard11.insert(std::pair<int, IStrategy::Action>(6, IStrategy::DOUBLE));
	hard11.insert(std::pair<int, IStrategy::Action>(7, IStrategy::DOUBLE));
	hard11.insert(std::pair<int, IStrategy::Action>(8, IStrategy::DOUBLE));
	hard11.insert(std::pair<int, IStrategy::Action>(9, IStrategy::DOUBLE));
	hard11.insert(std::pair<int, IStrategy::Action>(10, IStrategy::DOUBLE));
	hard11.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_hardTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("11", hard11));
	std::map<int, IStrategy::Action> hard12;
	hard12.insert(std::pair<int, IStrategy::Action>(2, IStrategy::HIT));
	hard12.insert(std::pair<int, IStrategy::Action>(3, IStrategy::HIT));
	hard12.insert(std::pair<int, IStrategy::Action>(4, IStrategy::STAY));
	hard12.insert(std::pair<int, IStrategy::Action>(5, IStrategy::STAY));
	hard12.insert(std::pair<int, IStrategy::Action>(6, IStrategy::STAY));
	hard12.insert(std::pair<int, IStrategy::Action>(7, IStrategy::STAY));
	hard12.insert(std::pair<int, IStrategy::Action>(8, IStrategy::HIT));
	hard12.insert(std::pair<int, IStrategy::Action>(9, IStrategy::HIT));
	hard12.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	hard12.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_hardTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("12", hard12));
	std::map<int, IStrategy::Action> hard13_16;
	hard13_16.insert(std::pair<int, IStrategy::Action>(2, IStrategy::STAY));
	hard13_16.insert(std::pair<int, IStrategy::Action>(3, IStrategy::STAY));
	hard13_16.insert(std::pair<int, IStrategy::Action>(4, IStrategy::STAY));
	hard13_16.insert(std::pair<int, IStrategy::Action>(5, IStrategy::STAY));
	hard13_16.insert(std::pair<int, IStrategy::Action>(6, IStrategy::STAY));
	hard13_16.insert(std::pair<int, IStrategy::Action>(7, IStrategy::HIT));
	hard13_16.insert(std::pair<int, IStrategy::Action>(8, IStrategy::HIT));
	hard13_16.insert(std::pair<int, IStrategy::Action>(9, IStrategy::HIT));
	hard13_16.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	hard13_16.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_hardTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("13-16", hard13_16));
	std::map<int, IStrategy::Action> hard_17_21;
	hard_17_21.insert(std::pair<int, IStrategy::Action>(2, IStrategy::STAY));
	hard_17_21.insert(std::pair<int, IStrategy::Action>(3, IStrategy::STAY));
	hard_17_21.insert(std::pair<int, IStrategy::Action>(4, IStrategy::STAY));
	hard_17_21.insert(std::pair<int, IStrategy::Action>(5, IStrategy::STAY));
	hard_17_21.insert(std::pair<int, IStrategy::Action>(6, IStrategy::STAY));
	hard_17_21.insert(std::pair<int, IStrategy::Action>(7, IStrategy::STAY));
	hard_17_21.insert(std::pair<int, IStrategy::Action>(8, IStrategy::STAY));
	hard_17_21.insert(std::pair<int, IStrategy::Action>(9, IStrategy::STAY));
	hard_17_21.insert(std::pair<int, IStrategy::Action>(10, IStrategy::STAY));
	hard_17_21.insert(std::pair<int, IStrategy::Action>(14, IStrategy::STAY));
	m_hardTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("17-21", hard_17_21));

	// Soft
	std::map<int, IStrategy::Action> soft13;
	soft13.insert(std::pair<int, IStrategy::Action>(2, IStrategy::HIT));
	soft13.insert(std::pair<int, IStrategy::Action>(3, IStrategy::HIT));
	soft13.insert(std::pair<int, IStrategy::Action>(4, IStrategy::HIT));
	soft13.insert(std::pair<int, IStrategy::Action>(5, IStrategy::HIT));
	soft13.insert(std::pair<int, IStrategy::Action>(6, IStrategy::DOUBLE));
	soft13.insert(std::pair<int, IStrategy::Action>(7, IStrategy::HIT));
	soft13.insert(std::pair<int, IStrategy::Action>(8, IStrategy::HIT));
	soft13.insert(std::pair<int, IStrategy::Action>(9, IStrategy::HIT));
	soft13.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	soft13.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_softTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("13", soft13));
	std::map<int, IStrategy::Action> soft14_17;
	soft14_17.insert(std::pair<int, IStrategy::Action>(2, IStrategy::HIT));
	soft14_17.insert(std::pair<int, IStrategy::Action>(3, IStrategy::HIT));
	soft14_17.insert(std::pair<int, IStrategy::Action>(4, IStrategy::DOUBLE));
	soft14_17.insert(std::pair<int, IStrategy::Action>(5, IStrategy::DOUBLE));
	soft14_17.insert(std::pair<int, IStrategy::Action>(6, IStrategy::DOUBLE));
	soft14_17.insert(std::pair<int, IStrategy::Action>(7, IStrategy::HIT));
	soft14_17.insert(std::pair<int, IStrategy::Action>(8, IStrategy::HIT));
	soft14_17.insert(std::pair<int, IStrategy::Action>(9, IStrategy::HIT));
	soft14_17.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	soft14_17.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_softTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("14-17", soft14_17));
	std::map<int, IStrategy::Action> soft18;
	soft18.insert(std::pair<int, IStrategy::Action>(2, IStrategy::HIT));
	soft18.insert(std::pair<int, IStrategy::Action>(3, IStrategy::HIT));
	soft18.insert(std::pair<int, IStrategy::Action>(4, IStrategy::DOUBLE));
	soft18.insert(std::pair<int, IStrategy::Action>(5, IStrategy::DOUBLE));
	soft18.insert(std::pair<int, IStrategy::Action>(6, IStrategy::DOUBLE));
	soft18.insert(std::pair<int, IStrategy::Action>(7, IStrategy::STAY));
	soft18.insert(std::pair<int, IStrategy::Action>(8, IStrategy::STAY));
	soft18.insert(std::pair<int, IStrategy::Action>(9, IStrategy::HIT));
	soft18.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	soft18.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_softTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("18", soft18));

	// Pair
	std::map<int, IStrategy::Action> pairAA_88;
	pairAA_88.insert(std::pair<int, IStrategy::Action>(2, IStrategy::SPLIT));
	pairAA_88.insert(std::pair<int, IStrategy::Action>(3, IStrategy::SPLIT));
	pairAA_88.insert(std::pair<int, IStrategy::Action>(4, IStrategy::SPLIT));
	pairAA_88.insert(std::pair<int, IStrategy::Action>(5, IStrategy::SPLIT));
	pairAA_88.insert(std::pair<int, IStrategy::Action>(6, IStrategy::SPLIT));
	pairAA_88.insert(std::pair<int, IStrategy::Action>(7, IStrategy::SPLIT));
	pairAA_88.insert(std::pair<int, IStrategy::Action>(8, IStrategy::SPLIT));
	pairAA_88.insert(std::pair<int, IStrategy::Action>(9, IStrategy::SPLIT));
	pairAA_88.insert(std::pair<int, IStrategy::Action>(10, IStrategy::SPLIT));
	pairAA_88.insert(std::pair<int, IStrategy::Action>(14, IStrategy::SPLIT));
	m_pairTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("AA,88", pairAA_88));
	std::map<int, IStrategy::Action> pair22_33;
	pair22_33.insert(std::pair<int, IStrategy::Action>(2, IStrategy::SPLIT));
	pair22_33.insert(std::pair<int, IStrategy::Action>(3, IStrategy::SPLIT));
	pair22_33.insert(std::pair<int, IStrategy::Action>(4, IStrategy::SPLIT));
	pair22_33.insert(std::pair<int, IStrategy::Action>(5, IStrategy::SPLIT));
	pair22_33.insert(std::pair<int, IStrategy::Action>(6, IStrategy::SPLIT));
	pair22_33.insert(std::pair<int, IStrategy::Action>(7, IStrategy::SPLIT));
	pair22_33.insert(std::pair<int, IStrategy::Action>(8, IStrategy::HIT));
	pair22_33.insert(std::pair<int, IStrategy::Action>(9, IStrategy::HIT));
	pair22_33.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	pair22_33.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_pairTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("22,33", pair22_33));
	std::map<int, IStrategy::Action> pair44;
	pair44.insert(std::pair<int, IStrategy::Action>(2, IStrategy::HIT));
	pair44.insert(std::pair<int, IStrategy::Action>(3, IStrategy::HIT));
	pair44.insert(std::pair<int, IStrategy::Action>(4, IStrategy::HIT));
	pair44.insert(std::pair<int, IStrategy::Action>(5, IStrategy::SPLIT));
	pair44.insert(std::pair<int, IStrategy::Action>(6, IStrategy::SPLIT));
	pair44.insert(std::pair<int, IStrategy::Action>(7, IStrategy::HIT));
	pair44.insert(std::pair<int, IStrategy::Action>(8, IStrategy::HIT));
	pair44.insert(std::pair<int, IStrategy::Action>(9, IStrategy::HIT));
	pair44.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	pair44.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_pairTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("44", pair44));
	std::map<int, IStrategy::Action> pair55;
	pair55.insert(std::pair<int, IStrategy::Action>(2, IStrategy::DOUBLE));
	pair55.insert(std::pair<int, IStrategy::Action>(3, IStrategy::DOUBLE));
	pair55.insert(std::pair<int, IStrategy::Action>(4, IStrategy::DOUBLE));
	pair55.insert(std::pair<int, IStrategy::Action>(5, IStrategy::DOUBLE));
	pair55.insert(std::pair<int, IStrategy::Action>(6, IStrategy::DOUBLE));
	pair55.insert(std::pair<int, IStrategy::Action>(7, IStrategy::DOUBLE));
	pair55.insert(std::pair<int, IStrategy::Action>(8, IStrategy::DOUBLE));
	pair55.insert(std::pair<int, IStrategy::Action>(9, IStrategy::DOUBLE));
	pair55.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	pair55.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_pairTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("55", pair55));
	std::map<int, IStrategy::Action> pair66;
	pair66.insert(std::pair<int, IStrategy::Action>(2, IStrategy::HIT));
	pair66.insert(std::pair<int, IStrategy::Action>(3, IStrategy::SPLIT));
	pair66.insert(std::pair<int, IStrategy::Action>(4, IStrategy::SPLIT));
	pair66.insert(std::pair<int, IStrategy::Action>(5, IStrategy::SPLIT));
	pair66.insert(std::pair<int, IStrategy::Action>(6, IStrategy::SPLIT));
	pair66.insert(std::pair<int, IStrategy::Action>(7, IStrategy::HIT));
	pair66.insert(std::pair<int, IStrategy::Action>(8, IStrategy::HIT));
	pair66.insert(std::pair<int, IStrategy::Action>(9, IStrategy::HIT));
	pair66.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	pair66.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_pairTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("66", pair66));
	std::map<int, IStrategy::Action> pair77;
	pair77.insert(std::pair<int, IStrategy::Action>(2, IStrategy::SPLIT));
	pair77.insert(std::pair<int, IStrategy::Action>(3, IStrategy::SPLIT));
	pair77.insert(std::pair<int, IStrategy::Action>(4, IStrategy::SPLIT));
	pair77.insert(std::pair<int, IStrategy::Action>(5, IStrategy::SPLIT));
	pair77.insert(std::pair<int, IStrategy::Action>(6, IStrategy::SPLIT));
	pair77.insert(std::pair<int, IStrategy::Action>(7, IStrategy::SPLIT));
	pair77.insert(std::pair<int, IStrategy::Action>(8, IStrategy::HIT));
	pair77.insert(std::pair<int, IStrategy::Action>(9, IStrategy::HIT));
	pair77.insert(std::pair<int, IStrategy::Action>(10, IStrategy::HIT));
	pair77.insert(std::pair<int, IStrategy::Action>(14, IStrategy::HIT));
	m_pairTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("77", pair77));
	std::map<int, IStrategy::Action> pair99;
	pair99.insert(std::pair<int, IStrategy::Action>(2, IStrategy::SPLIT));
	pair99.insert(std::pair<int, IStrategy::Action>(3, IStrategy::SPLIT));
	pair99.insert(std::pair<int, IStrategy::Action>(4, IStrategy::SPLIT));
	pair99.insert(std::pair<int, IStrategy::Action>(5, IStrategy::SPLIT));
	pair99.insert(std::pair<int, IStrategy::Action>(6, IStrategy::SPLIT));
	pair99.insert(std::pair<int, IStrategy::Action>(7, IStrategy::STAY));
	pair99.insert(std::pair<int, IStrategy::Action>(8, IStrategy::SPLIT));
	pair99.insert(std::pair<int, IStrategy::Action>(9, IStrategy::SPLIT));
	pair99.insert(std::pair<int, IStrategy::Action>(10, IStrategy::STAY));
	pair99.insert(std::pair<int, IStrategy::Action>(14, IStrategy::STAY));
	m_pairTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("99", pair99));
	std::map<int, IStrategy::Action> pairTT;
	pairTT.insert(std::pair<int, IStrategy::Action>(2, IStrategy::STAY));
	pairTT.insert(std::pair<int, IStrategy::Action>(3, IStrategy::STAY));
	pairTT.insert(std::pair<int, IStrategy::Action>(4, IStrategy::STAY));
	pairTT.insert(std::pair<int, IStrategy::Action>(5, IStrategy::STAY));
	pairTT.insert(std::pair<int, IStrategy::Action>(6, IStrategy::STAY));
	pairTT.insert(std::pair<int, IStrategy::Action>(7, IStrategy::STAY));
	pairTT.insert(std::pair<int, IStrategy::Action>(8, IStrategy::STAY));
	pairTT.insert(std::pair<int, IStrategy::Action>(9, IStrategy::STAY));
	pairTT.insert(std::pair<int, IStrategy::Action>(10, IStrategy::STAY));
	pairTT.insert(std::pair<int, IStrategy::Action>(14, IStrategy::STAY));
	m_pairTotals.insert(std::pair<std::string, std::map<int, IStrategy::Action> >("TT", pairTT));
}
