/*
 * GameInfo.cpp
 *
 *  Created on: 23/4/2015
 *      Author: julian
 */

#include "../headers/GameInfo.h"

GameInfo::GameInfo(const LoaderParams* pParams, vector<std::string> playerName) :
		SDLObjectGUI(pParams) {
	this->playerName = playerName;
	bgColor = {204, 0, 0};
	frontColor = {0, 0, 204};
	barWidth = ((pParams->getWidth() * 0.9) - (WINDOW_MARGIN * 2)) / 2;
	this->percent = 0.0f;
	TTF_Init();
	this->initAnimation = true;
}

bool GameInfo::load() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();

	// carga de textos personajes

	SDL_Color textColor = {255, 255, 255};
	TTF_Font* font = TTF_OpenFont( "fonts/MK4.ttf", 28 );

	return (TextureManager::Instance()->loadFromRenderedText("nameSubzero", textColor, font, render));
}

bool GameInfo::load(SDL_Renderer* r) {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();

	// carga de textos personajes
	SDL_Color textColor = {255, 255, 255};
	TTF_Font* font = TTF_OpenFont( "fonts/mk1.ttf", 28 );

	//jugador 1
	std::transform(this->playerName[0].begin(), this->playerName[0].end(), this->playerName[0].begin(), ::toupper);
	return (TextureManager::Instance()->loadFromRenderedText(playerName[0], textColor, font, render));

	//jugador 2
	//std::transform(this->playerName[1].begin(), this->playerName[1].end(), this->playerName[1].begin(), ::toupper);
	//return (TextureManager::Instance()->loadFromRenderedText(playerName[1], textColor, font, render));

}


void GameInfo::HealthBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer* pRender, int player) {
	   Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	   SDL_Color old;
	   SDL_GetRenderDrawColor(pRender, &old.r, &old.g, &old.g, &old.a);
	   SDL_Rect bgrect = { x, y, w, h };
	   SDL_SetRenderDrawColor(pRender, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	   SDL_RenderFillRect(pRender, &bgrect);
	   SDL_SetRenderDrawColor(pRender, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
	   int pw = (int)((float)w * Percent);
	   int px;
	   if (player == 0) {
		   px = x;
	   } else {
		   px = x + (w - pw);
	   }

	   SDL_Rect fgrect = { px, y, pw, h };
	   SDL_RenderFillRect(pRender, &fgrect);
       SDL_SetRenderDrawColor( pRender, 225, 174, 140, 0xFF );
       SDL_RenderDrawRect( pRender, &bgrect );
	   SDL_SetRenderDrawColor(pRender, 0x00, 0x00, 0x00, 0xFF );
}

void GameInfo::animation() {
	if (this->percent < 1.0f && this->initAnimation) {
		this->percent += 0.05f;
	} else {
		this->initAnimation = false;
	}
}

void GameInfo::update() {
	animation();
}

void GameInfo::clean() {
	delete this->pParams;
	TTF_Quit();
}

void GameInfo::draw() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();

	//jugador 1
	HealthBar(positionX * ratioX ,35,barWidth * ratioX ,22, percent, frontColor, bgColor, render, 0);
	TextureManager::Instance()->draw("name" + this->playerName[0], WINDOW_MARGIN + 1, (35 / ratioY) + 1, barWidth / 2, 22/ratioY, render);

	//jugador 2
	//TextureManager::Instance()->draw("name"+this->playerName[0], WINDOW_MARGIN,0,barWidth/2, 10, render);
	HealthBar((this->width - WINDOW_MARGIN - barWidth) * ratioX, 35, barWidth * ratioX, 22, percent, frontColor, bgColor, render, 1);
}


