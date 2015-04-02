/*
 * Character.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Character.h"
using namespace std;
Character::Character() {
	// TODO Auto-generated constructor stub

}
Character::Character(int width, int height, int zindex) {
	this->width = width;
	this->height = height;
	this->zindex = zindex;
}

Character::Character(int width, int height, int zindex,std::string spriteWalk,std::string spriteStand) {
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->spriteStand = spriteStand;
	this->spriteWalk = spriteWalk;
	this->activeSprite = spriteStand;
	this->frame = 1;
}

std::string Character::getActiveSprite(){
	return this->activeSprite;
}

int Character::h(){return this->height;}
int Character::w(){return this->width;}

void Character::setActiveSprite(std::string active){
	this->activeSprite = active;
}

int Character::getNextFrame(){
	if (this->frame==7) {frame=1;}
	return frame++;
}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

