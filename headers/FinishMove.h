/*
 * FinishMove.h
 *
 *  Created on: 15/6/2015
 *      Author: mauro
 */

#ifndef FINISHMOVE_H_
#define FINISHMOVE_H_

#include <string>
#include <unistd.h>


class FinishMove {

protected:
	FinishMove(){}
	virtual ~FinishMove(){}
public:
	virtual void onPreFinish(std::string name)=0;
	virtual void onFinish(std::string name)=0;
	virtual void onPostFinish(std::string name)=0;
};

#endif /* FINISHMOVE_H_ */
