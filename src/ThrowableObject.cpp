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
		SDLObjectGUI::draw();

		//draw box colisionale
		SDL_Rect outlineRect2 = { this->positionX * ratioX, positionY * ratioY, this->width * ratioX, this->height * ratioY };
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

		//orientacion del que dispara
		this->playerIsRightOriented = this->releaser->getIsRightOriented();

		//arranca la bola pegada al personaje
		float posXCharacter = this->releaser->getPositionX() / ratioX;
		float posYCharacter = this->releaser->getPositionY() / ratioY;
		float centerWidthCharacter = (this->releaser->getWidth() / 2);
		float centerHeightCharacter = (this->releaser->getHeight() / 2);

		if (!this->posXSetReleaser) {
			if (this->playerIsRightOriented) {
				this->positionX = posXCharacter + centerWidthCharacter + 10;
			}
			else {
				this->positionX = posXCharacter + centerWidthCharacter - 10;
			}

			this->posXSetReleaser = true;
		}
		if(!this->posYsetReleaser) {
			this->positionY = posYCharacter + centerHeightCharacter;
			this->posYsetReleaser = true;
		}



		bool endBoom = false;
		//si esta mirando para la derecha
		//TODO: hacerlo colisionable ahora corta cuando llega a la posX del personaje que recibe el objecto arrojable
		if (this->playerIsRightOriented && !endBoom) {
			if (this->positionX < this->receiver->getPositionX() / ratioX + this->receiver->getWidth() /2) {
				this->positionX+= OBJECT_SPEED;
			} else {
				endBoom = true;
			}
		}

		//si esta mirando para izq
		//TODO: hacerlo colisionable, ahora corta cuando llega a la posX del personaje que recibe el objecto arrojable
		if (!this->playerIsRightOriented && !endBoom) {
			if (this->receiver->getPositionX() / ratioX + this->receiver->getWidth()/ 2 < this->positionX) {
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
	}
	this->updateCShapesPosition(this->positionX * ratioX, this->positionY * ratioY, this->width * ratioX, this->height * ratioY );
}

void ThrowableObject::clean(){

}
