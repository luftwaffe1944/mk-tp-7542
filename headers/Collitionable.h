/*
 * Character.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef COLLITIONABLE_H_
#define COLLITIONABLE_H_

#include <string>
#include "SDLObjectGUI.h"
#include <SDL.h>
#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;

class Box {
private:
	int height;
	int width;
	float centerX;
	float centerY;
	bool active;

public:
	Box();
	virtual ~Box();
	void setHeight(int H){this->height=H;}
	void setWidth(int W){this->width=W;}
	void setCenter(float X, float Y){this->centerX=X; this->centerY=Y;}
	float getTopY(){return (this->centerY)+(this->height/2);}
	float getBottomY(){return (this->centerY)-(this->height/2);}
	float getLeftX(){return (this->centerX)-(this->width/2);}
	float getRightX(){return (this->centerX)+(this->height/2);}
	bool isActive(){return this->active;}
};

class Collitionable {
private:

	vector<Box*> Shapes;
	bool isMoving;


	std::map<std::string,Sprite*> characterSprites;
	SDL_Renderer* renderer; //TODO: review

public:
	Collitionable();

	virtual ~Collitionable();
	Collitionable(const LoaderParams* pParams, bool isRightOriented);

	virtual void update();

	//Movement & position methods

	bool isMoving();

};

#endif /* COLLITIONABLE_H_ */
