/*
 * Layer.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Layer.h"
#include <string>
#include <sstream>
#include <iostream>

Layer::Layer(const LoaderParams* pParams) :
		SDLObjectGUI(pParams) {
}

//TODO Deprecated.. use constructor above
//Layer::Layer(string image, int width, int zIndex) {
//	this->backgroundImage = image;
//	this->width = width;
//	this->zIndex = zIndex;
//}

//TODO Deprecated..
bool Layer::load(SDL_Renderer* render) {
	stringstream sLayerName;
	sLayerName << "layer";
	sLayerName << this->zIndex;
	return (TextureManager::Instance()->load(this->backgroundImage,
			sLayerName.str(), render));
}
bool Layer::render(SDL_Renderer* render) {
	return true;
}

Layer::~Layer() {
	// TODO Auto-generated destructor stub
}

void Layer::draw() {
	SDLObjectGUI::draw();
}

void Layer::update() {
//	m_x -= 1;
	currentFrame = int(((SDL_GetTicks() / 100) % 6));
}
void Layer::clean() {
}

