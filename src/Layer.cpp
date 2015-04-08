/*
 * Layer.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Layer.h"
#include <string>
#include <iostream>
#include "../headers/Log.h"
#include "../headers/Constants.h"

Layer::Layer(const LoaderParams* pParams) :
		SDLObjectGUI(pParams) {
	this->bkgSpeed = 0.5;
	this->offScene = 0;
	this->scrollingOffset = 0;
}

Layer::~Layer() {
	// TODO Auto-generated destructor stub
}

void Layer::draw() {
	SDLObjectGUI::draw();
}

void Layer::update() {
	currentFrame = int(((SDL_GetTicks() / 100) % 6));

	this->offScene = ((this->width - GameGUI::getInstance()->getWindow().getWidthPx()) / 2);
}
void Layer::clean() {
}

