/*
 * Character.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Character.h"

Character::Character(const LoaderParams* pParams) :
		SDLObjectGUI(pParams) {

}

Character::Character(int width, int height, int zindex, std::string orientation) : SDLObjectGUI() {
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->orientation = orientation;
}

Character::Character(int name, int width, int height, int zindex, std::string orientation) : SDLObjectGUI(){
	this->name = name;
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->orientation = orientation;
}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

void Character::draw() {
	SDLObjectGUI::draw();
}
void Character::update() {
//	m_x -= 1;
	currentFrame = int(((SDL_GetTicks() / 100) % 6));
}
void Character::clean() {
}

