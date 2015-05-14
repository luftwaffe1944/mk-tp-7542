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
	this->setCMoving(true);
	this->isWeapon = true;
}

ThrowableObject::~ThrowableObject() {
	// TODO Auto-generated destructor stub
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
	*nextPositionX = this->positionX + OBJECT_SPEED;
	*nextPositionY = this->positionY;
}

void ThrowableObject::update() {

	if (this->releaser->fire) {
		if (this->orientationPosXFix != 0) {
			this->fixPosXStandingCharacter();
			this->orientationPosXFix = 0;
		}


		float charWidht = this->releaser->getWidth()*ratioX;
		float charHeight = (this->releaser->getHeight())*ratioY;
		float centerX = this->releaser->getPositionX() + this->releaser->getWidth() * ratioX / 2;
		float centerY = this->releaser->getPositionY() + this->releaser->getHeight() * ratioY / 2;


		//orientacion del que dispara
		this->playerIsRightOriented = this->releaser->getIsRightOriented();

		//arranca la bola pegada al personaje
		//float posXCharacter = this->releaser->getPositionX() / ratioX;
		//float posYCharacter = this->releaser->getPositionY() / ratioY;
		//float centerWidthCharacter = (this->releaser->getWidth() / 2);
		//float centerHeightCharacter = (this->releaser->getHeight() / 2);

		if (!this->posXSetReleaser) {
			if (this->playerIsRightOriented) {
				this->positionX = centerX + 10;
			}
			else {
				this->positionX = centerX - 10;
			}

			this->posXSetReleaser = true;

		}
		if(!this->posYsetReleaser) {
			this->positionY = centerY;
			this->posYsetReleaser = true;
		}



		bool endBoom = false;
		//si esta mirando para la derecha
		//TODO: hacerlo colisionable ahora corta cuando llega a la posX del personaje que recibe el objecto arrojable
		if (this->playerIsRightOriented && !endBoom) {
			if (this->positionX / ratioX < this->widthWindow) {
				this->positionX+= OBJECT_SPEED;
			} else {
				endBoom = true;
			}
		}

		//si esta mirando para izq
		//TODO: hacerlo colisionable, ahora corta cuando llega a la posX del personaje que recibe el objecto arrojable
		if (!this->playerIsRightOriented && !endBoom) {
			if (0 < this->positionX / ratioX) {
				this->positionX-= OBJECT_SPEED;
			} else {
				endBoom = true;
			}
		}

		//Si llego al personaje que recibe, se setea que no se muestre mas
		//TODO: hacerlo colisionable
		if (endBoom) {
			this->releaser->fire = false;
			this->posXSetReleaser = false;
			this->posYsetReleaser = false;
		}

		//if (this->positionX / ratioX > this->widthWindow) {
		//	this->releaser->fire = false;
		//	this->posXSetReleaser = false;
		//	this->posYsetReleaser = false;
		//}
		//cout << "Y: " << this->positionY << " " << this->receiver->getPositionY() << endl;
		//this->updateCShapesPosition(this->positionX, this->positionY, this->width * ratioX, this->height * ratioY);
	}
	
}

void ThrowableObject::clean(){

}

void ThrowableObject::setFixPosXStandingCharacter( int orientation) {
	this->orientationPosXFix = orientation;
}

void ThrowableObject::fixPosXStandingCharacter() {
	positionX = positionX + FRONTAL_LAYER_SPEED * ratioX * this->orientationPosXFix * -1;
}
