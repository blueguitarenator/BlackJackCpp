/*
 * IDealer.h
 *
 *  Created on: Nov 10, 2011
 *      Author: richardjohnson
 */

#ifndef IDEALER_H_
#define IDEALER_H_

class IPlayer;

class IDealer
{
public:
	virtual void Deal() = 0;
	virtual void DealHits(IPlayer* p) = 0;
	virtual int FinishUp() = 0;
	virtual int GetValue() = 0;
};

#endif /* IDEALER_H_ */
