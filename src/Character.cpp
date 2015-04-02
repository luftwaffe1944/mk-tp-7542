/*
 * Character.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Character.h"

Character::Character() {
	// TODO Auto-generated constructor stub

}

Character::Character(int width, int height, int zindex, std::string orientation) {
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->orientation = orientation;

}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

