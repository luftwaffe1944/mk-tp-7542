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
#include "../headers/Log.h"

Layer::Layer() {

}

Layer::Layer(string image, int width, int zIndex) {
	this->backgroundImage = image;
	this->width = width;
	this->zIndex = zIndex;
}

bool Layer::load(SDL_Renderer* render) {
	stringstream sLayerName;
	sLayerName << "layer";
	sLayerName << this->zIndex;
	return (TextureManager::Instance()->load(this->backgroundImage, sLayerName.str(), render));
}
bool Layer::render(SDL_Renderer* render) {
	return true;
}

Layer::~Layer() {
	// TODO Auto-generated destructor stub
}

