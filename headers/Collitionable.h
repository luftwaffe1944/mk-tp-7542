/*
 * Character.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef COLLITIONABLE_H_
#define COLLITIONABLE_H_

#include <string>
#include "SDLObjectGUI.h"
#include <SDL.h>
#include <stdio.h>
#include <map>
#include <iostream>
#include <vector>
#include "Box.h"
using namespace std;



class Collitionable {
private:

	vector<Box*> Shapes;
	bool isCMoving;
	bool isCActive;

public:
	Collitionable();
	void initShapes(int qty,float X, float Y, int W, int H);
	virtual ~Collitionable();
	void getCNextPosition(float* nextPositionX, float* nextPositionY);
	bool getCMoving(){return this->isCMoving;}
	void setCMoving(bool moving){this->isCMoving = moving;}
	void setCActive(bool active){this->isCActive = active;}
	vector<Box*> getShapes(){return this->Shapes;}



};

#endif /* COLLITIONABLE_H_ */
