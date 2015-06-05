/*
 * MenuItem.cpp
 *
 *  Created on: 26/5/2015
 *      Author: julian
 */

#include "../headers/MenuItem.h"

MenuItem::MenuItem(int x, int y, int w, int h, std::string tm) {
	this->positionX = x;
	this->positionY = y;
	this->width = w;
	this->height = h;
	this->text = tm;
	this->next = NULL;
	this->color = { 150, 150, 150 };
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

void MenuItem::setColor(int r, int g, int b) {
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
}

void MenuItem::show(SDL_Renderer* render) {
	TTF_Font* font = TTF_OpenFont("fonts/apple.ttf", 50);
	//std::transform(text.begin(), text.end(), text.begin(), ::toupper);
	SDL_Texture* mTexture = NULL;
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	mTexture = SDL_CreateTextureFromSurface(render, textSurface);
	SDL_FreeSurface(textSurface);

	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	SDL_QueryTexture(mTexture, NULL, NULL, &srcRect.w, &srcRect.h);

	destRect.w = srcRect.w;
	destRect.h = height;
	destRect.x = positionX;
	destRect.y = positionY;

	SDL_RenderCopyEx(render, mTexture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
	SDL_RenderPresent(render);
}

void MenuItem::drawBox(SDL_Renderer* render) {
	SDL_Rect boxCharacter = { positionX, positionY, width, height };
	SDL_SetRenderDrawColor(render, color.r, color.g, color.b, 0xFF);
	SDL_RenderDrawRect(render, &boxCharacter);
	SDL_RenderPresent(render);
}