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
#include "../headers/Constants.h"

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
void Layer::render(SDL_Renderer* render, int height) {
	stringstream sLayerName;
	sLayerName << "layer";
	sLayerName << this->zIndex;
	TextureManager::Instance()->draw(sLayerName.str(), 0, 0, this->width, height, render);
}

Layer::~Layer() {
	// TODO Auto-generated destructor stub
}

