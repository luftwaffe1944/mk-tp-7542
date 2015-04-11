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
	this->orientation = -1;
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
		this->scrollingOffset -= this->bkgSpeed * this->orientation; //USAR INPUT EN VEZ DE ORIENTATION
		this->positionX = scrollingOffset - this->offScene;
	}
}
void Layer::clean() {
}

void Layer::setLayerOffScene(int windowsWidth) {
	this->offScene = ((this->width - windowsWidth) / 2);
	FILE_LOG(logDEBUG) << "Layer " << this->textureID << " layeroffScene " << this->offScene;
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

void Layer::setPositionX(int position) {
	this->positionX = position;
}

int Layer::getPositionX(){
	return this->positionX;
}

float Layer::getScrollingOffset(){
	return this->scrollingOffset;
}

int Layer::getWidth(){
	return this->width;
}

int Layer::getOrientation() const {
	return this->orientation;
}

void Layer::setOrientation(int orientation) {
	this->orientation = orientation;
}
