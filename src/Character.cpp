/*
 * Character.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Character.h"

#include <SDL_render.h>
#include <SDL_timer.h>
#include <utility>
#include <fstream>
#include "../headers/MKGame.h"

#include "../headers/GameGUI.h"
#include "../headers/LoaderParams.h"
#include "../headers/Log.h"
#include "../headers/Stage.h"
#include "../headers/TextureManager.h"
#include "../headers/Window.h"
#include <cmath>        // std::abs

using namespace std;

float gravity = 14.0f;
float jumpVel = 60.0f;
float jumpVelFalling = 40.0f;
float jumpVelRoof = 80.0f;
float jumpVelFallingUpper = 50.0f;


std::map<std::string,int> Character::movesCounter;

bool somePunchInputCommand(InputCommand inputCommand);
bool someKickInputCommand(InputCommand inputCommand);
bool validateSpritesForSelectedCharacter(std::string characterPath);

Character::Character(const LoaderParams* pParams, bool isRightOriented) :
		SDLObjectGUI(pParams) {
		this->isRightOriented = isRightOriented;
		this->name = pParams->getTextureID();
		this->yGround = (GameGUI::getInstance()->getStage()->getYGround() - this->height) * ratioY;
		this->imagePath = ROOT_IMAGE_PATH;
		//TODO: Review positions according to logic and pixels measures.
		//override constructor
		// initializing movements statements
		clearMovementsFlags();
		this->initCShapes(2,this->positionX, this->positionY,this->width,this->height);
		this->setIsWeapon(false);
		//TODO: setear en false
		this->fire = false;
		gravity = 14.0f;
		jumpVel = 60.0f;
		this->smoothOffsetX = 0;
		this->beingPushed = false;
		this->allowMovements = false;
}

Character::Character(const LoaderParams* pParams) :
		SDLObjectGUI(pParams) {
		this->name = pParams->getTextureID();
		this->yGround = (GameGUI::getInstance()->getStage()->getYGround() - this->height) * ratioY;
		this->originalPosY =  this->yGround;
		this->imagePath = ROOT_IMAGE_PATH;
		this->isAltPlayer = false;
		//TODO: Review positions according to logic and pixels measures.
		//override constructor
		// initializing movements statements
		clearMovementsFlags();
		//initializing shapes for colitions
		this->initCShapes(2,this->positionX, this->positionY,this->width,this->height);
		this->setIsWeapon(false);
		//TODO: setear en false
		this->fire = false;
		gravity = 14.0f;
		jumpVel = 60.0f;
		this->smoothOffsetX = 0;
		this->beingPushed = false;
		this->allowMovements = false;
}



bool Character::load(SDL_Renderer* render) {
	this->renderer = render;
	std::string characterPath = this->imagePath+this->name;
	bool isValid = validateSpritesForSelectedCharacter(characterPath);
	if (!isValid) {
		characterPath = this->imagePath + DEFAULT_PATH_SPRITE_CONTAINER;
	}

	Sprite* spriteWalk = new Sprite(this->name+this->playerNumber+WALK_SUFFIX, characterPath+WALK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 8, this->isAltPlayer, this->altColor);
	Sprite* spriteStance = new Sprite(this->name+this->playerNumber+STANCE_SUFFIX, characterPath+STANCE_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 9, this->isAltPlayer, this->altColor);
	Sprite* spriteJump = new Sprite(this->name+this->playerNumber+JUMP_SUFFIX, characterPath+JUMP_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);
	Sprite* spriteJumpDiagonal = new Sprite(this->name+this->playerNumber+JUMP_DIAGONAL_SUFFIX, characterPath+DIAGONAL_JUMP_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 9, this->isAltPlayer, this->altColor);
	Sprite* spriteDuck = new Sprite(this->name+this->playerNumber+DUCK_SUFFIX, characterPath+DUCK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);
	Sprite* spriteHighPunch = new Sprite(this->name+this->playerNumber+HI_PUNCH_SUFFIX, characterPath+HIPUNCH_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 7, this->isAltPlayer, this->altColor);
	Sprite* spriteLowPunch = new Sprite(this->name+this->playerNumber+LO_PUNCH_SUFFIX, characterPath+LOPUNCH_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 6, this->isAltPlayer, this->altColor);
	Sprite* spriteDuckPunch = new Sprite(this->name+this->playerNumber+DUCK_PUNCH_SUFFIX, characterPath+DUCKPUNCH_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 2, this->isAltPlayer, this->altColor);
	Sprite* spriteUpperCut = new Sprite(this->name+this->playerNumber+UPPERCUT_SUFFIX, characterPath+UPPERCUT_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 5, this->isAltPlayer, this->altColor);
	Sprite* spriteLowKick = new Sprite(this->name+this->playerNumber+LOW_KICK_SUFFIX, characterPath+LOW_KICK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 6, this->isAltPlayer, this->altColor);
	Sprite* spriteHighKick = new Sprite(this->name+this->playerNumber+HIGH_KICK_SUFFIX, characterPath+HIGH_KICK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 6, this->isAltPlayer, this->altColor);
	Sprite* spriteDuckLowKick = new Sprite(this->name+this->playerNumber+DUCK_LOW_KICK_SUFFIX, characterPath+DUCK_LOW_KICK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 3, this->isAltPlayer, this->altColor);
	Sprite* spriteDuckHighKick = new Sprite(this->name+this->playerNumber+DUCK_HIGH_KICK_SUFFIX, characterPath+DUCK_HIGH_KICK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 4, this->isAltPlayer, this->altColor);
	Sprite* spriteSuperKick = new Sprite(this->name+this->playerNumber+SUPER_KICK_SUFFIX, characterPath+SUPER_KICK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 8, this->isAltPlayer, this->altColor);
	Sprite* spriteAirHighKick = new Sprite(this->name+this->playerNumber+AIR_HIGH_kICK_SUFFIX, characterPath+AIR_HIGH_KICK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);
	Sprite* spriteAirLowKick = new Sprite(this->name+this->playerNumber+AIR_LOW_kICK_SUFFIX, characterPath+AIR_LOW_KICK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);
	Sprite* spriteBlock = new Sprite(this->name+this->playerNumber+BLOCK_SUFFIX, characterPath+BLOCK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);
	Sprite* spriteDuckBlock = new Sprite(this->name+this->playerNumber+DUCK_BLOCK_SUFFIX, characterPath+DUCK_BLOCK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);
	Sprite* spriteUnderKick = new Sprite(this->name+this->playerNumber+UNDER_KICK_SUFFIX, characterPath+UNDER_KICK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 8, this->isAltPlayer, this->altColor);
	Sprite* spriteAirPunch = new Sprite(this->name+this->playerNumber+AIR_PUNCH_SUFFIX, characterPath+AIR_PUNCH_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);
	Sprite* spriteBeingHintStanceUp = new Sprite(this->name+this->playerNumber+BEING_HINT_STANCE_UP_SUFFIX, characterPath+BEING_HINT_STANCE_UP_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 3, this->isAltPlayer, this->altColor);
	Sprite* spriteBeingHintStanceDown = new Sprite(this->name+this->playerNumber+BEING_HINT_STANCE_DOWN_SUFFIX, characterPath+BEING_HINT_STANCE_DOWN_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 3, this->isAltPlayer, this->altColor);
	Sprite* spriteBeingHintFallingUnderKick = new Sprite(this->name+this->playerNumber+BEING_HINT_FALLING_UNDER_KICK_SUFFIX, characterPath+BEING_HINT_FALLING_UNDER_KICK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 11, this->isAltPlayer, this->altColor);
	Sprite* spriteHintFlying = new Sprite(this->name+this->playerNumber+HINT_FLYING_SUFFIX, characterPath+HINT_FLYING_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 9, this->isAltPlayer, this->altColor);
	Sprite* spriteGetUp = new Sprite(this->name+this->playerNumber+GET_UP_SUFFIX, characterPath+GET_UP_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 7, this->isAltPlayer, this->altColor);
	Sprite* spriteSweep = new Sprite(this->name+this->playerNumber+SWEEP_SUFFIX, characterPath+SWEEP_SPRITE,
				renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);
	Sprite* spriteFire = new Sprite(this->name+this->playerNumber+FIRE_SUFFIX, characterPath+FIRE_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);
	Sprite* spriteBabality = new Sprite(this->name+this->playerNumber+BABALITY_SUFFIX, characterPath+BABALITY_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 3, this->isAltPlayer, this->altColor);
	Sprite* spriteReptile = new Sprite(this->name+this->playerNumber+REPTILE_SUFFIX, characterPath+REPTILE_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 16, this->isAltPlayer, this->altColor);
	Sprite* spriteBurning = new Sprite(this->name+this->playerNumber+BURNING_SUFFIX, characterPath+BURNING_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 16, this->isAltPlayer, this->altColor);
	Sprite* spriteHeadless = new Sprite(this->name+this->playerNumber+HEADLESS_SUFFIX, characterPath+HEADLESS_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);
	Sprite* spriteHeadlessBlood = new Sprite(this->name+this->playerNumber+HEADLESS_BLOOD_SUFFIX, characterPath+HEADLESS_BLOOD_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 8, this->isAltPlayer, this->altColor);
	Sprite* spriteFriendship = new Sprite(this->name+this->playerNumber+FRIENDSHIP_SUFFIX, characterPath+FRIENDSHIP_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 19, this->isAltPlayer, this->altColor);
	Sprite* spriteVictory = new Sprite(this->name+this->playerNumber+VICTORY_SUFFIX, characterPath+VICTORY_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);
	Sprite* spriteLazy = new Sprite(this->name+this->playerNumber+LAZY_SUFFIX, characterPath+LAZY_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 8, this->isAltPlayer, this->altColor);
	Sprite* spriteFalling = new Sprite(this->name+this->playerNumber+FALLING_SUFFIX, characterPath+FALLING_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 6, this->isAltPlayer, this->altColor);
	Sprite* spriteSpecial = new Sprite(this->name+this->playerNumber+SPECIAL_SUFFIX, characterPath+SPECIAL_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 5, this->isAltPlayer, this->altColor);
	Sprite* spriteSpecialHint = new Sprite(this->name+this->playerNumber+SPECIAL_HINT_SUFFIX, characterPath+SPECIAL_HINT_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1, this->isAltPlayer, this->altColor);

	//TODO: Files path must be generated depending on the character
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+WALK_SUFFIX, spriteWalk));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+STANCE_SUFFIX, spriteStance));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+JUMP_SUFFIX, spriteJump));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+JUMP_DIAGONAL_SUFFIX, spriteJumpDiagonal));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+DUCK_SUFFIX, spriteDuck));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+HI_PUNCH_SUFFIX, spriteHighPunch));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+LO_PUNCH_SUFFIX, spriteLowPunch));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+DUCK_PUNCH_SUFFIX, spriteDuckPunch));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+UPPERCUT_SUFFIX, spriteUpperCut));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+LOW_KICK_SUFFIX, spriteLowKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+HIGH_KICK_SUFFIX, spriteHighKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+DUCK_LOW_KICK_SUFFIX, spriteDuckLowKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+DUCK_HIGH_KICK_SUFFIX, spriteDuckHighKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+SUPER_KICK_SUFFIX, spriteSuperKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+AIR_HIGH_kICK_SUFFIX, spriteAirHighKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+AIR_LOW_kICK_SUFFIX, spriteAirLowKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+BLOCK_SUFFIX, spriteBlock));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+DUCK_BLOCK_SUFFIX, spriteDuckBlock));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+UNDER_KICK_SUFFIX, spriteUnderKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+AIR_PUNCH_SUFFIX, spriteAirPunch));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+BEING_HINT_STANCE_UP_SUFFIX, spriteBeingHintStanceUp));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+BEING_HINT_STANCE_DOWN_SUFFIX, spriteBeingHintStanceDown));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+BEING_HINT_FALLING_UNDER_KICK_SUFFIX, spriteBeingHintFallingUnderKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+HINT_FLYING_SUFFIX, spriteHintFlying));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+GET_UP_SUFFIX, spriteGetUp));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+SWEEP_SUFFIX, spriteSweep));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+FIRE_SUFFIX, spriteFire));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+BABALITY_SUFFIX, spriteBabality));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+REPTILE_SUFFIX, spriteReptile));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+HEADLESS_SUFFIX, spriteHeadless));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+HEADLESS_BLOOD_SUFFIX, spriteHeadlessBlood));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+FRIENDSHIP_SUFFIX, spriteFriendship));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+VICTORY_SUFFIX, spriteVictory));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+LAZY_SUFFIX, spriteLazy));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+BURNING_SUFFIX, spriteBurning));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+FALLING_SUFFIX, spriteFalling));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+SPECIAL_SUFFIX, spriteSpecial));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+this->playerNumber+SPECIAL_HINT_SUFFIX, spriteSpecialHint));

	return true;
}

void Character::render(SDL_Renderer* render) {
}


void Character::draw() {
	int currentFrame;
	if(this->isDucking || this->isHeadless || this->isVictory || this->isBabality || this->isFalling) {
		currentFrame = currentSprite->getNextFrameWithLimit();
	} else {
		if (shouldMoveForward()) {
			if (this->getMovement() == HEADLESS_BLOOD_MOVEMENT){
				currentFrame = currentSprite->getNextFrameWithLimitAndLoop(4, 8, 6);
			}
			else if (this->getMovement() == REPTILE_MOVEMENT){
				currentFrame = currentSprite->getNextFrameWithLimitAndShowFrame(3);
			}
			else if (this->getMovement() == BURNING_MOVEMENT){
				currentFrame = currentSprite->getNextFrameWithLimitAndLoop(4, 9, 5);
			}
			else if (this->getMovement() == FRIENDSHIP_MOVEMENT){
				currentFrame = currentSprite->getNextFrameWithLimitAndLoop(3, 18, 4);
			}
			else if (this->getMovement() == SPECIAL_HINT_MOVEMENT){
				currentFrame = currentSprite->getNextFrameWithLimitAndShowFrame(0);
			}
			else {
				currentFrame = currentSprite->getNextForwardingFrame();
			}
		} else {
			currentFrame = currentSprite->getNextBackwardingFrame();
		}
	}
	TextureManager::Instance()->drawFrame(currentSprite->getSpriteId(),
			(int) positionX, (int) positionY, width * ratioX, height * ratioY,
			1, currentFrame,
			renderer, currentSprite->getSpriteWidth(), currentSprite->getSpriteHeight(), (!isRightOriented)? SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);

	if (this->showBoxes) {
		//draw original sprite
		SDL_Rect outlineRect = { this->positionX, this->positionY, this->getWidth() * ratioX, this->height * ratioY };
		SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
		SDL_RenderDrawRect( renderer, &outlineRect );

		//draw box colisionale
		SDL_Rect outlineRect2 = { this->posXBox, this->posYBox, this->widthBox, this->heightBox };
		SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
		SDL_RenderDrawRect( renderer, &outlineRect2 );

		SDL_Rect outlineRect3 = { this->posXBox2, this->posYBox2, this->widthBox2, this->heightBox2 };
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
		SDL_RenderDrawRect( renderer, &outlineRect3 );

		//lineas bordes
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderDrawLine( renderer,
				WINDOW_MARGIN * ratioX, /* inicio X */
				0, 						/* inicio Y */
				WINDOW_MARGIN * ratioX, /* fin X */
				GameGUI::getInstance()->getWindow()->getHeightPx()); /* fin Y*/

		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderDrawLine( renderer,
				GameGUI::getInstance()->getWindow()->widthPx - WINDOW_MARGIN * ratioX,
				0,
				GameGUI::getInstance()->getWindow()->widthPx - WINDOW_MARGIN * ratioX,
				GameGUI::getInstance()->getWindow()->getHeightPx());

		//lineas dinamicas chequeo de desplazamaiento
		float posXCharacter = this->posXBox; 						/* pos character en unidades logicas*/
		float windowWidth = GameGUI::getInstance()->getWindow()->getWidth();	/* tamaño de la ventana en unidades logicas */
		float characterWidth = this->widthBox;
		if (this->isMovingRight()) {
			SDL_SetRenderDrawColor( renderer, 0x00, 0xCC, 0xCC, 0xFF );
			SDL_RenderDrawLine( renderer,
					(posXCharacter + characterWidth ),
					0,
					(posXCharacter + characterWidth ),
					GameGUI::getInstance()->getWindow()->getHeightPx());
		}

		if (this->isMovingLeft()) {
			SDL_SetRenderDrawColor( renderer, 0x00, 0xCC, 0xCC, 0xFF );
			SDL_RenderDrawLine( renderer,
					posXCharacter,
					0,
					posXCharacter,
					GameGUI::getInstance()->getWindow()->getHeightPx());
		}

	}
	//this->beingPushed = false;
}

bool Character::shouldMoveForward() {
	if ( (this->isRightOriented && (isJumpingRight || isWalkingRight)) || this->isUnderKick ||
			this->isKickingSuper || (!this->isRightOriented && (isJumpingLeft || isWalkingLeft))
			|| isBeingHintFallingUnderKick || isGettingUp || isHintFlying || isHintFlyingUpper || isReptile
			|| isFriendship || isHeadlessBlood || isBurning || isSpecial) {
		return true;
	} else {
		return false;
	}
}

bool Character::reachedWindowLeftLimit(){
	if (this->posXBox / ratioX < WINDOW_MARGIN) return true;
	return false;
}

bool Character::reachedWindowRightLimit(){
	float windowWidth = GameGUI::getInstance()->getWindow()->getWidth();
	if ( ( windowWidth - (this->posXBox / ratioX) - this->widthBox / ratioX ) < WINDOW_MARGIN) return true;
	return false;
}

void Character::fixOrientation() {
	Character * p1 = GameGUI::getInstance()->getCharacters()[0];
	Character * p2 = GameGUI::getInstance()->getCharacters()[1];
	if ((p1->movement != SWEEP_MOVEMENT && p2->movement != SWEEP_MOVEMENT)) {
		if (p1->posXBox < p2->posXBox) {
			p1->isRightOriented = true;
			p2->isRightOriented = false;
		} else {
			p1->isRightOriented = false;
			p2->isRightOriented = true;
		}
	}
}

void Character::update() {

	this->previousMovement = getMovement();
	this->beingPushed = false;
	if (this->orientationPosXFix != 0) { //acomoda la posX si se desplaza la cámara
		this->fixPosXStandingCharacter();
		this->orientationPosXFix = 0;
	}
	fixOrientation();
	InputCommand playerCommand;
	if (this->playerNumber == "1") {
		playerCommand = InputControl::Instance()->getFirstPlayerMove();

	} else {
		playerCommand = InputControl::Instance()->getSecondPlayerMove();
	}


	cout << "plyer: " << this->getName() << " Move: " << getMovement() << endl;
	//InputCommand optionCommand = keyboardControl.getControlOption();
	// Check if critical movements have finished

	if (this->isFinishingMove){
		doFinisher();
	}


	if (getMovement() == "stance" && completeMovementAndChangeLazy){
		this->setMovement(LAZY_MOVEMENT);
		this->isLazy = true;
		this->setCurrentSprite();
		completeMovementAndChangeLazy = false;
	}

	if (getMovement() == "stance" && completeMovementAndChangeVictory){
		this->setMovement(VICTORY_MOVEMENT);
		this->setCurrentSprite();
		this->isVictory = true;
		completeMovementAndChangeVictory = false;
	}

	else if (isReptile){
		isReptile = true;
	}
	else if (isBurning){
		setMovement(BURNING_MOVEMENT);
		setCurrentSprite();
	}
	else if (isLazy){
		completeMovement();
	}

	else if (isSpecial){
		completeMovement();
	}

	else if (isSubzeroFiring) {
		completeMovement();
	}
	else if (isHeadless){
		isHeadless = true;
	}
	else if (isFalling){
		isFalling = true;
	}

	else if (isHeadlessBlood){
		setMovement(HEADLESS_BLOOD_MOVEMENT);
		setCurrentSprite();
//		completeMovement();
	}

	else if (isBabality){
		isBabality = true;
	}

	else if (isFriendship) {
		isFriendship = true;

	}

	else if (isVictory) {
		isVictory = true;
	}

	else if (isSubzeroSweeping){
		sweepMovement();
	}

	else if (isSpecial_hint){
		hitWithRoof();
	}

	else if (isBeingHintStanceUp){
		completeMovement();
	}

	else if (isBeingHintStanceDown){
		completeMovement();
	}
	else if(isBeingHintFallingUnderKick){
		completeMovement();
	}
	else if(isHintFlying){
		flyFalling();
	}
	else if(isHintFlyingUpper){
		flyFallingUpper();
	}
	else if(isGettingUp){
		completeMovement();
	}
	else if (getMovement() == HINT_FLYING_MOVEMENT){
		setCurrentSprite();
		flyFalling();
	}
	else if (getMovement() == HINT_FLYING_UPPER_MOVEMENT){
		setCurrentSprite();
		flyFallingUpper();
	}
	else if (getMovement() == BEING_HINT_FALLING_UNDER_KICK_MOVEMENT){
		setCurrentSprite();
		completeMovement();
	}
	else if (getMovement() == BEING_HINT_STANCE_UP_MOVEMENT && !isTouchingGround(positionY)){
		setMovement(HINT_FLYING_MOVEMENT);
		setCurrentSprite();
		completeMovement();
	}
	else if (getMovement() == BEING_HINT_STANCE_UP_MOVEMENT && isTouchingGround(positionY)){
		setCurrentSprite();
		completeMovement();
	}
	else if (getMovement() == BEING_HINT_STANCE_DOWN_MOVEMENT && !isTouchingGround(positionY)){
		setMovement(HINT_FLYING_MOVEMENT);
		setCurrentSprite();
		completeMovement();
	}
	else if (getMovement() == BEING_HINT_STANCE_DOWN_MOVEMENT && isTouchingGround(positionY)){
		setCurrentSprite();
		completeMovement();
	}
	else if (getMovement() == GET_UP_MOVEMENT){
		setCurrentSprite();
		completeMovement();
	}
	else if (isJumping && playerCommand == FIRST_PLAYER_FIRE && !someKickInputCommand(playerCommand) && !somePunchInputCommand(playerCommand)) {
		fire = true;
		SoundManager::Instance()->playSoundByAction("fire",0);
		jump();
	}
	else if (isJumping && !someKickInputCommand(playerCommand) && !somePunchInputCommand(playerCommand)) {
		jump();
	}
	else if (isJumping && someKickInputCommand(playerCommand)) {
		this->setMovement(AIR_HIGH_kICK_MOVEMENT);
		setCurrentSprite();
		airHighKick();
	} else if (isJumping && somePunchInputCommand(playerCommand)) {
		this->setMovement(AIR_PUNCH_MOVEMENT);
		setCurrentSprite();
		airPunch();
	} else if (isJumpingRight && !someKickInputCommand(playerCommand) && !somePunchInputCommand(playerCommand)) {
		jumpRight();
	} else if (isJumpingRight && someKickInputCommand(playerCommand)) {
		this->setMovement(AIR_LOW_kICK_MOVEMENT);
		setCurrentSprite();
		airLowKickRight();
	} else if (isJumpingRight && somePunchInputCommand(playerCommand)) {
		this->setMovement(AIR_PUNCH_MOVEMENT);
		setCurrentSprite();
		airPunchRight();
	} else if (isJumpingLeft && !someKickInputCommand(playerCommand) && !somePunchInputCommand(playerCommand)) {
		jumpLeft();
	} else if (isJumpingLeft && someKickInputCommand(playerCommand)) {
		this->setMovement(AIR_LOW_kICK_MOVEMENT);
		setCurrentSprite();
		airLowKickLeft();
	} else if (isJumpingLeft && somePunchInputCommand(playerCommand)) {
		this->setMovement(AIR_PUNCH_MOVEMENT);
		setCurrentSprite();
		airPunchLeft();
	}else if (isKickingHigh){
		completeMovement();
	} else if (isKickingLow) {
		completeMovement();
	} else if (isKickingDuckHigh) {
		completeMovement();
	} else if (isKickingDuckLow) {
		completeMovement();
	} else if (isKickingSuper) {
		completeMovement();
	} else if (isUnderKick) {
		completeMovement();
	} else if (isPunchingAnUppercut) {
		completeMovement();
	} else if (isPunchingLow) {
		completeMovement();
	} else if (isPunchingDuck) {
		completeMovement();
	} else if (isPunchingHigh) {

		completeMovement();

	} else if (isKickingAirHigh) {
		airHighKick();
	} else if (isKickingAirLowRight) {
		airLowKickRight();
	} else if (isKickingAirLowLeft) {
		airLowKickLeft();
	} else if (isAirPunching) {
		airPunch();
	} else if (isAirPunchingRight) {
		airPunchRight();
	} else if (isAirPunchingLeft) {
		airPunchLeft();
	} else if (isBeingHintStanceUp) {
		completeMovement();
	} else {
		// Movements validation to refresh frames
		if (isDucking && (playerCommand != FIRST_PLAYER_MOVE_DOWN &&
				playerCommand != FIRST_PLAYER_MOVE_DOWN_LEFT &&
				playerCommand != FIRST_PLAYER_MOVE_DOWN_RIGHT &&
				playerCommand != FIRST_PLAYER_FIRE)) {
			this->refreshFrames();
		}
		if (isWalkingRight && playerCommand != FIRST_PLAYER_MOVE_RIGHT){
			this->refreshFrames();
		}
		if (isWalkingLeft && playerCommand != FIRST_PLAYER_MOVE_LEFT){
			this->refreshFrames();
		}

		this->clearMovementsFlags();

		Character* victim = getVictim();

		if (this->allowMovements) {
			switch (playerCommand) {
			case FIRST_PLAYER_MOVE_RIGHT:
				this->setMovement(WALKING_RIGHT_MOVEMENT);
				setCurrentSprite();
				walkRight();
				break;
			case FIRST_PLAYER_MOVE_LEFT:
				this->setMovement(WALKING_LEFT_MOVEMENT);
				setCurrentSprite();
				walkLeft();
				break;
			case FIRST_PLAYER_MOVE_UP:
				this->setMovement(JUMPING_MOVEMENT);
				talk("jump");
				setCurrentSprite();
				jump();
				break;
			case FIRST_PLAYER_MOVE_DOWN:
				this->setMovement(DUCKING_MOVEMENT);
				setCurrentSprite();
				this->isDucking = true;
				break;
			case FIRST_PLAYER_MOVE_DOWN_LEFT:
				this->setMovement(DUCKING_MOVEMENT);
				setCurrentSprite();
				this->isDucking = true;
				break;
			case FIRST_PLAYER_MOVE_DOWN_RIGHT:
				this->setMovement(DUCKING_MOVEMENT);
				setCurrentSprite();
				this->isDucking = true;
				break;
			case FIRST_PLAYER_MOVE_UP_RIGHT:
				this->setMovement(JUMPING_RIGHT_MOVEMENT);
				talk("jump");
				setCurrentSprite();
				jumpRight();
				break;
			case FIRST_PLAYER_MOVE_UP_LEFT:
				this->setMovement(JUMPING_LEFT_MOVEMENT);
				talk("jump");
				setCurrentSprite();
				jumpLeft();
				break;
			case FIRST_PLAYER_CHANGE_ORIENTATION:
				isRightOriented = !isRightOriented;
				break;
			case FIRST_PLAYER_HI_PUNCH:
				this->setMovement(PUNCHING_HIGH_MOVEMENT);
				talk("missPunch",1);
				setCurrentSprite();
				completeMovement();
				break;
			case FIRST_PLAYER_LO_PUNCH:
				this->setMovement(PUNCHING_LOW_MOVEMENT);
				talk("missPunch",1);
				setCurrentSprite();
				completeMovement();
				break;
			case FIRST_PLAYER_DUCK_PUNCH:
				this->setMovement(PUNCHING_DUCK_MOVEMENT);
				talk("missPunch");
				setCurrentSprite();
				completeMovement();
				break;
			case FIRST_PLAYER_UPPERCUT:
				this->setMovement(UPPERCUT_MOVEMENT);
				talk("missPunch");
				setCurrentSprite();
				completeMovement();
				break;
			case FIRST_PLAYER_LOW_KICK:
				this->setMovement(LOW_KICK_MOVEMENT);
				talk("missPunch");
				setCurrentSprite();
				completeMovement();
				break;
			case FIRST_PLAYER_HIGH_KICK:
				this->setMovement(HIGH_KICK_MOVEMENT);
				talk("missKick");
				setCurrentSprite();
				completeMovement();
				break;
			case FIRST_PLAYER_DUCK_LOW_kICK:
				this->setMovement(DUCK_LOW_KICK_MOVEMENT);
				talk("missPunch");
				setCurrentSprite();
				completeMovement();
				break;
			case FIRST_PLAYER_DUCK_HIGH_kICK:
				this->setMovement(DUCK_HIGH_KICK_MOVEMENT);
				talk("missPunch");
				setCurrentSprite();
				completeMovement();
				break;
			case FIRST_PLAYER_SUPER_kICK:
				this->setMovement(SUPER_KICK_MOVEMENT);
				talk("missKick");
				setCurrentSprite();
				completeMovement();
				break;
			case FIRST_PLAYER_UNDER_KICK:
				this->setMovement(UNDER_KICK_MOVEMENT);
				talk("missKick");
				setCurrentSprite();
				completeMovement();
				break;
			case FIRST_PLAYER_AIR_LOW_kICK_R:
				this->setMovement(AIR_LOW_kICK_MOVEMENT);
				talk("jump");
				setCurrentSprite();
				airLowKickRight();
				break;
			case FIRST_PLAYER_AIR_LOW_kICK_L:
				this->setMovement(AIR_LOW_kICK_MOVEMENT);
				talk("jump");
				setCurrentSprite();
				airLowKickLeft();
				break;
			case FIRST_PLAYER_AIR_HIGH_kICK:
				this->setMovement(AIR_HIGH_kICK_MOVEMENT);
				talk("jump");
				setCurrentSprite();
				airHighKick();
				break;
			case FIRST_PLAYER_BLOCK:
				this->setMovement(BLOCK_MOVEMENT);
				setCurrentSprite();
				break;
			case FIRST_PLAYER_DUCK_BLOCK:
				this->setMovement(DUCK_BLOCK_MOVEMENT);
				setCurrentSprite();
				break;
			case FIRST_PLAYER_AIR_PUNCH:
				this->setMovement(AIR_PUNCH_MOVEMENT);
				talk("jump");
				setCurrentSprite();
				airPunch();
				break;
			case FIRST_PLAYER_AIR_PUNCH_R:
				this->setMovement(AIR_PUNCH_MOVEMENT);
				talk("jump");
				setCurrentSprite();
				airPunchRight();
				break;
			case FIRST_PLAYER_AIR_PUNCH_L:
				this->setMovement(AIR_PUNCH_MOVEMENT);
				talk("jump");
				setCurrentSprite();
				airPunchLeft();
				break;
			case FIRST_PLAYER_FIRE:
				this->fire = true;
				//this->setMovement(FIRE_MOVEMENT);
				setCurrentSprite();
				fireMovement();
				SoundManager::Instance()->playSoundByAction("fire",0);
				break;
			case FIRST_PLAYER_DUCK_FIRE:
				this->setMovement(DUCKING_MOVEMENT);
				setCurrentSprite();
				this->isDucking = true;
				this->fire = true;
				SoundManager::Instance()->playSoundByAction("fire",0);
				break;
			case SUBZERO_SWEEP:
				this->setMovement(SWEEP_MOVEMENT);
				setCurrentSprite();
				sweepMovement();
				break;
			case SPECIAL:
				this->setMovement(SPECIAL_MOVEMENT);
				setCurrentSprite();
				completeMovement();
				victim->setMovement(SPECIAL_HINT_MOVEMENT);
				SoundManager::Instance()->playSound("hit_roof", 0);
				victim->setCurrentSprite();
				victim->isSpecial_hint = true;
				break;
			case BABALITY:
				this->finishMove = new Babality();
				doFinisher();
				break;
			case FATALITY:
				this->finishMove = new Fatality();
				doFinisher();
				break;
			case HEADLESS:
				this->setMovement(HEADLESS_MOVEMENT);
				setCurrentSprite();
				completeMovement();
				break;
			case HEADLESS_BLOOD:
				this->setMovement(HEADLESS_BLOOD_MOVEMENT);
				setCurrentSprite();
				completeMovement();
				break;
			case FRIENDSHIP:
				this->finishMove = new Friendship();
				doFinisher();
				break;
			case NO_INPUT:
				this->setMovement(STANCE);
				setCurrentSprite();
				break;
			}
		} else {
			this->setMovement(STANCE);
			setCurrentSprite();
		}
	}
	//refresh Collition Shapes positions
	this->updateShapesOnStatus();

	this->smoothMovPosX();
	SDL_Delay(25);
}

void Character::clearMovementsFlags(){
	isJumping = false;
	isJumpingRight = false;
	isJumpingLeft = false;
	isWalkingRight = false;
	isWalkingLeft = false;
	isDucking = false;
	isPunchingDuck = false;
	isPunchingHigh = false;
	isPunchingLow = false;
	isPunchingAnUppercut = false;
	isKickingHigh = false;
	isKickingLow = false;
	isKickingAirHigh = false;
	isKickingAirLowRight = false;
	isKickingAirLowLeft = false;
	isBlocking = false;
	isDuckBlocking = false;
	isUnderKick = false;
	isAirPunching = false;
	isAirPunchingRight = false;
	isAirPunchingLeft = false;
	isKickingDuckHigh = false;
	isKickingDuckLow = false;
	isKickingSuper = false;
	isBeingHintStanceUp = false;
	isBeingHintStanceDown = false;
	isBeingHintFallingUnderKick = false;
	isHintFlying = false;
	isGettingUp = false;
	isHintFlyingUpper = false;
	isSubzeroSweeping = false;
	isBabality = false;
	isFatality = false;
	isHeadless = false;
	isHeadlessBlood = false;
	isFriendship = false;
	isSubzeroFiring = false;
	isVictory = false;
	isBurning = false;
	isLazy = false;
	isFinishingMove = false;
	isReptile = false;
	isFalling = false;
	isSpecial = false;
	isSpecial_hint = false;
	//this->beingPushed = false;
}

void Character::jump() {
	isJumping = true;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (this->isTouchingGround(positionY)) {
		isJumping = false;
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY = yGround;
		refreshFrames();
	}
}

void Character::airHighKick() {
	isKickingAirHigh = true;
	isJumping = false;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (this->isTouchingGround(positionY)) {
		isKickingAirHigh = false;
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY = yGround;
		refreshFrames();
	}
}

void Character::airLowKickRight() {
	isKickingAirLowRight = true;
	isJumpingRight = false;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (!this->reachedWindowRightLimit()) {
		positionX = positionX + (3 * ratioX);
	}
	if (this->isTouchingGround(positionY)) {
		isKickingAirLowRight = false;
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY = yGround;
		refreshFrames();
	}
}

void Character::airPunch() {
	isAirPunching = true;
	isJumping = false;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (this->isTouchingGround(positionY)) {
		isAirPunching = false;
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY = yGround;
		refreshFrames();
	}
}

void Character::airPunchLeft() {
	isJumpingLeft = false;
	isAirPunchingLeft = true;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (!this->reachedWindowLeftLimit()) {
		positionX = positionX - (3 * ratioX);
	}
	if (this->isTouchingGround(positionY)) {
		isAirPunchingLeft = false;
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY = yGround;
		refreshFrames();
	}
}

void Character::airPunchRight() {
	isJumpingRight = false;
	isAirPunching = false;
	isAirPunchingLeft = false;
	isJumping = false;
	isJumpingLeft = false;
	isAirPunchingRight = true;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (!this->reachedWindowRightLimit()) {
		positionX = positionX + (3 * ratioX);
	}
	if (this->isTouchingGround(positionY)) {
		isAirPunchingRight = false;
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY = yGround;
		refreshFrames();
	}
}


void Character::airLowKickLeft() {
	isKickingAirLowLeft = true;
	isJumpingLeft = false;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (!this->reachedWindowLeftLimit()) {
		positionX = positionX - (3 * ratioX);
	}
	if (this->isTouchingGround(positionY)) {
		isKickingAirLowLeft = false;
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY = yGround;
		refreshFrames();
	}
}

//Devuelve la distancia en X UL que recorre un salto diagonal.
//Solo se calcula si el personaje está en el piso.
float Character::getJumpDistance() {
	if ( !this->isTouchingGround(this->positionY) ) return -1;
	int posY = positionY;
	float jumpSpeed = jumpVel;
	float initialPosX = positionX;
	float currentPosX = positionX;

	do {
		posY = posY - jumpSpeed;
		jumpSpeed -= gravity;
		currentPosX = currentPosX + (JUMPING_X_SPEED * ratioX);

		}
	 while ( ! this->isTouchingGround(posY));

	return fabs( currentPosX - initialPosX) / ratioX ;
}

void Character::jumpRight() {
	isJumpingRight = true;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (!this->reachedWindowRightLimit()) {
		positionX = positionX + (JUMPING_X_SPEED * ratioX);
	}
	if (this->isTouchingGround(positionY)) {
		isJumpingRight = false;
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY = yGround;
		refreshFrames();
	}
}

void Character::flyFalling() {

	MKGame::Instance()->setShaking(true);
	isHintFlying = true;
	isJumpingRight = false;
	isJumping = false;
	isJumpingLeft = false;
	positionY = positionY - jumpVelFalling;
	jumpVelFalling -= gravity;
	if (!this->reachedWindowRightLimit() && !this->reachedWindowLeftLimit()) {
		if (isRightOriented){
			positionX = positionX - (6 * ratioX);
		} else {
			positionX = positionX + (6 * ratioX);
		}
	}
	if (this->isTouchingGround(positionY)) {
		isHintFlying = false;
		jumpVelFalling = 40.0f;
		this->setMovement(GET_UP_MOVEMENT);
		this->positionY = yGround;
		refreshFrames();
	}
}

void Character::flyFallingUpper() {
	MKGame::Instance()->setShaking(true);
	isHintFlyingUpper = true;
	isJumpingRight = false;
	isJumping = false;
	isJumpingLeft = false;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (!this->reachedWindowRightLimit() && !this->reachedWindowLeftLimit()) {
		if (isRightOriented) {
			positionX = positionX - (4 * ratioX);
		} else {
			positionX = positionX + (4 * ratioX);

		}
	}
	if (this->isTouchingGround(positionY)) {
		isHintFlyingUpper = false;
		jumpVel = 60.0f;
		this->setMovement(GET_UP_MOVEMENT);
		this->setCurrentSprite();
		completeMovement();
		this->positionY = yGround;
		refreshFrames();
	}
}

void Character::jumpLeft() {
	isJumpingLeft = true;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (!this->reachedWindowLeftLimit()) {
		positionX = positionX - (JUMPING_X_SPEED * ratioX);
	}
	if (this->isTouchingGround(positionY)) {
		isJumpingLeft = false;
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY = yGround;
		refreshFrames();
	}
}


bool Character::isTouchingGround(float positionY) {
	if (positionY >= this->yGround) {
		return true;
	}
	return false;
}

void Character::refreshFrames(){

	 for (std::map<string,Sprite*>::iterator it=this->characterSprites.begin(); it!=this->characterSprites.end(); ++it)
		 it->second->refresh();

}

void Character::walkRight() {
	isWalkingRight = true;
	if (!this->reachedWindowRightLimit()) {
		positionX = positionX + FRONTAL_LAYER_SPEED * ratioX;
	}


}

void Character::sweepMovement() {
	isSubzeroSweeping = true;

	if (isRightOriented && !this->reachedWindowRightLimit()){
		positionX = positionX + (SWEEP_X_SPEED * ratioX);
	}
	else if (!isRightOriented && !this->reachedWindowLeftLimit()){
		positionX = positionX - (SWEEP_X_SPEED * ratioX);

	}else {
		isSubzeroSweeping = false;
	}
}

void Character::fireMovement() {

}

void Character::walkLeft() {
	isWalkingLeft = true;
	if (!this->reachedWindowLeftLimit()){
		positionX = positionX - FRONTAL_LAYER_SPEED * ratioX;
	}

}


void Character::setMovement(std::string movement) {
	//this->previousMovement = this->movement;
	this->movement = movement;
	this->setDOMovement(movement);
}

std::string Character::getMovement() {
	return this->movement;
}

void Character::clean() {
	delete this->pParams;
	delete this->altColor;
}


int Character::getWidth() {
	return this->width;
}

int Character::getPosX() {
	return this->positionX;
}

float Character::getPosXUL(){
	return this->positionX / this->ratioX;
}

float Character::getYGround() {
	return this->yGround;
}

string Character::getName() {
	return this->name;
}

std::string Character::getPlayerNumber() {
	return this->playerNumber;
}

void Character::setPlayerNumber(std::string playerNumber) {
	this->playerNumber = playerNumber;
}


bool Character::isMovingRight(){
	if (this->isJumpingRight || this->isWalkingRight || this->isAirPunchingRight || this->isKickingAirLowRight
			|| this->isHintFlying || this->isHintFlyingUpper || this->beingPushed) return true;
	return false;
}

bool Character::isMovingLeft(){
	if (this->isJumpingLeft || this->isWalkingLeft || this->isAirPunchingLeft || this->isKickingAirLowLeft
			|| this->isHintFlying || this->isHintFlyingUpper || this->beingPushed) return true;
	return false;
}

void Character::hitWithRoof(){

	this->setEnergy(this->getEnergy() - 0.01f);
	isSpecial_hint = true;
	positionY = positionY - jumpVelRoof;
	jumpVelRoof -= gravity;
	cout << positionY << endl;
	if (positionY > 120 && positionY < 130) SoundManager::Instance()->playSound("fireHit3", 0);
	if (this->isTouchingGround(positionY)) {
		isSpecial_hint = false;
		jumpVelRoof = 80.0f;
		this->setMovement(STANCE);
		this->positionY = yGround;
	}
}

void Character::completeMovement(){
	incrementCounter(getMovement());
	setMoveFlag(true);
	int moveCounter = movesCounter.at(getMovement());
	int spriteAmount = currentSprite->getFramesAmount();
	if (moveCounter == spriteAmount) {
		if (!isLazy) setMoveFlag(false);
		if (isTouchingGround(positionY)){
			if (!isLazy) clearMovementsFlags();
		}
		resetCounter(getMovement());
		if (!isLazy) this->movement="";
	}
}

//void Character::completeMovemenAndChangeToVictory(){
//	this->completeMovementAndChangeVictory = true;
//	incrementCounter(getMovement());
//	setMoveFlag(true);
//
//	int moveCounter = movesCounter.at(getMovement());
//	int spriteAmount = currentSprite->getFramesAmount();
//	if (moveCounter == spriteAmount) {
//		setMoveFlag(false);
//		if (isTouchingGround(positionY)) {
//				clearMovementsFlags();
//		}
//		resetCounter(getMovement());
//		this->completeMovementAndChangeVictory = false;
//		this->setMovement(VICTORY_MOVEMENT);
//		this->setCurrentSprite();
//		this->isVictory = true;
//	}
//}

void sleepSafe(int limit);

void Character::doFinisher() {

	isFinishingMove = true;

	Character* victim = getVictim();

	//FATALITY
	if (finishMove->getID() == 0) {

		//Scorpion hace la fatality
		if (this->name == "scorpion") {

			if (victim->isLazy) {
				this->finishMove->onPreFinish(this->name);

			} else if (victim->isBurning) {
				this->finishMove->onFinish(this->name);

			}
			Sprite* victimCurrentSprite = victim->currentSprite;
			int currentFrame = victimCurrentSprite->getCurrentFrame();
			int framesAmount = victimCurrentSprite->getFramesAmount();
			if (victim->isBurning && victimCurrentSprite->isLooped && currentFrame == framesAmount - 1) {
				sleepSafe(90000000);
				this->finishMove->onPostFinish(this->name);
				MKGame::Instance()->showFatality = true;
			}

			//Subzero hace la fatality
		} else {

			int distance = std::abs ( (this->getPosX() - victim->getPosX()) );
			cout << "DISTANCE: " << distance << endl;
			if (distance <= 140) {
				if (victim->isLazy && this->getMovement() != REPTILE_MOVEMENT) {
					this->finishMove->onPreFinish(this->name);

				}
				if (victim->isLazy
						&& this->currentSprite->getCurrentFrame()
								== this->currentSprite->getFramesAmount() - 1) {
					this->finishMove->onFinish(this->name);

				} else if (victim->isHeadlessBlood
						&& victim->currentSprite->isLooped
						&& victim->currentSprite->getCurrentFrame() == victim->currentSprite->getFramesAmount() - 1) {
					this->finishMove->onPostFinish(this->name);
					MKGame::Instance()->showFatality = true;
				}
			} else {
				clearMovementsFlags();
				victim->isLazy = true;
			}

		}
	}


	//BABALITY
	if (finishMove->getID() == 1) {

		if (victim->isLazy) {
			this->finishMove->onPreFinish(this->name);
		}

		Sprite* victimCurrentSprite = victim->currentSprite;
		int currentFrame = victimCurrentSprite->getCurrentFrame();
		int framesAmount = victimCurrentSprite->getFramesAmount();

		if ((this->getMovement() == "stance" || this->getMovement() == "") && victim->isBabality && currentFrame == framesAmount - 1) {
			this->finishMove->onFinish(this->name);

		}

		else if(this->isVictory && currentFrame == framesAmount - 1){
			sleepSafe(100000000);
			this->finishMove->onPostFinish(this->name);
			MKGame::Instance()->showBabality = true;

		}

	}

	//FRIENDSHIP
	else if (finishMove->getID() == 2){


		Sprite* winnerCurrentSprite = this->currentSprite;
		int currentFrame = winnerCurrentSprite->getCurrentFrame();
		int framesAmount = winnerCurrentSprite->getFramesAmount();

		if (victim->isLazy && !this->isFriendship) {
			this->finishMove->onPreFinish(this->name);
		}

		else if (this->isFriendship && victim->isLazy) {
			this->finishMove->onFinish(this->name);

		}

		if (this->isFriendship && currentFrame == framesAmount - 1) {
			sleepSafe(90000000);
			this->finishMove->onPostFinish(this->name);
			this->isFinishingMove = false;
			MKGame::Instance()->showFriendship = true;
		}


	}

}


void Character::incrementCounter(string key){
	int value = 1;
	int containKey = movesCounter.count(key);
	if (containKey == 1){
		value = movesCounter.at(key);
		resetCounter(key);
		value++;
	}
	movesCounter.insert({key, value});
}


void Character::resetCounter(string key){
	movesCounter.erase(key);
}

Character::~Character() {
	 delete this->pParams;
	for (std::map<string,Sprite*>::iterator it=this->characterSprites.begin(); it!=this->characterSprites.end(); ++it){
		 delete(it->second);
	 }
	 this->characterSprites.clear();

	 delete this->altColor;


}


bool fileExists(string s)
{
	ifstream file(s.c_str(), std::ifstream::binary);

	if (file.good()) {
		return true;
	}else{
		FILE_LOG(logERROR) << "File not found: " << s;
		return false;
	}
}

bool validateSpritesForSelectedCharacter(string characterPath) {
	if ( (!fileExists(characterPath+WALK_SPRITE)) || (!fileExists(characterPath+STANCE_SPRITE)) ||
			(!fileExists(characterPath+DIAGONAL_JUMP_SPRITE)) ||
			(!fileExists(characterPath+DUCK_SPRITE)) ||
			(!fileExists(characterPath+JUMP_SPRITE)) ) {
		return false;
	}
	return true;
}


AlternativeColor* Character::getAlternativeColor(){
	return this->altColor;

}

void Character::setAlternativeColor(AlternativeColor* altColor) {
	this->altColor = altColor;
}

bool Character::getIsAlternativePlayer() {
	return this->isAltPlayer;
}

void Character::setIsAlternativePlayer(bool isAltPlayer) {
	this->isAltPlayer = isAltPlayer;
}


void Character::setCurrentSprite(){
	if (this->getMovement() == WALKING_RIGHT_MOVEMENT){
			currentSprite = this->characterSprites[this->name+this->playerNumber+WALK_SUFFIX];

		} else if (this->getMovement() == WALKING_LEFT_MOVEMENT){
			currentSprite = this->characterSprites[this->name+this->playerNumber+WALK_SUFFIX];

		} else if (this->getMovement() == JUMPING_MOVEMENT){
			currentSprite = this->characterSprites[this->name+this->playerNumber+JUMP_SUFFIX];

		} else if (this->getMovement() == STANCE){
			currentSprite = this->characterSprites[this->name+this->playerNumber+STANCE_SUFFIX];

		} else if (this->getMovement() == JUMPING_RIGHT_MOVEMENT ||
				this->getMovement() == JUMPING_LEFT_MOVEMENT){
			currentSprite = this->characterSprites[this->name+this->playerNumber+JUMP_DIAGONAL_SUFFIX];

		} else if (this->getMovement() == DUCKING_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+DUCK_SUFFIX];

		} else if (this->getMovement() == PUNCHING_HIGH_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+HI_PUNCH_SUFFIX];

		} else if (this->getMovement() == PUNCHING_LOW_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+LO_PUNCH_SUFFIX];

		} else if (this->getMovement() == PUNCHING_DUCK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+DUCK_PUNCH_SUFFIX];

		} else if (this->getMovement() == UPPERCUT_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+UPPERCUT_SUFFIX];

		} else if (this->getMovement() == LOW_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+LOW_KICK_SUFFIX];

		} else if (this->getMovement() == HIGH_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+HIGH_KICK_SUFFIX];

		} else if (this->getMovement() == DUCK_HIGH_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+DUCK_HIGH_KICK_SUFFIX];

		} else if (this->getMovement() == DUCK_LOW_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+DUCK_LOW_KICK_SUFFIX];

		} else if (this->getMovement() == SUPER_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+SUPER_KICK_SUFFIX];

		} else if (this->getMovement() == AIR_HIGH_kICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+AIR_HIGH_kICK_SUFFIX];

		} else if (this->getMovement() == AIR_LOW_kICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+AIR_LOW_kICK_SUFFIX];

		} else if (this->getMovement() == DUCK_BLOCK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+DUCK_BLOCK_SUFFIX];

		} else if (this->getMovement() == BLOCK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+BLOCK_SUFFIX];

		} else if (this->getMovement() == UNDER_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+UNDER_KICK_SUFFIX];

		} else if (this->getMovement() == AIR_PUNCH_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+AIR_PUNCH_SUFFIX];

		} else if (this->getMovement() == BEING_HINT_STANCE_UP_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+BEING_HINT_STANCE_UP_SUFFIX];

		} else if (this->getMovement() == BEING_HINT_STANCE_DOWN_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+BEING_HINT_STANCE_DOWN_SUFFIX];

		} else if (this->getMovement() == BEING_HINT_FALLING_UNDER_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+BEING_HINT_FALLING_UNDER_KICK_SUFFIX];

		} else if (this->getMovement() == HINT_FLYING_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+HINT_FLYING_SUFFIX];

		} else if (this->getMovement() == HINT_FLYING_UPPER_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+HINT_FLYING_SUFFIX];

		} else if (this->getMovement() == GET_UP_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+GET_UP_SUFFIX];

		} else if (this->getMovement() == SWEEP_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+SWEEP_SUFFIX];

		} else if (this->getMovement() == FIRE_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+this->playerNumber+FIRE_SUFFIX];

		} else if (this->getMovement() == BABALITY_MOVEMENT) {
			currentSprite = this->characterSprites[this->name + this->playerNumber+ BABALITY_SUFFIX];

		} else if (this->getMovement() == REPTILE_MOVEMENT) {
			currentSprite = this->characterSprites[this->name + this->playerNumber+ REPTILE_SUFFIX];
		}

		else if (this->getMovement() == HEADLESS_MOVEMENT) {
			currentSprite = this->characterSprites[this->name + this->playerNumber+ HEADLESS_SUFFIX];
		}

		else if (this->getMovement() == HEADLESS_BLOOD_MOVEMENT) {
			currentSprite = this->characterSprites[this->name + this->playerNumber+ HEADLESS_BLOOD_SUFFIX];
		}

		else if (this->getMovement() == FRIENDSHIP_MOVEMENT) {
			currentSprite = this->characterSprites[this->name + this->playerNumber+ FRIENDSHIP_SUFFIX];
		}

		else if (this->getMovement() == VICTORY_MOVEMENT) {
			currentSprite = this->characterSprites[this->name + this->playerNumber+ VICTORY_SUFFIX];
		}

		else if (this->getMovement() == LAZY_MOVEMENT) {
			currentSprite = this->characterSprites[this->name + this->playerNumber+ LAZY_SUFFIX];
		}

		else if (this->getMovement() == BURNING_MOVEMENT) {
			currentSprite = this->characterSprites[this->name + this->playerNumber+ BURNING_SUFFIX];
			isLazy = false;
		}

		else if (this->getMovement() == FALLING_MOVEMENT) {
			currentSprite = this->characterSprites[this->name + this->playerNumber+ FALLING_SUFFIX];
		}
		else if (this->getMovement() == SPECIAL_MOVEMENT) {
			currentSprite = this->characterSprites[this->name + this->playerNumber+ SPECIAL_SUFFIX];
		}
		else if (this->getMovement() == SPECIAL_HINT_MOVEMENT) {
			currentSprite = this->characterSprites[this->name + this->playerNumber+ SPECIAL_HINT_SUFFIX];
		}
		else{
			//TODO: review
		}
}

void Character::setMoveFlag(bool trueOrFalse){

	if (this->getMovement() == PUNCHING_HIGH_MOVEMENT) {
		isPunchingHigh = trueOrFalse;

	} else if (this->getMovement() == PUNCHING_LOW_MOVEMENT) {
		isPunchingLow = trueOrFalse;

	} else if (this->getMovement() == PUNCHING_DUCK_MOVEMENT) {
		isPunchingDuck = trueOrFalse;
	} else if (this->getMovement() == UPPERCUT_MOVEMENT) {
		isPunchingAnUppercut = trueOrFalse;

	} else if (this->getMovement() == LOW_KICK_MOVEMENT) {
		isKickingLow = trueOrFalse;

	} else if (this->getMovement() == HIGH_KICK_MOVEMENT) {
		isKickingHigh = trueOrFalse;

	} else if (this->getMovement() == DUCK_HIGH_KICK_MOVEMENT) {
		isKickingDuckHigh = trueOrFalse;

	} else if (this->getMovement() == DUCK_LOW_KICK_MOVEMENT) {
		isKickingDuckLow = trueOrFalse;

	} else if (this->getMovement() == SUPER_KICK_MOVEMENT) {
		isKickingSuper = trueOrFalse;

	} else if (this->getMovement() == AIR_HIGH_kICK_MOVEMENT) {
		isKickingAirHigh = trueOrFalse;

	} else if (this->getMovement() == UNDER_KICK_MOVEMENT) {
		isUnderKick = trueOrFalse;

	} else if (this->getMovement() == BEING_HINT_STANCE_UP_MOVEMENT) {
		isBeingHintStanceUp = trueOrFalse;

	} else if (this->getMovement() == BEING_HINT_STANCE_DOWN_MOVEMENT) {
		isBeingHintStanceDown = trueOrFalse;

	} else if (this->getMovement() == BEING_HINT_FALLING_UNDER_KICK_MOVEMENT) {
		isBeingHintFallingUnderKick = trueOrFalse;

	} else if (this->getMovement() == HINT_FLYING_MOVEMENT) {
		isHintFlying = trueOrFalse;

	} else if (this->getMovement() == HINT_FLYING_UPPER_MOVEMENT) {
		isHintFlyingUpper = trueOrFalse;

	} else if (this->getMovement() == GET_UP_MOVEMENT) {
		isGettingUp = trueOrFalse;

	} else if (this->getMovement() == SWEEP_MOVEMENT) {
		isSubzeroSweeping = trueOrFalse;

	} else if (this->getMovement() == FIRE_MOVEMENT) {
		isSubzeroSweeping = trueOrFalse;

	} else if (this->getMovement() == BABALITY_MOVEMENT) {
		isBabality = trueOrFalse;
	}
	else if (this->getMovement() == REPTILE_MOVEMENT) {
		isReptile = trueOrFalse;
	}
	else if (this->getMovement() == HEADLESS_MOVEMENT) {
		isHeadless = trueOrFalse;
	}
	else if (this->getMovement() == HEADLESS_BLOOD_MOVEMENT) {
		isHeadlessBlood = trueOrFalse;
	}
	else if (this->getMovement() == FRIENDSHIP_MOVEMENT) {
		isFriendship = trueOrFalse;
	}
	else if (this->getMovement() == VICTORY_MOVEMENT) {
		isVictory = trueOrFalse;
	}
	else if (this->getMovement() == LAZY_MOVEMENT) {
		isLazy = trueOrFalse;
	}
	else if (this->getMovement() == BURNING_MOVEMENT) {
		isBurning = trueOrFalse;
	}
	else if (this->getMovement() == FALLING_MOVEMENT) {
		isFalling = trueOrFalse;
	}
	else if (this->getMovement() == SPECIAL_MOVEMENT) {
		isSpecial = trueOrFalse;
	}
	else if (this->getMovement() == SPECIAL_HINT_MOVEMENT) {
		isSpecial_hint = trueOrFalse;
	}
	else {
		//TODO: review
	}

}

bool someKickInputCommand(InputCommand inputCommand) {
	return ((inputCommand == FIRST_PLAYER_LOW_KICK) || (inputCommand == FIRST_PLAYER_HIGH_KICK) ||
			(inputCommand == FIRST_PLAYER_AIR_HIGH_kICK) || (inputCommand == FIRST_PLAYER_AIR_LOW_kICK_R)
			|| (inputCommand == FIRST_PLAYER_AIR_LOW_kICK_L));
}

bool somePunchInputCommand(InputCommand inputCommand) {
	return ((inputCommand == FIRST_PLAYER_LO_PUNCH) || (inputCommand == FIRST_PLAYER_HI_PUNCH) ||
			(inputCommand == FIRST_PLAYER_AIR_PUNCH_L) || (inputCommand == FIRST_PLAYER_AIR_PUNCH_R)
			|| (inputCommand == FIRST_PLAYER_AIR_PUNCH));
}

void Character::setIsRightOriented(bool isRightOriented) {
	this->isRightOriented = isRightOriented;
}


void Character::getCNextPosition(float* nextPositionX, float* nextPositionY){

		if ((!this->reachedWindowRightLimit()) && (this->isWalkingRight)){ //si no llego al limite de pantalla y esta caminando para derecha
			*nextPositionX = positionX + FRONTAL_LAYER_SPEED * ratioX;
		}else if ((!this->reachedWindowLeftLimit()) && (this->isWalkingLeft)){
			*nextPositionX = positionX - FRONTAL_LAYER_SPEED * ratioX;
		}else if (this->isJumping){
			*nextPositionY = positionY - jumpVel;
			if (this->isTouchingGround(*nextPositionY)) {
				*nextPositionY = yGround;
			}
		}else if (this->isJumpingRight){
			*nextPositionY = this->positionY - jumpVel;
			if (!this->reachedWindowRightLimit()) {
				*nextPositionX = positionX + (FRONTAL_LAYER_SPEED * ratioX);
			}
			if (this->isTouchingGround(*nextPositionY)) {
				*nextPositionY = yGround;

			}
		}else if (this->isJumpingLeft){
			*nextPositionY = positionY - jumpVel;
			if (!this->reachedWindowLeftLimit()) {
				*nextPositionX = positionX - (FRONTAL_LAYER_SPEED * ratioX);
			}
			if (this->isTouchingGround(*nextPositionY)) {
				*nextPositionY = yGround;
			}
		}
}
void Character::updateShapesOnStatus(){


//		void updateCShapesPosition(float X, float Y, float W, float H, bool rightOriented, bool secShapeTop, float secShapeW, float secShapeH);

	float charWidht = this->getWidth()*ratioX;
	float charHeight = (this->height)*ratioY;
	float centerX = this->getPositionX() + this->width * ratioX /2;
	float centerY = this->getPositionY() + this->height * ratioY /2;

	if (isJumping) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/4), charWidht/3, charHeight/2);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/4) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/2;
	}else if (isJumpingRight) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/4), charWidht/3, charHeight/2);
		posXBox = centerX - widthBox/2;
		posYBox = centerY - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/2;
	}else if (isJumpingLeft) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/4), charWidht/3, charHeight/2);
		posXBox = centerX - widthBox/2;
		posYBox = centerY - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/2;
	}else if (isKickingHigh){
		this->updateCShapesPosition(centerX, (centerY  + charHeight/8), charWidht/3, charHeight*3/4, this->isRightOriented, false, (charWidht)/4, (charHeight)/3 );
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/8) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight*3/4;
		float secX,secY;
		widthBox2 = charWidht/4;
		heightBox2 = charHeight/3;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (false){secY=(centerY+charHeight/8)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/8)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isKickingLow) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/8), charWidht/3, charHeight*3/4, this->isRightOriented, false, (charWidht)/6, charHeight *2/ 5);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/8) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight*3/4;
		float secX,secY;
		widthBox2 = charWidht/6;
		heightBox2 = charHeight*2/5;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (false){secY=(centerY+charHeight/8)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/8)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isKickingDuckHigh) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/3), charWidht/3, (charHeight)/3, this->isRightOriented, false, (charWidht)/8, (charHeight)/3);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/3) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/3;
		float secX,secY;
		widthBox2 = charWidht/8;
		heightBox2 = charHeight/3;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (false){secY=(centerY+charHeight/3)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/3)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isKickingDuckLow) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/3), charWidht/3, (charHeight)/3, this->isRightOriented, true, (charWidht)/8, (charHeight)/3);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/3) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/3;
		float secX,secY;
		widthBox2 = charWidht/8;
		heightBox2 = charHeight/3;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (true){secY=(centerY+charHeight/3)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/3)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isKickingSuper) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/8), charWidht/3, charHeight*3/4, this->isRightOriented, true, (charWidht)/4, (charHeight)/3 );
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/8) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight*3/4;
		float secX,secY;
		widthBox2 = charWidht/4;
		heightBox2 = charHeight/3;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (false){secY=(centerY+charHeight/8)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/8)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isUnderKick){
		this->updateCShapesPosition(centerX, (centerY  + charHeight/3) , charWidht/3, (charHeight)/3, this->isRightOriented, false, (charWidht)/3, (charHeight)/3);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/3) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/3;
		float secX,secY;
		widthBox2 = charWidht/3;
		heightBox2 = charHeight/3;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (false){secY=(centerY+charHeight/3)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/3)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isPunchingAnUppercut) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/8), (charWidht)/3, (charHeight)*3/4, this->isRightOriented, false, (charWidht)/9, charHeight/3);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/8) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight*3/4;
		float secX,secY;
		widthBox2 = charWidht/9;
		heightBox2 = charHeight/3;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (false){secY=(centerY+charHeight/8)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/8)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isPunchingLow) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/8), charWidht/3, charHeight*3/4, this->isRightOriented, false, (charWidht)/14, charHeight /3);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/8) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight*3/4;
		float secX,secY;
		widthBox2 = charWidht/14;
		heightBox2 = charHeight/3;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (false){secY=(centerY+charHeight/8)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/8)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isPunchingDuck) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/3), charWidht/3, (charHeight)/3, this->isRightOriented, false, charWidht/8, charHeight / 3);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/3) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/3;
		float secX,secY;
		widthBox2 = charWidht/8;
		heightBox2 = charHeight/3;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (false){secY=(centerY+charHeight/3)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/3)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isPunchingHigh) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/8), charWidht/3, charHeight*3/4, this->isRightOriented, false, charWidht/14, charHeight/6);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/8) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight*3/4;
		float secX,secY;
		widthBox2 = charWidht/14;
		heightBox2 = charHeight/6;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (false){secY=(centerY+charHeight/8)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/8)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isDuckBlocking) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/3), (charWidht)/3, (charHeight));
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/3) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight;
	}else if (isDucking) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/3), charWidht/3, charHeight/3);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/3) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/3;
	}else if (isWalkingRight) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/8),charWidht/3,charHeight*3/4);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/8) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight*3/4;
	}else if (isWalkingLeft) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/8),charWidht/3,charHeight*3/4);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/8) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight*3/4;
	}else if (isBlocking) {
		this->updateCShapesPosition(centerX, (centerY  + charHeight/8), charWidht/3,charHeight*3/4);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/8) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight*3/4;
	}else if (isKickingAirHigh){
		this->updateCShapesPosition(centerX, (centerY), charWidht/3, charHeight/2, this->isRightOriented, false, charWidht/4, charHeight/6);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/2;
		float secX,secY;
		widthBox2 = charWidht/4;
		heightBox2 = charHeight/6;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (false){secY=(centerY+charHeight/8)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/8)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isKickingAirLowRight){
		this->updateCShapesPosition(centerX, (centerY + charHeight/4), charWidht/3, charHeight/2, this->isRightOriented, true, charWidht/4, charHeight/6);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY + charHeight/4) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/2;
		float secX,secY;
		widthBox2 = charWidht/4;
		heightBox2 = charHeight/6;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (true){secY=(centerY+charHeight/4)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/4)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isKickingAirLowLeft){
		this->updateCShapesPosition(centerX, (centerY + charHeight/4), charWidht/3, charHeight/2, this->isRightOriented, true, charWidht/4, charHeight/6);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY + charHeight/4) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/2;
		float secX,secY;
		widthBox2 = charWidht/4;
		heightBox2 = charHeight/6;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (true){secY=(centerY+charHeight/4)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/4)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isAirPunchingRight){
		this->updateCShapesPosition(centerX, (centerY + charHeight/4), charWidht/3, charHeight/2, this->isRightOriented, true, charWidht/4, charHeight/6);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY + charHeight/4) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/2;
		float secX,secY;
		widthBox2 = charWidht/4;
		heightBox2 = charHeight/6;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (true){secY=(centerY+charHeight/4)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/4)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isAirPunching){
		this->updateCShapesPosition(centerX, (centerY + charHeight/4), charWidht/3, charHeight/2, this->isRightOriented, true, charWidht/4, charHeight/6);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY + charHeight/4) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/2;
		float secX,secY;
		widthBox2 = charWidht/4;
		heightBox2 = charHeight/6;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (true){secY=(centerY+charHeight/4)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/4)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	}else if (isAirPunchingLeft){
		this->updateCShapesPosition(centerX, (centerY + charHeight/4), charWidht/3, charHeight/2, this->isRightOriented, true, charWidht/4, charHeight/6);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY + charHeight/4) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight/2;
		float secX,secY;
		widthBox2 = charWidht/4;
		heightBox2 = charHeight/6;
		if (this->isRightOriented){secX =centerX+(widthBox/2)+(widthBox2/2);}else{secX=centerX-(widthBox/2)-(widthBox2/2);}
		if (true){secY=(centerY+charHeight/4)+(heightBox/2)-(heightBox2/2);}else{secY=(centerY+charHeight/4)-(heightBox/2)+(heightBox2/2);}
		posXBox2 = secX - widthBox2/2;
		posYBox2 = secY - heightBox2/2;
	} else if (isSubzeroSweeping) {
		this->updateCShapesPosition(centerX, (centerY + charHeight / 3), charWidht / 1.8, charHeight / 4);
		posXBox = centerX - widthBox / 2;
		posYBox = (centerY + charHeight / 3) - heightBox / 2;
		widthBox = charWidht / 1.8;
		heightBox = charHeight / 4;
	}else{
		this->updateCShapesPosition(centerX, (centerY  + charHeight/8), charWidht/3,charHeight*3/4);
		posXBox = centerX - widthBox/2;
		posYBox = (centerY  + charHeight/8) - heightBox/2;
		widthBox = charWidht/3;
		heightBox = charHeight*3/4;
	}
}

bool Character::getIsRightOriented(){
	return this->isRightOriented;
}

Character* Character::getCopyInstance() {
	LoaderParams* characterParams = new LoaderParams(positionX, positionY, width, height, zIndex, ratioX, ratioY, name);
	AlternativeColor* copyAltColor = new AlternativeColor(altColor->getInitialH(), altColor->getFinalH(), altColor->getShift());
	Character* copyOfCharacter = new Character(characterParams);
	copyOfCharacter->setAlternativeColor(copyAltColor);
	copyOfCharacter->setPlayerNumber(playerNumber);
	return copyOfCharacter;
}

int Character::getHeight(){
	return this->height;
}

void Character::setFixPosXStandingCharacter( int orientation) {
	this->orientationPosXFix = orientation;
}

void Character::fixPosXStandingCharacter() {
	positionX = positionX + FRONTAL_LAYER_SPEED * ratioX * this->orientationPosXFix *-1;
}

bool Character::getIsKickingAirLowRight() {
	return this->isKickingAirLowRight;
}
bool Character::getIsKickingAirLowLeft() {
	return this->isKickingAirLowLeft;
}
bool Character::getIsAirPunchingRight() {
	return this->isAirPunchingRight;
}
bool Character::getIsAirPunchingLeft() {
	return this->isAirPunchingLeft;
}

void Character::smoothMovPosX() {
	float offset = this->getPositionX() + this->smoothOrientation*15;
	if (this->smoothOffsetX > 0) {
	//	if( !this->reachedWindowLeftLimit() && !this->reachedWindowRightLimit()){
			this->setPositionX(offset);
			this->smoothOffsetX-=15;
	//	}
	}
}

float Character::getPosXBoxUL() {
	return this->posXBox / this->ratioX;
}

float Character::getPosXBox2UL() {
	return this->posXBox2 / this->ratioX;
}

float Character::getWidthBoxUL() {
	return this->widthBox / this->ratioX;
}

float Character::getWidthBox2UL() {
	return this->widthBox2 / this->ratioX;
}

void Character::talk(std::string action, int repetitions) {
	if (this->movement != this->previousMovement || action == "toasty") {
		SoundManager::Instance()->playSoundByAction(action,repetitions);
	}
}

Character* Character::getVictim(){

	Character* character = GameGUI::getInstance()->getCharacters()[0];
	if (character->name == this->name){
		return GameGUI::getInstance()->getCharacters()[1];
	}
	return character;

}
