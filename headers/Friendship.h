/*
 * Friendship.h
 *
 *  Created on: 15/6/2015
 *      Author: mauro
 */

#ifndef FRIENDSHIP_H_
#define FRIENDSHIP_H_

#include "FinishMove.h"

class Friendship : public FinishMove{
public:
	Friendship();
	virtual ~Friendship();
	virtual void onPreFinish(std::string name);
	virtual void onFinish(std::string name);
	virtual void onPostFinish(std::string name);
	virtual int getID();
};

#endif /* FRIENDSHIP_H_ */
