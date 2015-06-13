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
	this->specialSecuenceOne = getCleanSecuence();
	this->specialSecuenceTwo = getCleanSecuence();
	this->specialSecuenceOneActive = false;
	this->specialSecuenceTwoActive = false;
	this->textureID = "secuenceManager";
	this->elapsedTimeOne=0;
	this->elapsedTimeTwo=0;

	 this->joy1DownPressOnce=false;
	 this->joy1UpPressOnce=false;
	 this->joy1LeftPressOnce=false;
	 this->joy1RightPressOnce=false;
	 this->joy1BlockPressOnce=false;
	 this->joy2DownPressOnce=false;
	 this->joy2UpPressOnce=false;
	 this->joy2LeftPressOnce=false;
	 this->joy2RightPressOnce=false;
	 this->joy2BlockPressOnce=false;

	 loadSpecialMoves();
}

bool SecuenceInputManager::load() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();
	TTF_Font* font = TTF_OpenFont( "fonts/mk1.ttf", 50 );
	string secuencia = "";

	SDL_Color textColor = {255, 255, 255};
	//secuencia 1
	if (this->specialSecuenceOneActive){
		secuencia = this->specialSecuenceOne.substr(this->specialSecuenceOne.length()-SIMBOLS_TO_SHOW_SPECIAL_MOVES,SIMBOLS_TO_SHOW_SPECIAL_MOVES);
		this->specialSecuenceOnePreview = secuencia;
		std::transform(secuencia.begin(), secuencia.end(), secuencia.begin(), ::toupper);
		TextureManager::Instance()->loadFromRenderedText( this->textureID+"secuencia1", secuencia, textColor, font, render);
	}
	//secuencia 2
	if (this->specialSecuenceTwoActive){
		secuencia = this->specialSecuenceTwo.substr(this->specialSecuenceTwo.length()-SIMBOLS_TO_SHOW_SPECIAL_MOVES,SIMBOLS_TO_SHOW_SPECIAL_MOVES);
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
	int width = (WINDOW_MARGIN * 6/7)*SIMBOLS_TO_SHOW_SPECIAL_MOVES;
	int x = (window->widthPx*0.02);
	int y = window->heightPx* 0.06;
	int height = 15;
	if (this->specialSecuenceOneActive){
		TextureManager::Instance()->draw( id, x, y, width, height, render);
	}
	//secuencia 2
	id = this->textureID + "secuencia2"+this->specialSecuenceTwoPreview;
	width = (WINDOW_MARGIN * 6/7)*SIMBOLS_TO_SHOW_SPECIAL_MOVES;
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
			//this->timerOne.stop();
			this->reset(1);
		}
	}
	if (this->timerTwo.isStarted()  && (this->specialSecuenceTwoActive)){
		this->elapsedTimeTwo += (this->timerOne.getTicks()-this->elapsedTimeTwo);
		if ((int)(this->elapsedTimeTwo/1000.0f) > TIME_TOLERANCE_SPECIAL_MOVES){
			//this->timerTwo.stop();
			this->reset(2);
		}
	}
}

void SecuenceInputManager::reset(int secNum) {
	if (secNum==1){
		if (this->specialSecuenceOne.length()>100){
			this->specialSecuenceOne.erase(0,100-SIMBOLS_TO_SHOW_SPECIAL_MOVES);
		}
		this->specialSecuenceOne += getCleanSecuence();
		this->specialSecuenceOneActive = false;
		this->elapsedTimeOne=0;
		this->timerOne.stop();
	}else if (secNum==2){
		if (this->specialSecuenceTwo.length()>100){
			this->specialSecuenceTwo.erase(0,100-SIMBOLS_TO_SHOW_SPECIAL_MOVES);
		}
		this->specialSecuenceTwo += getCleanSecuence();
		this->specialSecuenceTwoActive = false;
		this->elapsedTimeTwo=0;
		this->timerTwo.stop();
	}

}

std::string SecuenceInputManager::getCleanSecuence() {
	std::string cleanSecuence="";
	for (int i=1; i <= SIMBOLS_TO_SHOW_SPECIAL_MOVES; i++){
		cleanSecuence += "-";
	}
	return cleanSecuence;
}

void SecuenceInputManager::loadSpecialMoves() {
		this->specialMoves.push_back(SECUENCE_FOR_SPECIAL_MOVE_0);
		this->specialMoves.push_back(SECUENCE_FOR_SPECIAL_MOVE_1);
		this->specialMoves.push_back(SECUENCE_FOR_SPECIAL_MOVE_2);
}

int SecuenceInputManager::detectSpecialSecuence(int playerNum) {
	int specialMoveNumber = -1;
	//logica para detectar movimientos especiales con secuencia exacta

	int i = 0;
	bool isMatch=false;


	while ((i<this->specialMoves.size()) && (!isMatch)){
		if ((playerNum==0) && (this->specialSecuenceOneActive)){
			std::string currentSecuenceToCompare = this->specialSecuenceOne.substr(this->specialSecuenceOne.length() - this->specialMoves[i].length(), this->specialMoves[i].length());
			if (this->specialMoves[i] == currentSecuenceToCompare){
				specialMoveNumber = i;
				isMatch = true;
			}
		}else if ((playerNum==1) && (this->specialSecuenceTwoActive)){
			std::string currentSecuenceToCompare = this->specialSecuenceTwo.substr(this->specialSecuenceTwo.length() - this->specialMoves[i].length(), this->specialMoves[i].length());
			if (this->specialMoves[i] == currentSecuenceToCompare){
				specialMoveNumber = i;
				isMatch = true;
			}
		}
		i++;
	}

	if (!isMatch){
		i=0;
		while ((i<this->specialMoves.size()) && (!isMatch)){
			std::string csChar = this->specialSecuenceOne.substr(this->specialSecuenceOne.length() - 1, 1);
			std::string smChar = this->specialMoves[i].substr(this->specialMoves[i].length()-1, 1);
			//se evaluan los ultimos caracteres, si son iguales se evalua el resto, sino se corta procesamiento
			if (csChar==smChar){

				int smIndex = 2;
				int csIndex = 2;
				int acuErrores = 0;
				while ((smIndex <= this->specialMoves[i].length()) && (acuErrores <= ERROR_TOLERANCE_SPECIAL_MOVES )){
					csChar = this->specialSecuenceOne.substr(this->specialSecuenceOne.length() - smIndex, 1);
					smChar = this->specialMoves[i].substr(this->specialMoves[i].length()- csIndex, 1);
					if (!csChar==smChar){
						acuErrores++;
						csIndex++;
					}else if (csChar==smChar){
						smIndex++;
						csIndex++;
					}



				}
			}

		}

	}


	return specialMoveNumber;
}
