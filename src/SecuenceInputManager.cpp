#include "../headers/SecuenceInputManager.h"



SecuenceInputManager* SecuenceInputManager::dm_pInstance = NULL;

SecuenceInputManager* SecuenceInputManager::Instance() {
	if (!dm_pInstance) {
		dm_pInstance = new SecuenceInputManager();
		return dm_pInstance;
	} else {
		return dm_pInstance;
	}
}
SecuenceInputManager::SecuenceInputManager(){
	this->specialSecuenceOne = "";
	this->specialSecuenceTwo = "";
	this->specialSecuenceOneActive = false;
	this->specialSecuenceTwoActive = false;
	this->textureID = "secuenceManager";
}

bool SecuenceInputManager::load() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();
	TTF_Font* font = TTF_OpenFont( "fonts/mk1.ttf", 50 );
	string secuencia = "";

	SDL_Color textColor = {255, 255, 255};
	//secuencia 1
	secuencia = this->specialSecuenceOne;
	std::transform(secuencia.begin(), secuencia.end(), secuencia.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID+"secuencia1", secuencia, textColor, font, render);

	//secuencia 2
	secuencia = this->specialSecuenceTwo;
	std::transform(secuencia.begin(), secuencia.end(), secuencia.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID+"secuencia2", secuencia, textColor, font, render);
	TTF_CloseFont(font);
	return true;
}

void SecuenceInputManager::draw() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();
	Window* window = GameGUI::getInstance()->getWindow();

	//secuencia 1
	string id = this->textureID + "secuencia1";
	int width = WINDOW_MARGIN * 3;
	int x = (window->widthPx/4);
	int y = window->heightPx* 0.3;
	int height = 15;
	TextureManager::Instance()->draw( id, x, y, width, height, render);

	//secuencia 2
	id = this->textureID + "secuencia2";
	width = WINDOW_MARGIN * 3;
	x = (window->widthPx*3/4);
	y = window->heightPx* 0.3;
	height = 15;
	TextureManager::Instance()->draw( id, x, y, width, height, render);
}

void SecuenceInputManager::update() {
	TextureManager::Instance()->unload(this->textureID + "secuencia1");
	TextureManager::Instance()->unload(this->textureID + "secuencia2");
	this->load();
}
