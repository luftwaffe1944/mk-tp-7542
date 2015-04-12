/*
 * Stage.cpp
 *
 *  Created on: 28/3/2015
 *      Author: mauro
 */

#include "../headers/Stage.h"

Stage::Stage() {
	// TODO Auto-generated constructor stub

}

Stage::Stage(int width, int height, int yfloor) {
	this->width = width;
	this->height = height;
	this->yfloor = yfloor;
}

int Stage::getHeight(){
	return this->height;
}

int Stage::getWidth() {
	return this->width;
}

Stage::~Stage() {
	// TODO Auto-generated destructor stub
}


