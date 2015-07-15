/*
 * Fatality.h
 *
 *  Created on: 15/6/2015
 *      Author: mauro
 */

#ifndef FATALITY_H_
#define FATALITY_H_

#include "FinishMove.h"
#include "SoundManager.h"

class Fatality :public FinishMove{
public:
	Fatality();
	virtual ~Fatality();
	virtual void onPreFinish(std::string name);
	virtual void onFinish(std::string name);
	virtual void onPostFinish(std::string name);
	virtual int getID();
};

#endif /* FATALITY_H_ */
