/*
 * Character.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */


#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../headers/Constants.h"
#include "../headers/Sprite.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
using namespace std;

class Character {
private:
	int time;
	int width;
	int height;
	int zindex;
	int posX;
    float posY;
	std::string movement;
	std::string spriteWalk;
	std::string spriteStand;
	std::string spriteJump;
	std::string activeSprite;
	int frame;
	std::map<std::string,Sprite*> characterSprites;
	SDL_Renderer* m_pRenderer;
public:
	Character();
	Character(int width, int height, int zindex);
	Character(int posX, int posY, int width, int height, int zindex, std::string spriteWalk,std::string spriteStand,std::string spriteJump);
	Character(int posX, int posY, int width, int height, int zindex);
	void load(SDL_Renderer* m_pRenderer);
	virtual ~Character();
	std::string getActiveSprite();
	int h();
	int w();
	int x();
	float y();
	void setY(float posY);
	void setX(int posX);
	void setMovement(std::string movement);
	std::string getMovement();
	void setActiveSprite(std::string active);
	int getNextFrame();
	int getFrame();
	void update();
	void jump();
	void walkRight();
	void walkLeft();
	void draw();
};

#endif /* CHARACTER_H_ */
