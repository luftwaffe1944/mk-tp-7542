
#include "../headers/Collitionable.h"
#include "../headers/Box.h"
#include <iostream>
#include <stdlib.h>


Collitionable::Collitionable(){
	this->isCActive=true;
	this->isCMoving=false;
}

Collitionable::~Collitionable(){
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
}


void Collitionable::getCNextPosition(float* nextPositionX, float* nextPositionY){

}
