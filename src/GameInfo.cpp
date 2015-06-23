/*
 * GameInfo.cpp
 *
 *  Created on: 23/4/2015
 *      Author: julian
 */

#include "../headers/GameInfo.h"

GameInfo::GameInfo(const LoaderParams* pParams, vector<Character*> characters, std::string nameOne, std::string nameTwo) :
		SDLObjectGUI(pParams) {
	this->characters = characters;
	bgColor = {204, 0, 0, 150};
	frontColor = {0, 0, 204, 255};
	barWidth = ((pParams->getWidth() * 0.9) - (WINDOW_MARGIN * 2)) / 2;
	this->percent = 0.0f;
	this->fightAnimationTimer = 40;
	this->winnerAnimationTimer = 50;
	this->finishHimAnimationTimer = 30;
	this->fatalityAnimationTimer = 30;
	this->babalityAnimationTimer = 50;
	TTF_Init();
	this->initAnimation = true;
	this->showFightAnimation = true;
	this->msTime = 100000.0f;
	this->idTimer = "";
	this->roundCompleted = false;
	this->currentRound = 1;
	this->roundTriggered = false;
	this->roundOneCompleted = false;
	this->roundTwoCompleted = false;
	this->roundThreeCompleted = false;
	this->characterOneWins = 0;
	this->characterTwoWins = 0;
	this->charOneWon = false;
	this->charOneWon = false;
	this->showWinnerAnimation = false;
	this->showFinishHimAnimation = false;
	this->charOneAlreadyDeath = false;
	this->charTwoAlreadyDeath = false;

	this->nameOne = nameOne;
	this->nameTwo = nameTwo;

	this->playingRoundSound = false;
	this->playingFightSound = false;
	this->playingCharacterWinsSound = false;
	this->playingFinishHimSound  = false;
	this->lazyAnimationAlreadyTriggered = false;
	this->showFatalityAnimation = false;
	this->showBabalityAnimation = false;

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
	TTF_Font* font = TTF_OpenFont( "fonts/MK4.TTF", 70 );

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
	TTF_Font* font = TTF_OpenFont( "fonts/MK3.ttf", 40 );
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
	TTF_Font* fontMK3 = TTF_OpenFont( "fonts/MK3.ttf", 100 );
	string name = "";
	string round1 = "ROUND 1";
	string round2 = "ROUND 2";
	string round3 = "ROUND 3";
	string charOneWins = "";
	string charTwoWins = "";

	//Timer
	loadTextTimer();

	SDL_Color playerColor = {255, 255, 255};
	SDL_Color charWinsWhiteColor = {255, 255, 255};
	SDL_Color charWinsRedColor = {255, 0, 0};
	SDL_Color roundColor = {255, 255, 255};

	//jugador 1
	//name = this->characters[0]->getName();
	name = nameOne;
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, name, playerColor, font, render);

	//jugador 2
	//name = this->characters[1]->getName();
	name = nameTwo;
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, name, playerColor, font, render);

	//Round 1
	std::transform(round1.begin(), round1.end(), round1.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, round1, roundColor, fontMK3, render);

	//Round 2
	std::transform(round2.begin(), round2.end(), round2.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, round2, roundColor, fontMK3, render);

	//Round 3
	std::transform(round3.begin(), round3.end(), round3.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID, round3, roundColor, fontMK3, render);

	//fightRed sprite
	TextureManager::Instance()->load(FIGHT_IMAGE_SPRITE, "fightSprite", r);
	//fightYellow sprite
	TextureManager::Instance()->load(FIGHT2_IMAGE_SPRITE, "fight2Sprite", r);

	//finish him sprite
	TextureManager::Instance()->load(FINISH_HIM_IMAGE_SPRITE, "finishHimSprite", r);

	//fatality sprite
	TextureManager::Instance()->load(FATALITY_IMAGE_SPRITE, "fatalitySprite", r);

	//babality sprite
	TextureManager::Instance()->load(BABALITY_IMAGE_SPRITE, "babalitySprite", r);

	//character 1 wins
	//charOneWins = this->characters[0]->getName() + "  wins";
	charOneWins = nameOne + "  wins";
	std::transform(charOneWins.begin(), charOneWins.end(), charOneWins.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID+"white", charOneWins, charWinsWhiteColor, fontMK3, render);
	TextureManager::Instance()->loadFromRenderedText( this->textureID+"red", charOneWins, charWinsRedColor, fontMK3, render);

	//character 2 wins
	//charTwoWins = this->characters[1]->getName() + "  wins";
	charTwoWins = nameTwo + "  wins";
	std::transform(charTwoWins.begin(), charTwoWins.end(), charTwoWins.begin(), ::toupper);
	TextureManager::Instance()->loadFromRenderedText( this->textureID+"white", charTwoWins, charWinsWhiteColor, fontMK3, render);
	TextureManager::Instance()->loadFromRenderedText( this->textureID+"red", charTwoWins, charWinsRedColor, fontMK3, render);

	TTF_CloseFont(font);
	TTF_CloseFont(fontMK3);
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
	if (this->fightAnimationTimer > 0 && this->showFightAnimation){
		this->fightAnimationTimer -= 1;
	} else {
		//this->fightAnimationTimer = 40;
		this->showFightAnimation = false;
		if (!this->roundTriggered) {
			this->timerStart();
			//MKGame::Instance()->setAllowPlayerMovements(true);
			this->characters[0]->allowMovements = true;
			this->characters[1]->allowMovements = true;
			this->roundTriggered=true;
		}
	}
}

void GameInfo::time() {
	if (this->timer.getTicks() > 99000.f ) {
		this->timer.stop();
		this->timer.start();
	}
	loadTextTimer();
}

void GameInfo::prepareNewRound(){
	time();
	this->percent = 0.0f;
	this->fightAnimationTimer = 40;
	this->winnerAnimationTimer = 50;
	this->initAnimation = true;
	this->showFightAnimation = true;
	this->roundTriggered=false;
	this->charOneWon = false;
	this->charTwoWon = false;
	this->charOneAlreadyDeath = false;
	this->charTwoAlreadyDeath = false;
	this->playingRoundSound = false;
	this->playingFightSound = false;
	this->playingCharacterWinsSound = false;
	this->playingFinishHimSound  = false;
	this->characters[0]->setEnergy(1.0f);
	this->characters[1]->setEnergy(1.0f);
	this->characters[0]->setPositionX(GameGUI::getInstance()->getWindow()->widthPx / 4 - this->characters[0]->getWidth() * this->characters[0]->getRatioX()/2);
	this->characters[1]->setPositionX((GameGUI::getInstance()->getWindow()->widthPx / 4)*3 -  this->characters[1]->getWidth() * this->characters[1]->getRatioX()/2);
	this->characters[0]->clearMovementsFlags();
	this->characters[1]->clearMovementsFlags();
}

void GameInfo::triggerSounds() {
	if (!this->roundOneCompleted && this->initAnimation && !this->playingRoundSound) {
		SoundManager::Instance()->playSoundByAction("roundOne", 0);
		this->playingRoundSound = true;
	}
	if (!this->roundTwoCompleted && this->initAnimation && !this->playingRoundSound) {
		SoundManager::Instance()->playSoundByAction("roundTwo", 0);
		this->playingRoundSound = true;
	}
	if (!this->roundThreeCompleted && this->initAnimation && !this->playingRoundSound) {
		SoundManager::Instance()->playSoundByAction("roundThree", 0);
		this->playingRoundSound = true;
	}
	if (!this->initAnimation && this->showFightAnimation && !this->playingFightSound) {
		SoundManager::Instance()->playSoundByAction("fight", 0);
		this->playingFightSound = true;
	}
}


void GameInfo::update() {
	animation();
	loadTextTimer();
	// CONDICION DE FIN DE ROUND, SI CUALQUIERA DE LOS DOS SE QUEDA SIN VIDA O SI SE ACABA EL TIEMPO
	if (this->characters[0]->getEnergy() <= 0.0f || this->characters[1]->getEnergy() <= 0.0f ||
			this->timer.getTicks() > 99000.f ) {
		// TERMINO EL ROUND, NINGUNO DEBE MOVERSE MAS, SETEO ALLOW MOVEMENTS EN FALSE
		//MKGame::Instance()->setAllowPlayerMovements(false);
		this->characters[0]->allowMovements = false;
		this->characters[1]->allowMovements = false;

		// SI EL QUE MURIO O TIENE MENOS VIDA ES EL PLAYER ONE
		if (this->characters[0]->getEnergy() <= 0.0f ||
				this->characters[0]->getEnergy() <= this->characters[1]->getEnergy() ) {
			// PREGUNTO SI NO ESTA YA SETEADO EL FLAG DE QUE MURIO EL PLAYER ONE
			if (!this->charOneAlreadyDeath) {
				// SUMO VICTORIA A PLAYER 2 Y SETEO FLAGS DE QUE GANO Y SHOW WINNER ANIMATION
				this->characterTwoWins += 1;
				this->charTwoWon = true;
				this->showWinnerAnimation = true;
			}
			this->charOneAlreadyDeath = true;
			// PREGUNTO POR CONDICION DE QUE NO SEA FIN DE PELEA (NO TENGA DOS VICTORIAS)
			if (characterTwoWins < 2){
				if (this->characters[1]->getMovement() == STANCE) {
					this->characters[1]->setMovement(VICTORY_MOVEMENT);
					this->characters[1]->setCurrentSprite();
				}
				if (this->characters[0]->isTouchingGround(this->characters[0]->getPositionY())) {
					this->characters[0]->setMovement(FALLING_MOVEMENT);
					this->characters[0]->setCurrentSprite();
					this->characters[0]->isFalling = true;
				}
			}
			FILE_LOG(logDEBUG) <<"############ RESULT: " << this->characters[1]->getName() << "Wins #############";
			// REPRODUCE SONIDO DEL PLAYER 2 WINS
			if (!this->playingCharacterWinsSound && this->characterTwoWins < 2) {
				SoundManager::Instance()->playSoundByAction(characters[1]->getName() + "Wins",0);
				this->playingCharacterWinsSound = true;
			}

		// MISMA LOGICA QUE ARRIBA PARA EL CASO EN QUE MUERE EL PLAYER TWO
		} else {
			if (!this->charTwoAlreadyDeath) {
				this->characterOneWins += 1;
				this->charOneWon = true;
				this->showWinnerAnimation = true;
			}
			this->charTwoAlreadyDeath = true;
			if (characterOneWins < 2) {
				if (this->characters[0]->getMovement() == STANCE) {
					this->characters[0]->setMovement(VICTORY_MOVEMENT);
					this->characters[0]->setCurrentSprite();
				}
				if (this->characters[1]->isTouchingGround(this->characters[1]->getPositionY())){
					this->characters[1]->setMovement(FALLING_MOVEMENT);
					this->characters[1]->setCurrentSprite();
					this->characters[1]->isFalling = true;
				}
			}
			FILE_LOG(logDEBUG) << "############ RESULT: " << this->characters[0]->getName() << " Wins #############";
			if (!this->playingCharacterWinsSound && this->characterOneWins < 2) {
				SoundManager::Instance()->playSoundByAction(characters[0]->getName() + "Wins",0);
				this->playingCharacterWinsSound = true;
			}
		}
		loadTextTimer();

		// PARA EL CASO EN QUE ALGUNO DE LOS DOS HAYA GANADO DOS PELEAS SE ACTIVA LOGICA DE FINISH HIM
		if (this->characterOneWins == 2 || this->characterTwoWins == 2) {
			CollitionManager::Instance()->collitionEnabled = false;
			this->showFinishHimAnimation = true;
			MKGame::Instance()->isFinishimMoment = true;
			//MKGame::Instance()->setAllowPlayerMovements(true);
			this->characters[0]->allowMovements = true;
			this->characters[1]->allowMovements = true;
			if (this->finishHimAnimationTimer > 0) {
				this->finishHimAnimationTimer -= 1;
			} else {
				this->showFinishHimAnimation = false;
				CollitionManager::Instance()->collitionEnabled = true;
				SecuenceInputManager::Instance()->fatalityTime = true;
				//this->showFatalityAnimation = true;
			}
			if (MKGame::Instance()->showFatality && this->fatalityAnimationTimer > 0) {
				this->showFatalityAnimation = true;
				this->fatalityAnimationTimer -= 1;
			} else if (fatalityAnimationTimer == 0){
				this->showFatalityAnimation = false;
				MKGame::Instance()->setOnReset();
			}

			if (MKGame::Instance()->showBabality && this->babalityAnimationTimer > 0) {
				this->showBabalityAnimation = true;
				this->babalityAnimationTimer -= 1;
			} else if (babalityAnimationTimer == 0){
				this->showBabalityAnimation = false;
				MKGame::Instance()->setOnReset();
			}

			//finish him logic
			this->showWinnerAnimation = false; //Cuando este terminada la funcionalidad de finish him quitar esta linea
			if (!this->playingFinishHimSound) {
				SoundManager::Instance()->playSoundByAction("finishHim",0);
				this->playingFinishHimSound  = true;
			}
			if (this->characterOneWins == 2 && !this->lazyAnimationAlreadyTriggered) {
				//Character One won, char two receives fatality
				this->characters[1]->completeMovementAndChangeLazy = true;
				this->characters[0]->clearMovementsFlags();
//				this->characters[1]->setMovement(LAZY_MOVEMENT);
//				this->characters[1]->isLazy = true;
//				this->characters[1]->setCurrentSprite();
//				this->characters[1]->completeMovement();
				this->characters[1]->setPositionY(this->characters[1]->originalPosY);
				this->characters[1]->allowMovements = false;
				this->lazyAnimationAlreadyTriggered = true;
				MKGame::Instance()->lazyAnimationAlreadyTriggered = true;
			}
			if (this->characterTwoWins == 2 && !this->lazyAnimationAlreadyTriggered) {
				//Character One won, char two receives fatality
				this->characters[1]->completeMovementAndChangeLazy = true;
//				this->characters[0]->setMovement(LAZY_MOVEMENT);
//				this->characters[0]->isLazy = true;
//				this->characters[0]->setCurrentSprite();
//				this->characters[0]->completeMovement();
				this->characters[0]->setPositionY(this->characters[0]->originalPosY);
				this->characters[0]->allowMovements = false;
				this->lazyAnimationAlreadyTriggered = true;
				MKGame::Instance()->lazyAnimationAlreadyTriggered = true;
			}

		} else {
			//MKGame::Instance()->setOnReset();

			if (this->winnerAnimationTimer > 0) {
				if (this->showWinnerAnimation) {
					this->timerPause();
					this->winnerAnimationTimer -= 1;
				}
			} else {
				this->showWinnerAnimation = false;
			}
			if (!this->roundOneCompleted && !this->showWinnerAnimation) {
				this->roundOneCompleted = true;
				this->prepareNewRound();
			} else if (!this->roundTwoCompleted && !this->showWinnerAnimation) {
				this->roundTwoCompleted = true;
				this->prepareNewRound();
			} else if (!this->roundThreeCompleted && !this->showWinnerAnimation) {
				//MKGame::Instance()->setOnReset();
			}
		}
	}
	triggerSounds();
}

void GameInfo::clean() {
	delete this->pParams;
	this->timer.stop();
	TTF_Quit();
}

void GameInfo::draw() {
	SDL_Renderer* render = MKGame::Instance()->getRenderer();
	SDL_Rect rc;

	//timer
	string id = this->textureID + this->idTimer;
	int width = WINDOW_MARGIN * 3;
	int x = (pParams->getWidth()/2 - width/2);
	int y = this->height * 0.1;
	int height = 70 / ratioY;
	TextureManager::Instance()->draw( id, x, y, width, height, render);

	string name = "";
	string round1 = "ROUND 1";
	string round2 = "ROUND 2";
	string round3 = "ROUND 3";
	string charOneWins = "";
	string charTwoWins = "";
	float energy = 0.0f;

	//jugador 1
	//name = this->characters[0]->getName();
	name = this->nameOne;

	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	rc = TextureManager::Instance()->queryTexture(this->textureID + name);
	TextureManager::Instance()->draw( this->textureID + name, WINDOW_MARGIN, 0, rc.w / ratioX, 40 / ratioY, render );
	energy = this->characters[0]->getEnergy();
	if (this->initAnimation) HealthBar(positionX * ratioX, 35, barWidth * ratioX, 20, percent, frontColor, bgColor, render, 0 );
	else HealthBar(positionX * ratioX, 35, barWidth * ratioX, 20, energy, frontColor, bgColor, render, 0 );

	//jugador 2
	//name = this->characters[1]->getName();
	name = nameTwo;
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	rc = TextureManager::Instance()->queryTexture(this->textureID + name);
	TextureManager::Instance()->draw(this->textureID + name, pParams->getWidth() - rc.w / ratioX - WINDOW_MARGIN, 0, rc.w / ratioX, 40 / ratioY, render);
	energy = this->characters[1]->getEnergy();
	if (this->initAnimation) {
		HealthBar((this->width - WINDOW_MARGIN - barWidth) * ratioX, 35, barWidth * ratioX, 20, percent, frontColor, bgColor, render, 1);
	} else HealthBar((this->width - WINDOW_MARGIN - barWidth) * ratioX, 35, barWidth * ratioX, 20, energy, frontColor, bgColor, render, 1);

	//round 1
	float roundWidth = barWidth/2;
	float roundHeight = 10;
	float fightWidth = 60;
	float fightHeight = 20;

	if (this->initAnimation) {
		if (!this->roundOneCompleted) {
			std::transform(round1.begin(), round1.end(), round1.begin(), ::toupper);
			TextureManager::Instance()->draw(this->textureID + round1, pParams->getWidth()/2 - roundWidth/2,
					GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - roundHeight, roundWidth, roundHeight, render);
		} else if (!this->roundTwoCompleted) {
			std::transform(round2.begin(), round2.end(), round2.begin(), ::toupper);
			TextureManager::Instance()->draw(this->textureID + round2, pParams->getWidth()/2 - roundWidth/2,
					GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - roundHeight, roundWidth, roundHeight, render);

		} else if (!this->roundThreeCompleted) {
			std::transform(round3.begin(), round3.end(), round3.begin(), ::toupper);
			TextureManager::Instance()->draw(this->textureID + round3, pParams->getWidth()/2 - roundWidth/2,
					GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - roundHeight, roundWidth, roundHeight, render);
		}
	}

	if (!this->initAnimation && this->showFightAnimation) {
		if ( (this->fightAnimationTimer % 2) == 0){
			TextureManager::Instance()->draw("fightSprite", pParams->getWidth()/2 - fightWidth/2,
							GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - fightHeight, fightWidth, fightHeight, render);
		} else {
			TextureManager::Instance()->draw("fight2Sprite", pParams->getWidth()/2 - fightWidth/2,
										GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - fightHeight, fightWidth, fightHeight, render);
		}

	}

	float charWinsHeight = 10;
	float charWinsWidth = barWidth;
	if (this->charOneWon && this->showWinnerAnimation) {
		//char 1 wins
		if ((this->winnerAnimationTimer % 2) == 0) {
			charOneWins = nameOne + "  wins";
			//charOneWins = this->characters[0]->getName() + "  wins";
			std::transform(charOneWins.begin(), charOneWins.end(), charOneWins.begin(), ::toupper);
			TextureManager::Instance()->draw(this->textureID+"white"+charOneWins, pParams->getWidth()/2 - charWinsWidth/2,
					GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 4 - charWinsHeight - 10, charWinsWidth, charWinsHeight, render);
		} else {
			charOneWins = nameOne + "  wins";
			//charOneWins = this->characters[0]->getName() + "  wins";
			std::transform(charOneWins.begin(), charOneWins.end(), charOneWins.begin(), ::toupper);
			TextureManager::Instance()->draw(this->textureID+"red"+charOneWins, pParams->getWidth()/2 - charWinsWidth/2,
					GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 4 - charWinsHeight - 10, charWinsWidth, charWinsHeight, render);
		}

	} else if (this->charTwoWon && this->showWinnerAnimation) {
		//char 2 wins
		if ((this->winnerAnimationTimer % 2) == 0) {
			charTwoWins = nameTwo + "  wins";
			//charTwoWins = this->characters[1]->getName() + "  wins";
			std::transform(charTwoWins.begin(), charTwoWins.end(), charTwoWins.begin(), ::toupper);
			TextureManager::Instance()->draw(this->textureID+"white"+charTwoWins, pParams->getWidth()/2 - charWinsWidth/2,
					GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 4 - charWinsHeight - 10, charWinsWidth, charWinsHeight, render);
		} else {
			charTwoWins = nameTwo + "  wins";
			//charTwoWins = this->characters[1]->getName() + "  wins";
			std::transform(charTwoWins.begin(), charTwoWins.end(), charTwoWins.begin(), ::toupper);
			TextureManager::Instance()->draw(this->textureID+"red"+charTwoWins, pParams->getWidth()/2 - charWinsWidth/2,
					GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 4 - charWinsHeight - 10, charWinsWidth, charWinsHeight, render);
		}
	}

	float finishHimWidth = 100;
	float finishHimHeight = 25;

	if (this->showFinishHimAnimation) {
		TextureManager::Instance()->draw("finishHimSprite", pParams->getWidth()/2 - finishHimWidth/2,
				GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - finishHimHeight, finishHimWidth, finishHimHeight, render);
	}

	float fatalityWidth = 60;
	float fatalityHeight = 20;
	if (this->showFatalityAnimation) {
		TextureManager::Instance()->draw("fatalitySprite", pParams->getWidth()/2 - fatalityWidth/2,
				GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - fatalityHeight, fatalityWidth, fatalityHeight, render);
	}

	if (this->showBabalityAnimation) {
		TextureManager::Instance()->draw("babalitySprite", pParams->getWidth()/2 - fatalityWidth/2,
				GameGUI::getInstance()->getWindow()->getHeightPx()/ratioY/ 2 - fatalityHeight, fatalityWidth, fatalityHeight, render);
	}
}

void GameInfo::timerStart() {
	this->timer.start();
}

void GameInfo::timerStop() {
	this->timer.stop();
}

void GameInfo::timerPause() {
	this->timer.pause();
}

bool GameInfo::isRoundTriggered() {
	return this->isRoundTriggered();
}
