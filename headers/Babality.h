/*
 * Babality.h
 *
 *  Created on: 15/6/2015
 *      Author: mauro
 */

#ifndef BABALITY_H_
#define BABALITY_H_

#include "FinishMove.h"

class Babality :public FinishMove {
public:
	Babality();
	virtual ~Babality();
	virtual void onPreFinish(std::string name);
	virtual void onFinish(std::string name);
	virtual void onPostFinish(std::string name);
};

#endif /* BABALITY_H_ */
