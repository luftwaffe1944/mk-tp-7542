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

