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
#include <string>
#include <sstream>
#include <iostream>


float gravity = 14.0f;
float jumpVel = 60.0f;

Character::Character(const LoaderParams* pParams) :
		SDLObjectGUI(pParams) {

}

Character::Character(int width, int height, int zindex, std::string orientation) : SDLObjectGUI() {
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->orientation = orientation;
}

Character::Character(string name, int width, int height, int zindex, std::string orientation) : SDLObjectGUI(){
	this->name = name;
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->orientation = orientation;
}

bool Character::load(SDL_Renderer* render) {
	this->renderer = render;
	Sprite* spriteWalk = new Sprite(this->name+WALK_SUFFIX, this->imagePath+"/UMK3_Sub-Zero_walk.png",
			renderer, 66, 132, 10);
	Sprite* spriteStance = new Sprite(this->name+STANCE_SUFFIX, this->imagePath+"UMK3_Sub-Zero_stance.png",
			renderer, 66, 132, 6);
	Sprite* spriteJump = new Sprite(this->name+JUMP_SUFFIX, this->imagePath+"UMK3_Sub-Zero_duckjump.png",
			renderer, 66, 132, 1);
	//TODO: Files path must be generated depending on the character
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+WALK_SUFFIX, spriteWalk));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+STANCE_SUFFIX, spriteStance));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type(this->name+JUMP_SUFFIX, spriteJump));

}

void Character::render(SDL_Renderer* render) {
	Sprite* currentSprite;
		if (this->getMovement() == WALKING_RIGHT_MOVEMENT){
			currentSprite = this->characterSprites[this->name+WALK_SUFFIX];
		} else if (this->getMovement() == JUMPING_MOVEMENT){
			currentSprite = this->characterSprites[this->name+JUMP_SUFFIX];
		} else if (this->getMovement() == STANCE){
			currentSprite = this->characterSprites[this->name+STANCE_SUFFIX];
		} else{
			//TODO: review
		}
		int currentFrame = currentSprite->getNextFrame();
		TextureManager::Instance()->drawFrame(currentSprite->getSpriteId(),
				(int) positionX, (int) positionY, currentSprite->getSpriteWidth(), currentSprite->getSpriteHeight(),
				1, currentFrame,
				this->renderer,SDL_FLIP_NONE);
}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

void Character::draw() {
	Sprite* currentSprite;
		if (this->getMovement() == WALKING_RIGHT_MOVEMENT){
			currentSprite = this->characterSprites[this->name+WALK_SUFFIX];
		} else if (this->getMovement() == JUMPING_MOVEMENT){
			currentSprite = this->characterSprites[this->name+JUMP_SUFFIX];
		} else if (this->getMovement() == STANCE){
			currentSprite = this->characterSprites[this->name+STANCE_SUFFIX];
		} else{
			//TODO: review
		}
		int currentFrame = currentSprite->getNextFrame();
		TextureManager::Instance()->drawFrame(currentSprite->getSpriteId(),
				(int) positionX, (int) positionY, currentSprite->getSpriteWidth(), currentSprite->getSpriteHeight(),
				1, currentFrame,
				renderer,SDL_FLIP_NONE);
}

void Character::update() {

	InputCommand playerCommand = InputControl::Instance()->getFirstPlayerMove();
	//InputCommand optionCommand = keyboardControl.getControlOption();
		switch(playerCommand){
		case FIRST_PLAYER_MOVE_RIGHT:
			if (!isJumping && !isJumpingForward) {
				this->setMovement(WALKING_RIGHT_MOVEMENT);
				walkRight();
			}
			break;
		case FIRST_PLAYER_MOVE_LEFT:
			this->setMovement(WALKING_LEFT_MOVEMENT);
			walkLeft();
			break;
		case FIRST_PLAYER_MOVE_UP:
			this->setMovement(JUMPING_MOVEMENT);
			jump();
			isJumping = true;
			break;
		case NO_INPUT:
			if (this->isTouchingGround(this->positionY)) {
				this->setMovement(STANCE);
				isJumping = false;
			} else {
				jump();
			}
			break;
		}
		SDL_Delay( 55 );
		currentFrame = int(((SDL_GetTicks() / 100) % 6));
}


void Character::jump(){
	positionY = positionY - jumpVel;
	jumpVel -= gravity;
	if (this->isTouchingGround(positionY)){
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->positionY = (MKGame::Instance()->getGameGUI()->getWindow().heightPx - this->height);
	}
}

bool Character::isTouchingGround(float positionY) {
	if (positionY >= (MKGame::Instance()->getGameGUI()->getWindow().heightPx - this->height)) {
		return true;
	}
	return false;
}

void Character::walkRight() {
	positionX = positionX + 7;
}

void Character::walkLeft() {
	positionX = positionX - 7;
}

void Character::setMovement(std::string movement){
	this->movement=movement;
}

std::string Character::getMovement(){
	 return this->movement;
}

void Character::clean() {
}
