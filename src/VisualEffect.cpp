/*
 * VisualEffect.cpp
 *
 *  Created on: 20/6/2015
 *      Author: uje
 */

#include "../headers/VisualEffect.h"

#define TOASTY_SPEED 15

VisualEffect::VisualEffect(const LoaderParams* pParams) : SDLObjectGUI(pParams)  {
	// TODO Auto-generated constructor stub

}

VisualEffect::~VisualEffect() {
	// TODO Auto-generated destructor stub
	delete this->pParams;
}

void VisualEffect::draw() {
	if ( visible )	SDLObjectGUI::draw();
}

void VisualEffect::animateToasty() {
	animate();
	positionX = windowWidth / ratioX ;
	positionY = windowHeight / ratioY - height;
	freezed = false;
	speed = - TOASTY_SPEED;
	startTime = SDL_GetTicks();
}

void VisualEffect::animate() {
	visible = true;

}

void VisualEffect::endAnimation() {
	visible = false;
	startTime = 0;
}

void VisualEffect::update() {
	if (isToasty) {
		if ( positionX < (windowWidth / ratioX - width) ) {
			unsigned int currentTick = SDL_GetTicks();
			if (!freezed) {
				startingTick = currentTick;
				freezed = true;
			}
			if ( currentTick > startingTick + 400) {
				speed = TOASTY_SPEED;
			} else {
				speed = 0;
			}
		} else if (positionX > (windowWidth / ratioX + 4)) {
			endAnimation();
		}
		positionX += speed;
	}
}

void VisualEffect::animateBlood() {
	animate();
	positionX = 10;
	positionY = 10;

}

void VisualEffect::setImagePath(std::string path) {
	this->imagePath = path;
}


void VisualEffect::clean() {

}
