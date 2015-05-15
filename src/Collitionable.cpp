
#include "../headers/Collitionable.h"
#include "../headers/Box.h"
#include <iostream>
#include <stdlib.h>


Collitionable::Collitionable(){
	this->isCActive=true;
	this->isCMoving=false;
	this->setIsWeapon(true);
}


Collitionable::~Collitionable(){
	for (std::vector<Box*>::size_type i = 0; i != this->Shapes.size(); i++) {
		delete Shapes[i];
	}
	this->Shapes.clear();
}


vector<Box*> Collitionable::getCShapes(){
	return this->Shapes;
}

void Collitionable::initCShapes(int qty,float X, float Y, float W, float H){

	Box* mainShape = new Box(X,Y,W,H,true);
	this->Shapes.push_back(mainShape);

	for (int i=1; i<=qty-1; i++){
		Box* auxShape = new Box(X,Y,0,0,false); //X,Y sin validez para figura inactiva
		this->Shapes.push_back(auxShape);
	}
};

void Collitionable::updateCShapesPosition(float X, float Y){
	this->Shapes[0]->setCenter(X,Y);
	this->Shapes[1]->setActive(false);
}

void Collitionable::updateCShapesPosition(float X, float Y, float W, float H){
	this->Shapes[0]->setCenter(X,Y);
	this->Shapes[0]->setWidth(W);
	this->Shapes[0]->setHeight(H);

	this->Shapes[1]->setActive(false);
}
void Collitionable::updateCShapesPosition(float X, float Y, float W, float H, bool rightOriented, bool secShapeTop, float secShapeW, float secShapeH){
	vector<Box*> boxes = this->Shapes;
	boxes[0]->setCenter(X,Y);
	boxes[0]->setWidth(W);
	boxes[0]->setHeight(H);

	float secX,secY;
	if (rightOriented){
		secX = X + (W/2) + (secShapeW/2);
	}else{
		secX = X - (W/2) - (secShapeW/2);
	}
	if (secShapeTop){
		secY = boxes[0]->getTopY() - (secShapeH/2);
	}else{
		secY = boxes[0]->getBottomY() + (secShapeH/2);
	}

	boxes[1]->setCenter(secX,secY);
	boxes[1]->setWidth(secShapeW);
	boxes[1]->setHeight(secShapeH);
	boxes[1]->setActive(true);
}


void Collitionable::getCNextPosition(float* nextPositionX, float* nextPositionY){

}

