/*
 * Character.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Character.h"
#include "../headers/TextureManager.h"
#include "../headers/MKGame.h"
#include <SDL.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

float gravity = 14.0f;
float jumpVel = 60.0f;

std::map<std::string,int> Character::movesCounter;

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
}



bool Character::load(SDL_Renderer* render) {
	this->renderer = render;
	std::string characterPath = this->imagePath+this->name;
	bool isValid = validateSpritesForSelectedCharacter(characterPath);
	if (!isValid) {
		characterPath = this->imagePath + DEFAULT_PATH_SPRITE_CONTAINER;
	}

	Sprite* spriteWalk = new Sprite(this->name+WALK_SUFFIX, characterPath+WALK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 8);
	Sprite* spriteStance = new Sprite(this->name+STANCE_SUFFIX, characterPath+STANCE_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 9);
	Sprite* spriteJump = new Sprite(this->name+JUMP_SUFFIX, characterPath+JUMP_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1);
	Sprite* spriteJumpDiagonal = new Sprite(this->name+JUMP_DIAGONAL_SUFFIX, characterPath+DIAGONAL_JUMP_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 9);
	Sprite* spriteDuck = new Sprite(this->name+DUCK_SUFFIX, characterPath+DUCK_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 3);
	Sprite* spriteHighPunch = new Sprite(this->name+HI_PUNCH_SUFFIX, characterPath+HIPUNCH_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 7);
	Sprite* spriteLowPunch = new Sprite(this->name+LO_PUNCH_SUFFIX, characterPath+LOPUNCH_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 6);
	Sprite* spriteDuckPunch = new Sprite(this->name+DUCK_PUNCH_SUFFIX, characterPath+DUCKPUNCH_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 2);
	Sprite* spriteUpperCut = new Sprite(this->name+UPPERCUT_SUFFIX, characterPath+UPPERCUT_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT +30, 5);
	Sprite* spriteLowKick = new Sprite(this->name+LOW_KICK_SUFFIX, characterPath+LOW_KICK_SPRITE,
			renderer, 200, 170, 6);
	Sprite* spriteHighKick = new Sprite(this->name+HIGH_KICK_SUFFIX, characterPath+HIGH_KICK_SPRITE,
			renderer, 200, 170, 6);
	Sprite* spriteDuckLowKick = new Sprite(this->name+DUCK_LOW_KICK_SUFFIX, characterPath+DUCK_LOW_KICK_SPRITE,
			renderer, 200, 170, 3);
	Sprite* spriteDuckHighKick = new Sprite(this->name+DUCK_HIGH_KICK_SUFFIX, characterPath+DUCK_HIGH_KICK_SPRITE,
			renderer, 200, 170, 4);
	Sprite* spriteSuperKick = new Sprite(this->name+SUPER_KICK_SUFFIX, characterPath+SUPER_KICK_SPRITE,
			renderer, 200, 170, 8);
	//TODO: Files path must be generated depending on the character
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+WALK_SUFFIX, spriteWalk));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+STANCE_SUFFIX, spriteStance));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+JUMP_SUFFIX, spriteJump));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+JUMP_DIAGONAL_SUFFIX, spriteJumpDiagonal));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+DUCK_SUFFIX, spriteDuck));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+HI_PUNCH_SUFFIX, spriteHighPunch));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+LO_PUNCH_SUFFIX, spriteLowPunch));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+DUCK_PUNCH_SUFFIX, spriteDuckPunch));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+UPPERCUT_SUFFIX, spriteUpperCut));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+LOW_KICK_SUFFIX, spriteLowKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+HIGH_KICK_SUFFIX, spriteHighKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+DUCK_LOW_KICK_SUFFIX, spriteDuckLowKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+DUCK_HIGH_KICK_SUFFIX, spriteDuckHighKick));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+SUPER_KICK_SUFFIX, spriteSuperKick));
	return true;
}

void Character::render(SDL_Renderer* render) {
}


void Character::draw() {

	int currentFrame;

	if(this->isDucking) {
		currentFrame = currentSprite->getNextFrameWithLimit();
	} else {
		if (shouldMoveForward()) {
			currentFrame = currentSprite->getNextForwardingFrame();
		} else {
			currentFrame = currentSprite->getNextBackwardingFrame();
		}
	}
	TextureManager::Instance()->drawFrame(currentSprite->getSpriteId(),
			(int) positionX, (int) positionY, width * ratioX, height * ratioY,
			1, currentFrame,
			renderer, currentSprite->getSpriteWidth(), currentSprite->getSpriteHeight(), (!isRightOriented)? SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
}

bool Character::shouldMoveForward() {
	if ( (this->isRightOriented && (isJumpingRight || isWalkingRight)) ||
			(!this->isRightOriented && (isJumpingLeft || isWalkingLeft))  ) {
		return true;
	} else {
		return false;
	}
}

bool Character::reachedWindowLeftLimit(){
	if (this->getPosXUL() < WINDOW_MARGIN -1) return true;
	return false;
}

bool Character::reachedWindowRightLimit(){
	float windowWidth = GameGUI::getInstance()->getWindow()->getWidth();
	if ( ( windowWidth - this->getPosXUL() - this->width ) < WINDOW_MARGIN -1) return true;
	return false;
}

void Character::update() {

	InputCommand playerCommand = InputControl::Instance()->getFirstPlayerMove();
	//InputCommand optionCommand = keyboardControl.getControlOption();
	// Check if critical movements have finished
	if (isJumping) {
		jump();
	} else if (isJumpingRight) {
		jumpRight();
	} else if (isJumpingLeft) {
		jumpLeft();
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
	} else if (isPunchingAnUppercut) {
		completeMovement();
	} else if (isPunchingLow) {
		completeMovement();
	} else if (isPunchingDuck) {
		completeMovement();
	} else if (isPunchingHigh) {
		completeMovement();
	} else {
		// Movements validation to refresh frames
		if (isDucking && (playerCommand != FIRST_PLAYER_MOVE_DOWN &&
				playerCommand != FIRST_PLAYER_MOVE_DOWN_LEFT &&
				playerCommand != FIRST_PLAYER_MOVE_DOWN_RIGHT)) {
			this->refreshFrames();
		}
		if (isWalkingRight && playerCommand != FIRST_PLAYER_MOVE_RIGHT){
			this->refreshFrames();
		}
		if (isWalkingLeft && playerCommand != FIRST_PLAYER_MOVE_LEFT){
			this->refreshFrames();
		}
		this->clearMovementsFlags();

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
			setCurrentSprite();
			jumpRight();
			break;
		case FIRST_PLAYER_MOVE_UP_LEFT:
			this->setMovement(JUMPING_LEFT_MOVEMENT);
			setCurrentSprite();
			jumpLeft();
			break;
		case FIRST_PLAYER_CHANGE_ORIENTATION:
			isRightOriented = !isRightOriented;
			break;
		case FIRST_PLAYER_HI_PUNCH:
			this->setMovement(PUNCHING_HIGH_MOVEMENT);
			setCurrentSprite();
			completeMovement();
			break;
		case FIRST_PLAYER_LO_PUNCH:
			this->setMovement(PUNCHING_LOW_MOVEMENT);
			setCurrentSprite();
			completeMovement();
			break;
		case FIRST_PLAYER_DUCK_PUNCH:
			this->setMovement(PUNCHING_DUCK_MOVEMENT);
			setCurrentSprite();
			completeMovement();
			break;
		case FIRST_PLAYER_UPPERCUT:
			this->setMovement(UPPERCUT_MOVEMENT);
			setCurrentSprite();
			completeMovement();
			break;
		case FIRST_PLAYER_LOW_KICK:
			this->setMovement(LOW_KICK_MOVEMENT);
			setCurrentSprite();
			completeMovement();
			break;
		case FIRST_PLAYER_HIGH_KICK:
			this->setMovement(HIGH_KICK_MOVEMENT);
			setCurrentSprite();
			completeMovement();
			break;
		case FIRST_PLAYER_DUCK_LOW_kICK:
			this->setMovement(DUCK_LOW_KICK_MOVEMENT);
			setCurrentSprite();
			completeMovement();
			break;
		case FIRST_PLAYER_DUCK_HIGH_kICK:
			this->setMovement(DUCK_HIGH_KICK_MOVEMENT);
			setCurrentSprite();
			completeMovement();
			break;
		case FIRST_PLAYER_SUPER_kICK:
			this->setMovement(SUPER_KICK_MOVEMENT);
			setCurrentSprite();
			completeMovement();
			break;
		case NO_INPUT:
			this->setMovement(STANCE);
			setCurrentSprite();
			break;
		}
	}
	SDL_Delay(55);
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


void Character::jumpRight() {
	isJumpingRight = true;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (!this->reachedWindowRightLimit()) {
		positionX = positionX + (2 * ratioX);
	}
	if (this->isTouchingGround(positionY)) {
		isJumpingRight = false;
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY = yGround;
		refreshFrames();
	}
}

void Character::jumpLeft() {
	isJumpingLeft = true;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (!this->reachedWindowLeftLimit()) {
		positionX = positionX - (2 * ratioX);
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
		positionX = positionX + 2 * ratioX;
	}


}

void Character::walkLeft() {
	isWalkingLeft = true;
	if (!this->reachedWindowLeftLimit()){
		positionX = positionX - 2 * ratioX;
	}

}


void Character::setMovement(std::string movement) {
	this->movement = movement;
}

std::string Character::getMovement() {
	return this->movement;
}

void Character::clean() {
	delete this->pParams;
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

bool Character::isMovingRight(){
	if (this->isJumpingRight || this->isWalkingRight) return true;
	return false;
}

bool Character::isMovingLeft(){
	if (this->isJumpingLeft || this->isWalkingLeft) return true;
	return false;
}

void Character::completeMovement(){
	incrementCounter(getMovement());
	setMoveFlag(true);
	int moveCounter = movesCounter.at(getMovement());
	int spriteAmount = currentSprite->getFramesAmount();
	if (moveCounter == spriteAmount) {
		setMoveFlag(false);
		resetCounter(getMovement());
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

std::string Character::getName(){
	return this->name;
}

void Character::setCurrentSprite(){
	if (this->getMovement() == WALKING_RIGHT_MOVEMENT){
			currentSprite = this->characterSprites[this->name+WALK_SUFFIX];

		} else if (this->getMovement() == WALKING_LEFT_MOVEMENT){
			currentSprite = this->characterSprites[this->name+WALK_SUFFIX];

		} else if (this->getMovement() == JUMPING_MOVEMENT){
			currentSprite = this->characterSprites[this->name+JUMP_SUFFIX];

		} else if (this->getMovement() == STANCE){
			currentSprite = this->characterSprites[this->name+STANCE_SUFFIX];

		} else if (this->getMovement() == JUMPING_RIGHT_MOVEMENT ||
				this->getMovement() == JUMPING_LEFT_MOVEMENT){
			currentSprite = this->characterSprites[this->name+JUMP_DIAGONAL_SUFFIX];

		} else if (this->getMovement() == DUCKING_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+DUCK_SUFFIX];

		} else if (this->getMovement() == PUNCHING_HIGH_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+HI_PUNCH_SUFFIX];

		} else if (this->getMovement() == PUNCHING_LOW_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+LO_PUNCH_SUFFIX];

		} else if (this->getMovement() == PUNCHING_DUCK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+DUCK_PUNCH_SUFFIX];

		} else if (this->getMovement() == UPPERCUT_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+UPPERCUT_SUFFIX];

		} else if (this->getMovement() == LOW_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+LOW_KICK_SUFFIX];

		} else if (this->getMovement() == HIGH_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+HIGH_KICK_SUFFIX];

		} else if (this->getMovement() == DUCK_HIGH_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+DUCK_HIGH_KICK_SUFFIX];

		} else if (this->getMovement() == DUCK_LOW_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+DUCK_LOW_KICK_SUFFIX];

		} else if (this->getMovement() == SUPER_KICK_MOVEMENT) {
			currentSprite = this->characterSprites[this->name+SUPER_KICK_SUFFIX];
		} else{
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
	} else {
		//TODO: review
	}

}
