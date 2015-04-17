/*
 * Stage.cpp
 *
 *  Created on: 28/3/2015
 *      Author: mauro
 */

#include "../headers/Stage.h"

Stage::Stage() {
	this->width = 0;
	this->height = 0;
	this->yGround = 0;
}

Stage::Stage(int width, int height, float yfloor) {
	this->width = width;
	this->height = height;
	this->yGround = yfloor;
}

int Stage::getHeight(){
	return this->height;
}

int Stage::getWidth() {
	return this->width;
}

float Stage::getYGround(){
	return this->yGround;
}

Stage::~Stage() {
}
