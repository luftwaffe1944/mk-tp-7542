/*
 * Sprite.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: nicolas.m.outeda
 */

#include "../headers/Sprite.h"

Sprite::Sprite() {
	// TODO Auto-generated constructor stub

}

Sprite::Sprite(std::string id, std::string spritePath, SDL_Renderer* m_pRenderer, int w, int h, int framesAmount) {
	if (!TextureManager::Instance()->load(spritePath, id, m_pRenderer)) {
		cout << "error con el load";
	}
	this->spriteId = id;
	this->spriteWidth = w;
	this->spriteHeight = h;
	this->framesAmount = framesAmount;
	this->currentFrame = 0;
}

std::string Sprite::getSpriteId() {
	return this->spriteId;
}

int Sprite::getSpriteWidth() {
	return this->spriteWidth;
}

int Sprite::getSpriteHeight() {
	return this->spriteHeight;
}


int Sprite::getNextFrame() {
	int pepe;
	pepe = this->currentFrame;
	if (this->currentFrame >= this->framesAmount) {
		this->currentFrame=0;
	}
	this->currentFrame = currentFrame + 1;
	return this->currentFrame;
}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

