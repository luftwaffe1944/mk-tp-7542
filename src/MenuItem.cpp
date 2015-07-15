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
	this->pathBg = "";
	this->background = NULL;
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

void MenuItem::setColor(int r, int g, int b, int a) {
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;
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
	SDL_DestroyTexture(mTexture);
	SDL_RenderPresent(render);
}

void MenuItem::loadBackgroundImage(SDL_Renderer* render) {
	pathBg = "images/menu/" + text + ".gif";
	SDL_Surface* pTempSurface = IMG_Load(pathBg.c_str());
	background = SDL_CreateTextureFromSurface(render, pTempSurface);
	SDL_FreeSurface(pTempSurface);
}

void MenuItem::drawBg(SDL_Texture* tx, SDL_Renderer* render) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 48;
	srcRect.h = 59;

	destRect.w = width;
	destRect.h = height;
	destRect.x = positionX;
	destRect.y = positionY;

	SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(render, &destRect);

	SDL_SetTextureAlphaMod(tx, color.a);
	SDL_RenderCopyEx(render, tx, &srcRect, &destRect, 0, 0,
		SDL_FLIP_NONE);
	SDL_RenderPresent(render);
}


void MenuItem::drawBox(SDL_Renderer* render) {
	loadBackgroundImage(render);
	drawBg(background, render);

	//rectangulo color
	SDL_Rect boxCharacter = { positionX, positionY, width, height };
	SDL_Rect boxCharacter1 = { positionX + 1, positionY + 1, width - 1, height - 1 };
	SDL_Rect boxCharacter2 = { positionX + 2, positionY + 2, width - 2, height - 2 };
	SDL_Rect boxCharacter3 = { positionX + 2, positionY + 2, width - 2, height - 2 };
	SDL_SetRenderDrawColor(render, color.r, color.g, color.b, 0xFF);
	SDL_RenderDrawRect(render, &boxCharacter);
	SDL_RenderDrawRect(render, &boxCharacter1);
	SDL_RenderDrawRect(render, &boxCharacter2);
	SDL_RenderDrawRect(render, &boxCharacter3);
	SDL_RenderPresent(render);
}

void MenuItem::setImageBG(std::string path){
	pathBg = path;
}