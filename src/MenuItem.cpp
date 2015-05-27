/*
 * MenuItem.cpp
 *
 *  Created on: 26/5/2015
 *      Author: julian
 */

#include "../headers/MenuItem.h"

MenuItem::MenuItem(const LoaderParams* params) : SDLObjectGUI(params) {
	this->next = NULL;
}

MenuItem::~MenuItem() {
	if (next != 0) {
		delete next;
	}
}

bool MenuItem::checkBounds(float posX, float posY) {
	if ( posX >= this->positionX && posX <= this->positionX + this->width)
	{
		if ( posY >= this->positionY && posY <= this->positionY + this->height)
		{
		        return true;
		}
	}
	return false;
}

bool MenuItem::load(SDL_Renderer* render) {
	this->render = render;
	TTF_Font* font = TTF_OpenFont( "fonts/mk1.ttf", 100 );
	SDL_Color itemMenuColor = {255, 255, 255};
	std:string itemText = this->getTextureID();
	std::transform(itemText.begin(), itemText.end(), itemText.begin(), ::toupper);

	return (TextureManager::Instance()->loadFromRenderedText( this->textureID, itemText, itemMenuColor, font, render));
}

void MenuItem::clean() {
	if (next != 0) {
		delete next;
	}
}

void MenuItem::draw() {
	SDLObjectGUI::draw();
}

void MenuItem::update() {

}
