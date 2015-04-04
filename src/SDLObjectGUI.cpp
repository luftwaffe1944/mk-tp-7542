/*
 * SDLObjectGUI.cpp
 *
 *  Created on: 2/4/2015
 *      Author: mauro
 */

#include "../headers/SDLObjectGUI.h"
#include "../headers/MKGame.h"

SDLObjectGUI::SDLObjectGUI(const LoaderParams* pParams) :
		ObjectGUI(pParams) {
	positionX = pParams->getPosX();
	positionY = pParams->getPosY();
	width = pParams->getWidth();
	height = pParams->getHeight();
	zIndex = pParams->getZIndex();
	drawRatio = pParams->getDrawRatio();
	textureID = pParams->getTextureID();
	currentRow = 1;
	currentFrame = 1;
}

SDLObjectGUI::SDLObjectGUI() :
		ObjectGUI() {

}

void SDLObjectGUI::setImagePath(string imagePath) {
	this->imagePath = imagePath;
}

bool SDLObjectGUI::load() {
	return (TextureManager::Instance()->load(this->imagePath, textureID,
			MKGame::Instance()->getRenderer()));
}

void SDLObjectGUI::draw() {
	TextureManager::Instance()->draw(textureID, positionX, positionY, width,
			height, MKGame::Instance()->getRenderer());
}

void SDLObjectGUI::update() {

}

void SDLObjectGUI::clean() {

}

int SDLObjectGUI::unitToPixel(float units) {
	return ((int) units * this->drawRatio);
}
