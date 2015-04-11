/*
 * Layer.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Layer.h"
#include <string>
#include <iostream>

Layer::Layer(const LoaderParams* pParams) :
		SDLObjectGUI(pParams) {
	this->bkgSpeed = 0;
	this->offScene = 0;
	this->scrollingOffset = 0;
	this->needRefresh = false;
	this->orientation = 1;
}

Layer::~Layer() {
	// TODO Auto-generated destructor stub
}

void Layer::draw() {
	SDLObjectGUI::draw();
}

void Layer::update() {
	currentFrame = int(((SDL_GetTicks() / 100) % 6));

	if (this->needRefresh) {
		this->scrollingOffset -= this->bkgSpeed * this->orientation;
		this->positionX = scrollingOffset - this->offScene;
	}
}
void Layer::clean() {
}

void Layer::setLayerOffScene(int windowsWidth) {
	this->offScene = ((this->width - windowsWidth) / 2);
}

void Layer::setLayerSpeed(float speedFirstLayer, float offSceneFirstLayer) {
	this->bkgSpeed = ((this->offScene * speedFirstLayer) / offSceneFirstLayer);
	FILE_LOG(logDEBUG) << "Layer " << this->textureID << " speed: " << this->bkgSpeed;
}

float Layer::getLayerOffScene() {
	return this->offScene;
}

float Layer::getLayerSpeed() {
	return this->bkgSpeed;
}

void Layer::setImagePath(std::string path) {
	this->imagePath = path;
}

void Layer::setNeedRefresh(bool needRefresh) {
	this->needRefresh = needRefresh;
}
