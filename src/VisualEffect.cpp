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

	if ( visible ) {
		SDLObjectGUI::draw();
//		std::cout << positionX << std::endl;
	}
}

void VisualEffect::animateToasty() {
	animate();
	positionX = windowWidth / ratioX ;
	//std::cout << positionX << "// " << windowWidth / ratioX << "//" << width << "//" << speed << std::endl;
	positionY = windowHeight / ratioY - height;
	freezed = false;
}

void VisualEffect::animate() {
	visible = true;
	speed = - TOASTY_SPEED;
	startTime = SDL_GetTicks();
}

void VisualEffect::endAnimation() {
	visible = false;
	startTime = 0;
}

void VisualEffect::clean() {

}

void VisualEffect::update() {
	if (isToasty) {
		if ( positionX < (windowWidth / ratioX - width) ) {
		//	std::cout << positionX << "//" << windowWidth / ratioY - width <<  std::endl;
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
	/*
	unsigned int currentTicks = SDL_GetTicks();
	if ( currentTicks - startTime > duration) {
		//transcurrió el tiempo de la animación
		endAnimation();
	} else {

	}
*/
}

void VisualEffect::setImagePath(std::string path) {
	this->imagePath = path;
}

