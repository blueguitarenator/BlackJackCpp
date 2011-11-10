/*
 * IDeck.h
 *
 *  Created on: Nov 6, 2011
 *      Author: richardjohnson
 */

#ifndef IDECK_H_
#define IDECK_H_

class Card;

class IDeck {
public:
	virtual ~IDeck(){};

	virtual Card* Next() = 0;
	virtual void Shuffle() = 0;
};

#endif /* IDECK_H_ */
