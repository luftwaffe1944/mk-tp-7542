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

Character::Character(const LoaderParams* pParams) :
		SDLObjectGUI(pParams) {

}

Character::Character(int width, int height, int zindex, bool isRightOriented) : SDLObjectGUI() {
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->isRightOriented = isRightOriented;
}

Character::Character(string name, int width, int height, int zindex, bool isRightOriented, float ratio, int winWidth) : SDLObjectGUI(){
	this->name = name;
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->isRightOriented = isRightOriented;
	//TODO: Review positions according to logic and pixels measures.
	this->positionX = 0;
	this->positionY = winWidth - height;
	// initializing movements statements
	this->isJumping = false;
	this->isJumpingRight = false;
	this->isJumpingLeft = false;
	this->isWalkingRight = false;
	this->isWalkingLeft = false;
	this->textureID = name;
	this->drawRatio = ratio;
}

bool Character::load(SDL_Renderer* render) {
	this->renderer = render;
	Sprite* spriteWalk = new Sprite(this->name+WALK_SUFFIX, this->imagePath+"/UMK3_Sub-Zero_walk.png",
			renderer, 66, 132, 10);
	Sprite* spriteStance = new Sprite(this->name+STANCE_SUFFIX, this->imagePath+"UMK3_Sub-Zero_stance.png",
			renderer, 66, 132, 6);
	Sprite* spriteJump = new Sprite(this->name+JUMP_SUFFIX, this->imagePath+"UMK3_Sub-Zero_jump.png",
			renderer, 73, 100, 0);
	Sprite* spriteJumpRight = new Sprite(this->name+JUMP_RIGHT_SUFFIX, this->imagePath+"UMK3_Sub-Zero_jump_forward.png",
				renderer, 78, 158, 9);
	//TODO: Files path must be generated depending on the character
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+WALK_SUFFIX, spriteWalk));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+STANCE_SUFFIX, spriteStance));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+JUMP_SUFFIX, spriteJump));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+JUMP_RIGHT_SUFFIX, spriteJumpRight));

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
		} else if (this->getMovement() == JUMPING_RIGHT_MOVEMENT){
			currentSprite = this->characterSprites[this->name+JUMP_RIGHT_SUFFIX];
		} else{
			//TODO: review
		}
		int currentFrame;
		if (shouldMoveForward()) {
			currentFrame = currentSprite->getNextForwardingFrame();
		} else {
			currentFrame = currentSprite->getNextBackwardingFrame();
		}
		TextureManager::Instance()->drawFrame(currentSprite->getSpriteId(),
				(int) positionX, (int) positionY, currentSprite->getSpriteWidth(), currentSprite->getSpriteHeight(),
				1, currentFrame,
				renderer,(!isRightOriented)?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
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

	// Check if critical movements have finished
	if (isJumping) {
		jump();
	} else if (isJumpingRight) {
		jumpRight();
	} else if (isJumpingLeft) {
		//jumpLeft();
	} else {
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
		case FIRST_PLAYER_MOVE_UP_RIGHT:
			this->setMovement(JUMPING_RIGHT_MOVEMENT);
			jumpRight();
			break;
		case FIRST_PLAYER_CHANGE_ORIENTATION:
			isRightOriented =! isRightOriented;
			break;
		case NO_INPUT:
			this->setMovement(STANCE);
			this->clearMovementsFlags();
			break;
		}
	}
	SDL_Delay(55);
	currentFrame = int(((SDL_GetTicks() / 100) % 6));
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
		this->positionY =
				(MKGame::Instance()->getGameGUI()->getWindow().heightPx
						- this->height);
	}
}

void Character::jumpRight() {
	isJumpingRight = true;
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	walkRight();
	if (this->isTouchingGround(positionY)) {
		isJumpingRight = false;
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY =
				(MKGame::Instance()->getGameGUI()->getWindow().heightPx
						- this->height);
	}
}


bool Character::isTouchingGround(float positionY) {
	if (positionY
			>= (MKGame::Instance()->getGameGUI()->getWindow().heightPx
					- this->height)) {
		return true;
	}
	return false;
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

Character::~Character() {
	// TODO Auto-generated destructor stub
}
