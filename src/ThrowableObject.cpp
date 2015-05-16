/*
 * ThrowableObject.cpp
 *
 *  Created on: 11/5/2015
 *      Author: julian
 */

#include "../headers/ThrowableObject.h"
#include "../headers/MKGame.h"

ThrowableObject::ThrowableObject(const LoaderParams* pParams, float widthWindow) : SDLObjectGUI(pParams) {
	this->posXSetReleaser = false;
	this->posYsetReleaser = false;
	this->widthWindow = widthWindow;
	this->initCShapes(2,this->positionX, this->positionY,this->width,this->height);
	this->setCMoving(false);
	this->setCActive(false);
	this->isWeapon = true;
}

ThrowableObject::~ThrowableObject() {
	// TODO Auto-generated destructor stub
	delete this->pParams;
}

void ThrowableObject::setReceiver(Character* receiver) {
	this->receiver = receiver;
}

void ThrowableObject::setReleaser(Character* releaser) {
	this->releaser = releaser;
}


void ThrowableObject::draw() {
	if (this->releaser->fire) {

		float auxX = this->positionX;
		float auxY = this->positionY;
		this->positionX = this->positionX / ratioX;
		this->positionY = this->positionY / ratioY;
		SDLObjectGUI::draw();
		this->positionX = auxX;
		this->positionY = auxY;
		//draw box colisionale
		SDL_Rect outlineRect2 = { this->positionX, positionY, this->width * ratioX, this->height * ratioY };
		SDL_SetRenderDrawColor( MKGame::Instance()->getRenderer(), 0xFF, 0x00, 0x00, 0xFF );
		SDL_RenderDrawRect( MKGame::Instance()->getRenderer(), &outlineRect2 );
	}
}


void ThrowableObject::getCNextPosition(float* nextPositionX, float* nextPositionY){
	if (this->playerIsRightOriented) {
		*nextPositionX = this->positionX + OBJECT_SPEED;
	}else{
		*nextPositionX = this->positionX - OBJECT_SPEED;
	}
	*nextPositionY = this->positionY;
}

void ThrowableObject::update() {
	float centerX;
	float centerY;

	if (!this->getCActive()){
		//

		this->positionY = this->releaser->posYBox + this->releaser->heightBox / 2;
		//orientacion del que dispara
		this->playerIsRightOriented = this->releaser->getIsRightOriented();
		if (this->playerIsRightOriented) {
			this->positionX = this->releaser->posXBox + this->releaser->widthBox *2;
		}else{
			this->positionX = this->releaser->posXBox - this->releaser->widthBox;
		}
		this->setLive();
	}

	if (this->releaser->fire) {
		if (!this->getDestroy()) {
			this->Cactivation(true);
		}else{
			this->releaser->fire = false;
			this->Cactivation(false);
		}

		if (this->orientationPosXFix != 0) {
			this->fixPosXStandingCharacter();
			this->orientationPosXFix = 0;
		}
		if (this->playerIsRightOriented) {
			this->positionX = this->positionX + OBJECT_SPEED;
		}
		else {
			this->positionX = this->positionX - OBJECT_SPEED;
		}
		if (!this->posXSetReleaser) {
			this->posXSetReleaser = true;
			cout << "X salida: " << this->positionX << " ";
		}
		if(!this->posYsetReleaser) {
			this->posYsetReleaser = true;
			cout << "Y salida: " << this->positionY << " ";
		}
		if ((this->positionX / ratioX > this->widthWindow) || (this->positionX / ratioX <0)) {
			this->releaser->fire = false;
			this->Cactivation(false);
			this->setCActive(false);
			this->posXSetReleaser = false;
			this->posYsetReleaser = false;
		}
		cout << "X Actual: " << this->getPositionX() << endl;
		//cout << "Y: " << this->positionY << " " << this->receiver->getPositionY() << endl;
		this->updateCShapesPosition(this->positionX, this->positionY, this->width * ratioX, this->height * ratioY);
	}
	
}

void ThrowableObject::clean(){
	delete this->pParams;
}

void ThrowableObject::setFixPosXStandingCharacter( int orientation) {
	this->orientationPosXFix = orientation;
}

void ThrowableObject::fixPosXStandingCharacter() {
	positionX = positionX + FRONTAL_LAYER_SPEED * ratioX * this->orientationPosXFix * -1;
}
