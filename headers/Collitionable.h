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



class Collitionable : public SDLObjectGUI {
private:

	vector<Box*> Shapes;
	bool isMoving;
	bool isRightOriented;

public:
	Collitionable();
	void initShapes(int qty,float X, float Y, int W, int H);
	virtual ~Collitionable();
	virtual void update();

	bool getMoving(){return this->isMoving;}
	void setCMoving(bool moving){this->isMoving = moving;}
	vector<Box*> getShapes(){return this->Shapes;}

};

#endif /* COLLITIONABLE_H_ */
