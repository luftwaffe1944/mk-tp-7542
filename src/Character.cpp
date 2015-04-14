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

float gravity = 14.0f;
float jumpVel = 60.0f;

Character::Character(const LoaderParams* pParams, bool isRightOriented) :
		SDLObjectGUI(pParams) {
		this->isRightOriented = isRightOriented;
		this->name = pParams->getTextureID();
		this->yGround = (GameGUI::getInstance()->getStage()->getYGround() - this->height);
cout << yGround << " " << height << " " << GameGUI::getInstance()->getStage()->getYGround() << endl;
		//TODO: Review positions according to logic and pixels measures.
		//override constructor
		// initializing movements statements
		clearMovementsFlags();
}



bool Character::load(SDL_Renderer* render) {
	this->renderer = render;
	Sprite* spriteWalk = new Sprite(this->name+WALK_SUFFIX, this->imagePath+"/UMK3_Sub-Zero_walk.png",
			renderer, 100, 135, 11);
	Sprite* spriteStance = new Sprite(this->name+STANCE_SUFFIX, this->imagePath+"UMK3_Sub-Zero_stance.png",
			renderer, 100, 135, 6);
	Sprite* spriteJump = new Sprite(this->name+JUMP_SUFFIX, this->imagePath+"UMK3_Sub-Zero_jump.png",
			renderer, 73, 100, 1);
	Sprite* spriteJumpDiagonal = new Sprite(this->name+JUMP_DIAGONAL_SUFFIX, this->imagePath+"UMK3_Sub-Zero_jump_forward.png",
				renderer, 100, 170, 9);
	Sprite* spriteDuck = new Sprite(this->name+DUCK_SUFFIX, this->imagePath+"UMK3_Sub-Zero_duck.png",
					renderer, 100, 140, 3);
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
				(int) positionX, (int) positionY, currentSprite->getSpriteWidth(), currentSprite->getSpriteHeight(),
				1, currentFrame,
				renderer,(!isRightOriented)? SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
}

bool Character::shouldMoveForward() {
	if ( (this->isRightOriented && (isJumpingRight || isWalkingRight)) ||
			(!this->isRightOriented && (isJumpingLeft || isWalkingLeft)) ) {
		return true;
	} else {
		return false;
	}
}

void Character::update() {

	InputCommand playerCommand = InputControl::Instance()->getFirstPlayerMove();
	//InputCommand optionCommand = keyboardControl.getControlOption();
	isDucking = false;
	// Check if critical movements have finished
	if (isJumping) {
		jump();
	} else if (isJumpingRight) {
		jumpRight();
	} else if (isJumpingLeft) {
		jumpLeft();
	} else {
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
	positionX+=10;
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
	positionX-=10;
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
	positionX = positionX + 7;

}

void Character::walkLeft() {
	isWalkingLeft = true;
	positionX = positionX - 7;

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

float Character::getYGround() {
	return this->yGround;
}

Character::~Character() {
	// TODO Auto-generated destructor stub

}
