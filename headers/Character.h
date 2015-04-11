/*
 * Character.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "Constants.h"
#include "Sprite.h"
#include "InputControl.h"
#include <string>
#include "SDLObjectGUI.h"
#include <SDL.h>
#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;


class Character : public SDLObjectGUI {
private:
	std::string name;
	int zindex;
	std::string orientation;
	std::string movement;
	std::map<std::string,Sprite*> characterSprites;
	SDL_Renderer* renderer; //TODO: review
	bool isJumping = false;
	bool isJumpingForward = false;
	bool isJumpingBackward = false;

public:
	Character();
	Character(int width, int height, int zindex, std::string orientation);
	Character(std::string name, int width, int height, int zindex, std::string orientation);
	virtual bool load(SDL_Renderer* render);
	void render(SDL_Renderer* render);
	virtual ~Character();
	Character(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	//Movement & position methods
	void jump();
	void jumpForward();
	void walkRight();
	void walkLeft();
	std::string getMovement();
	void setMovement(std::string movement);
	bool isTouchingGround(float positionY);

};

#endif /* CHARACTER_H_ */
