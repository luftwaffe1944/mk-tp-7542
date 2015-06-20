/*
 * VisualEffect.cpp
 *
 *  Created on: 20/6/2015
 *      Author: uje
 */

#include "../headers/VisualEffect.h"

VisualEffect::VisualEffect(const LoaderParams* pParams) : SDLObjectGUI(pParams)  {
	// TODO Auto-generated constructor stub

}

VisualEffect::~VisualEffect() {
	// TODO Auto-generated destructor stub
	delete this->pParams;
}

void VisualEffect::draw() {
	if ( visible ) SDLObjectGUI::draw();
}

void VisualEffect::animateToasty() {
	animate();
}
void VisualEffect::animate() {
	visible = true;
	startTime = SDL_GetTicks();
}

void VisualEffect::endAnimation() {
	visible = false;
	startTime = 0;
}

void VisualEffect::clean() {

}

void VisualEffect::update() {
	unsigned int currentTicks = SDL_GetTicks();
	if ( currentTicks - startTime > duration) {
		//transcurrió el tiempo de la animación
		endAnimation();
	} else {

	}

}

void VisualEffect::setImagePath(std::string path) {
	this->imagePath = path;
}

