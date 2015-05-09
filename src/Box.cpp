#include "../headers/Box.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

	Box::Box(float X, float Y,int W,int H,bool active){this->centerX=X; this->centerY=Y; this->width=W; this->height=H; this->active=active;}
	Box::~Box(){};
	void Box::setHeight(int H){this->height=H;}
	void Box::setWidth(int W){this->width=W;}
	void Box::setCenter(float X, float Y){this->centerX=X; this->centerY=Y;}
	void Box::setActive(bool active){this->active=active;}
	float Box::getTopY(){return (this->centerY)+(this->height/2);}
	float Box::getBottomY(){return (this->centerY)-(this->height/2);}
	float Box::getLeftX(){return (this->centerX)-(this->width/2);}
	float Box::getRightX(){return (this->centerX)+(this->height/2);}
	bool Box::isActive(){return this->active;}

	Box* Box::cloneBox(){
		Box* box = new Box(this->centerX, this->centerY, this->width, this->height, this->active);
		return box;
	}

	bool Box::isColliding(Box* box2){
		bool collide = false;

		bool overlapBox1Left = ((this->getRightX() > box2->getLeftX()) && (this->getLeftX() < box2->getLeftX()));
		bool overlapBox1Right = ((this->getRightX() > box2->getRightX()) && (this->getLeftX() < box2->getRightX()));
		bool overlapBox1OnBox2X = ((this->getLeftX() < box2->getLeftX()) && (this->getRightX() > box2->getRightX()));

		bool overlapBox1Top = ((this->getTopY() > box2->getBottomY()) && (this->getBottomY() < box2->getTopY()));
		bool overlapBox1Bottom = ((this->getTopY() > box2->getTopY()) && (this->getBottomY() < box2->getTopY()));
		bool overlapBox1OnBox2Y = ((this->getTopY() > box2->getTopY()) && (this->getBottomY() < box2->getBottomY()));


		bool overlapXaxis = (overlapBox1Left || overlapBox1Right || overlapBox1OnBox2X);
		bool overlapYaxis = (overlapBox1Top || overlapBox1Bottom || overlapBox1OnBox2Y);

		if (overlapXaxis && overlapYaxis){
			collide=true;
		}
		return collide;
	}
