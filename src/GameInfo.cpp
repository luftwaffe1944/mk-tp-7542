/*
 * GameInfo.cpp
 *
 *  Created on: 23/4/2015
 *      Author: julian
 */

#include "../headers/GameInfo.h"

GameInfo::GameInfo(const LoaderParams* pParams, vector<Character*> characters) :
		SDLObjectGUI(pParams) {
	this->characters = characters;
	bgColor = {204, 0, 0, 150};
	frontColor = {0, 0, 204, 255};
	barWidth = ((pParams->getWidth() * 0.9) - (WINDOW_MARGIN * 2)) / 2;
	this->percent = 0.0f;
	TTF_Init();
	this->initAnimation = true;
	this->msTime = 100000.0f;
	this->idTimer = "";
	timer.start();
}

bool GameInfo::load() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();

	// carga de textos personajes

	SDL_Color textColor = {255, 255, 255};
	TTF_Font* font = TTF_OpenFont( "fonts/MK4.ttf", 28 );

	return (TextureManager::Instance()->loadFromRenderedText( this->textureID, characters[0]->getName(), textColor, font, render ));
}

void GameInfo::loadTextTimer() {
	//libero timer anterior
	TextureManager::Instance()->unload(this->textureID + this->idTimer);

	SDL_Renderer* render = MKGame::Instance()->getRenderer();
	TTF_Font* font = TTF_OpenFont( "fonts/mk1.ttf", 200 );

	//Timer
	SDL_Color timerColor = {227, 188, 119};
	std::stringstream timeText;
    timeText.str( "" );
    timeText << (int)((msTime - timer.getTicks()) / 1000.f);
    this->idTimer = timeText.str();
	TextureManager::Instance()->loadFromRenderedText( this->textureID, idTimer, timerColor, font, render);
	TTF_CloseFont(font);
}

bool GameInfo::load(SDL_Renderer* r) {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();
	TTF_Font* font = TTF_OpenFont( "fonts/mk1.ttf", 100 );
	string name = "";

	//Timer
	loadTextTimer();

	SDL_Color playerColor = {255, 255, 255};
	//jugador 1
	name = this->characters[0]->getName();
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, name, playerColor, font, render);

	//jugador 2
	name = this->characters[1]->getName();
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, name, playerColor, font, render);
	TTF_CloseFont(font);
	return true;
}


void GameInfo::HealthBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, SDL_Renderer* pRender, int player) {
	   Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
	   SDL_Color old;
	   SDL_GetRenderDrawColor(pRender, &old.r, &old.g, &old.g, &old.a);
	   SDL_Rect bgrect = { x, y, w, h };
	   SDL_SetRenderDrawColor(pRender, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
	   SDL_SetRenderDrawBlendMode(pRender, SDL_BLENDMODE_BLEND);
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
       SDL_SetRenderDrawColor( pRender, 227, 188, 119, 0xFF );
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

void GameInfo::time() {
	if (this->timer.getTicks() > 99000.f ) {
		this->timer.stop();
		this->timer.start();
	}
	loadTextTimer();
}


void GameInfo::update() {
	animation();
	time();
	if (this->characters[0]->getEnergy() <= 0.0f || this->characters[1]->getEnergy() <= 0.0f) {
		if (this->characters[0]->getEnergy() <= 0.0f) {
			FILE_LOG(logDEBUG) << "RESULT: " << this->characters[0]->getName() << "Wins";
		} else {
			FILE_LOG(logDEBUG) << "RESULT: " << this->characters[0]->getName() << " Wins";
		}
		MKGame::Instance()->setOnReset();
	}
}

void GameInfo::clean() {
	delete this->pParams;
	this->timer.stop();
	TTF_Quit();
}

void GameInfo::draw() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();

	//timer
	string id = this->textureID + this->idTimer;
	int width = WINDOW_MARGIN * 3;
	int x = (pParams->getWidth()/2 - width/2);
	int y = this->height * 0.1;
	int height = 15;
	TextureManager::Instance()->draw( id, x, y, width, height, render);

	string name = "";
	float energy = 0.0f;

	//jugador 1
	name = this->characters[0]->getName();
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	TextureManager::Instance()->draw( this->textureID + name, WINDOW_MARGIN, 0, barWidth/2, 10, render );
	energy = this->characters[0]->getEnergy();
	if (this->initAnimation) HealthBar(positionX * ratioX, 35, barWidth * ratioX, 20, percent, frontColor, bgColor, render, 0 );
	else HealthBar(positionX * ratioX, 35, barWidth * ratioX, 20, energy, frontColor, bgColor, render, 0 );

	//jugador 2
	name = this->characters[1]->getName();
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	TextureManager::Instance()->draw(this->textureID + name, pParams->getWidth() - barWidth/2 - WINDOW_MARGIN,0,barWidth/2, 10, render);
	energy = this->characters[1]->getEnergy();
	if (this->initAnimation) {
		HealthBar((this->width - WINDOW_MARGIN - barWidth) * ratioX, 35, barWidth * ratioX, 20, percent, frontColor, bgColor, render, 1);
	} else HealthBar((this->width - WINDOW_MARGIN - barWidth) * ratioX, 35, barWidth * ratioX, 20, energy, frontColor, bgColor, render, 1);
}


