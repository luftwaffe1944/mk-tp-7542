/*
 * SDLObjectGUI.cpp
 *
 *  Created on: 2/4/2015
 *      Author: mauro
 */

#include "../headers/SDLObjectGUI.h"
#include "../headers/MKGame.h"

SDLObjectGUI::SDLObjectGUI(const LoaderParams* pParams) : ObjectGUI(pParams) {
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

SDLObjectGUI::SDLObjectGUI() : ObjectGUI(){

}

void SDLObjectGUI::draw() {
	TextureManager::Instance()->drawFrame(textureID, positionX, positionY, width,
			height, currentRow, currentFrame,
			MKGame::Instance()->getRenderer());
}

void SDLObjectGUI::update(){

}

void SDLObjectGUI::clean(){

}

int SDLObjectGUI::unitToPixel(float units) {
	return ((int)units*this->drawRatio);
}
