/*
 * Character.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Character.h"
using namespace std;

float gravity = 14.0f;
float jumpVel = 60.0f;

Character::Character() {
	// TODO Auto-generated constructor stub

}
Character::Character(int width, int height, int zindex) {
	this->width = width;
	this->height = height;
	this->zindex = zindex;
}

Character::Character(int posX, int posY, int width, int height, int zindex, std::string spriteWalk, std::string spriteStand, std::string spriteJump) {
	this->time = SDL_GetTicks();
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->posX = posX;
	this-> posY = posY;
	this->spriteStand = spriteStand;
	this->spriteWalk = spriteWalk;
	this->spriteJump = spriteJump;
	this->activeSprite = spriteStand;

	this->frame = 1;
}

Character::Character(int posX, int posY, int width, int height, int zindex) {
	this->time = SDL_GetTicks();
	this->width = width;
	this->height = height;
	this->zindex = zindex;
	this->posX = posX;
	this-> posY = posY;
	this->frame = 0;
	this->setMovement(STANCE);
}


void Character::load(SDL_Renderer* m_pRenderer) {
	this->m_pRenderer = m_pRenderer;
	Sprite* spriteWalk = new Sprite("subzerowalk", "images/spritesheets_subzero/UMK3_Sub-Zero_walk2.png",
			m_pRenderer, 66, 132, 10);
	Sprite* spriteStance = new Sprite("subzerostand", "images/spritesheets_subzero/UMK3_Sub-Zero_stance.png",
			m_pRenderer, 66, 132, 6);
	Sprite* spriteJump = new Sprite("subzerojump", "images/spritesheets_subzero/UMK3_Sub-Zero_duckjump.png",
			m_pRenderer, 66, 132, 1);

	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type("subzerowalk", spriteWalk));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type("subzerostand", spriteStance));
	this->characterSprites.insert(std::map<std::string, Sprite*>::value_type("subzerojump", spriteJump));
}

void Character::draw() {
	Sprite* currentSprite;
	if (this->getMovement() == WALKING_RIGHT_MOVEMENT){
		currentSprite = this->characterSprites["subzerowalk"];
	} else if (this->getMovement() == JUMPING_MOVEMENT){
		currentSprite = this->characterSprites["subzerojump"];
	} else if (this->getMovement() == STANCE){
		currentSprite = this->characterSprites["subzerostand"];
	} else{
		//TODO: review
	}
	int currentFrame = currentSprite->getNextFrame();
	TextureManager::Instance()->drawFrame(currentSprite->getSpriteId(),
			this->x(), this->y(), currentSprite->getSpriteWidth(), currentSprite->getSpriteHeight(),
			1, currentFrame,
			this->m_pRenderer,SDL_FLIP_NONE);
}

std::string Character::getActiveSprite(){
	return this->activeSprite;
}

int Character::h(){return this->height;}
int Character::w(){return this->width;}
int Character::x(){return this->posX;}
float Character::y(){return this->posY;}
void Character::setY(float posY){this->posY = posY;}
void Character::setX(int posX){this->posX = posX;}
int Character::getFrame(){return frame;}

void Character::setActiveSprite(std::string active){
	this->activeSprite = active;
}


void Character::update(){
	if (this->movement == JUMPING_MOVEMENT) {
		this->jump();
	} else if (this->movement == WALKING_RIGHT_MOVEMENT) {
		this->walkRight();
	} else if (this->movement == WALKING_LEFT_MOVEMENT) {
		this->walkLeft();
	} else {
		//TODO: Review
	}
	this->time = SDL_GetTicks();
}


void Character::jump(){
	posY = posY - jumpVel;
	jumpVel -= gravity;
	if (posY >= 480-132){
		jumpVel = 60.0f;
		this->setMovement(STANCE);
		this->posY = 480-132;
		//this->setActiveSprite("subzerostand");
	}
}

void Character::walkRight() {
	this->posX = this->posX + 7;
}

void Character::walkLeft() {
	this->posX = this->posX - 7;
}

void Character::setMovement(std::string movement){
	this->movement=movement;
}

std::string Character::getMovement(){
	 return this->movement;
}

Character::~Character() {
	// TODO Auto-generated destructor stub
}

