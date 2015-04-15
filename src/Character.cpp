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
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 10);
	Sprite* spriteStance = new Sprite(this->name+STANCE_SUFFIX, characterPath+STANCE_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 6);
	Sprite* spriteJump = new Sprite(this->name+JUMP_SUFFIX, characterPath+JUMP_SPRITE,
			renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 1);
	Sprite* spriteJumpDiagonal = new Sprite(this->name+JUMP_DIAGONAL_SUFFIX, characterPath+DIAGONAL_JUMP_SPRITE,
				renderer, SPRITE_WIDTH, SPRITE_HEIGHT + 10, 9);
	Sprite* spriteDuck = new Sprite(this->name+DUCK_SUFFIX, characterPath+DUCK_SPRITE,
					renderer, SPRITE_WIDTH, SPRITE_HEIGHT, 3);
	//TODO: Files path must be generated depending on the character
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+WALK_SUFFIX, spriteWalk));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+STANCE_SUFFIX, spriteStance));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+JUMP_SUFFIX, spriteJump));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+JUMP_DIAGONAL_SUFFIX, spriteJumpDiagonal));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+DUCK_SUFFIX, spriteDuck));

}

void Character::render(SDL_Renderer* render) {
}


void Character::draw() {
	Sprite* currentSprite;
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
		} else{
			//TODO: review
		}
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
			walkRight();
			break;
		case FIRST_PLAYER_MOVE_LEFT:
			this->setMovement(WALKING_LEFT_MOVEMENT);
			walkLeft();
			break;
		case FIRST_PLAYER_MOVE_UP:
			this->setMovement(JUMPING_MOVEMENT);
			jump();
			break;
		case FIRST_PLAYER_MOVE_DOWN:
			this->setMovement(DUCKING_MOVEMENT);
			this->isDucking = true;
			break;
		case FIRST_PLAYER_MOVE_DOWN_LEFT:
			this->setMovement(DUCKING_MOVEMENT);
			this->isDucking = true;
			break;
		case FIRST_PLAYER_MOVE_DOWN_RIGHT:
			this->setMovement(DUCKING_MOVEMENT);
			this->isDucking = true;
			break;
		case FIRST_PLAYER_MOVE_UP_RIGHT:
			this->setMovement(JUMPING_RIGHT_MOVEMENT);
			jumpRight();
			break;
		case FIRST_PLAYER_MOVE_UP_LEFT:
			this->setMovement(JUMPING_LEFT_MOVEMENT);
			jumpLeft();
			break;
		case FIRST_PLAYER_CHANGE_ORIENTATION:
			isRightOriented = !isRightOriented;
			break;
		case NO_INPUT:
			this->setMovement(STANCE);
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

Character::~Character() {
	// TODO Auto-generated destructor stub

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
