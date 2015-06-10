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
	this->specialSecuenceOne = "-------";
	this->specialSecuenceTwo = "-------";
	this->specialSecuenceOneActive = false;
	this->specialSecuenceTwoActive = false;
	this->textureID = "secuenceManager";
	this->elapsedTimeOne=0;
	this->elapsedTimeTwo=0;

	 this->joy1DownPressOnce=false;
	 this->joy1UpPressOnce=false;
	 this->joy1LeftPressOnce=false;
	 this->joy1RightPressOnce=false;
	 this->joy2DownPressOnce=false;
	 this->joy2UpPressOnce=false;
	 this->joy2LeftPressOnce=false;
	 this->joy2RightPressOnce=false;
};
}

bool SecuenceInputManager::load() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();
	TTF_Font* font = TTF_OpenFont( "fonts/mk1.ttf", 50 );
	string secuencia = "";

	SDL_Color textColor = {255, 255, 255};
	//secuencia 1
	if (this->specialSecuenceOneActive){
		secuencia = this->specialSecuenceOne.substr(this->specialSecuenceOne.length()-7,7);
		this->specialSecuenceOnePreview = secuencia;
		std::transform(secuencia.begin(), secuencia.end(), secuencia.begin(), ::toupper);
		TextureManager::Instance()->loadFromRenderedText( this->textureID+"secuencia1", secuencia, textColor, font, render);
	}
	//secuencia 2
	if (this->specialSecuenceTwoActive){
		secuencia = this->specialSecuenceTwo.substr(this->specialSecuenceTwo.length()-7,7);
		this->specialSecuenceTwoPreview = this->specialSecuenceTwo;
		std::transform(secuencia.begin(), secuencia.end(), secuencia.begin(), ::toupper);
		TextureManager::Instance()->loadFromRenderedText( this->textureID+"secuencia2", secuencia, textColor, font, render);
	}
	TTF_CloseFont(font);
	return true;
}

void SecuenceInputManager::draw() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();
	Window* window = GameGUI::getInstance()->getWindow();

	//secuencia 1
	string id = this->textureID + "secuencia1"+this->specialSecuenceOnePreview;
	int width = WINDOW_MARGIN * 6;
	int x = (window->widthPx*0.02);
	int y = window->heightPx* 0.06;
	int height = 15;
	if (this->specialSecuenceOneActive){
		TextureManager::Instance()->draw( id, x, y, width, height, render);
	}
	//secuencia 2
	id = this->textureID + "secuencia2"+this->specialSecuenceTwoPreview;
	width = WINDOW_MARGIN * 6;
	x = (window->widthPx*3/4);
	y = window->heightPx* 0.3;
	height = 15;
	if (this->specialSecuenceTwoActive){
		TextureManager::Instance()->draw( id, x, y, width, height, render);
	}
}

void SecuenceInputManager::update() {
	TextureManager::Instance()->unload(this->textureID + "secuencia1"+this->specialSecuenceOnePreview);
	TextureManager::Instance()->unload(this->textureID + "secuencia2"+this->specialSecuenceTwoPreview);
	this->load();

	if ((!this->timerOne.isStarted()) && (this->specialSecuenceOneActive)){
		this->timerOne.start();
	}
	if ((!this->timerTwo.isStarted()) && (this->specialSecuenceTwoActive)){
		this->timerTwo.start();
	}
	if (this->timerOne.getTicks()>99000){
			this->timerOne.stop();
			this->timerOne.start();
	}
	if (this->timerTwo.getTicks()>99000){
			this->timerTwo.stop();
			this->timerTwo.start();
	}
	if (this->timerOne.isStarted()  && (this->specialSecuenceOneActive)){
		this->elapsedTimeOne += (this->timerOne.getTicks()-this->elapsedTimeOne);
		if ((int)(this->elapsedTimeOne/1000.0f) > TIME_TOLERANCE_SPECIAL_MOVES){
			this->timerOne.stop();
			this->reset(1);
		}
	}
	if (this->timerTwo.isStarted()  && (this->specialSecuenceTwoActive)){
		this->elapsedTimeTwo += (this->timerOne.getTicks()-this->elapsedTimeTwo);
		if ((int)(this->elapsedTimeTwo/1000.0f) > TIME_TOLERANCE_SPECIAL_MOVES){
			this->timerTwo.stop();
			this->reset(2);
		}
	}



}

void SecuenceInputManager::reset(int secNum) {
	if (secNum==1){
		if (this->specialSecuenceOne.length()>100){
			this->specialSecuenceOne.erase(0,90);
		}
		this->specialSecuenceOne += "-------";
		this->specialSecuenceOneActive = false;
		this->elapsedTimeOne=0;
	}else if (secNum==2){
		if (this->specialSecuenceTwo.length()>100){
			this->specialSecuenceTwo.erase(0,90);
		}
		this->specialSecuenceTwo += "-------";
		this->specialSecuenceTwoActive = false;
		this->elapsedTimeTwo=0;
	}
}
