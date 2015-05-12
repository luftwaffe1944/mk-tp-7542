/*
 * ThrowableObject.cpp
 *
 *  Created on: 11/5/2015
 *      Author: julian
 */

#include "../headers/ThrowableObject.h"

ThrowableObject::ThrowableObject(const LoaderParams* pParams) : SDLObjectGUI(pParams) {
	this->posXSetReleaser = false;
	this->posYsetReleaser = false;
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
	}
}


void ThrowableObject::update() {

	if (this->releaser->fire) {
		//orientacion del que dispara
		this->playerIsRightOriented = this->releaser->getIsRightOriented();
		//arranca la bola pegada al personaje
		if (this->playerIsRightOriented) {
			if (!this->posXSetReleaser) {
				this->positionX = this->releaser->getPositionX() / ratioX + (this->releaser->getWidth())* 3/5;
				this->posXSetReleaser = true;
			}
			if(!this->posYsetReleaser) {
				this->positionY = this->releaser->getPositionY() / ratioY + (this->releaser->getPositionY() / ratioY) * 0.3;
				this->posYsetReleaser = true;
			}
		} else {
			if (!this->posXSetReleaser) {
				this->positionX = this->releaser->getPositionX() / ratioX + (this->releaser->getWidth())* 1/5;
				this->posXSetReleaser = true;
			}
			if(!this->posYsetReleaser) {
				this->positionY = this->releaser->getPositionY() / ratioY + (this->releaser->getPositionY() / ratioY) * 0.3;
				this->posYsetReleaser = true;
			}
		}




		bool endBoom = false;
		//si esta mirando para la derecha
		//TODO: hacerlo colisionable ahora corta cuando llega a la posX del personaje que recibe el objecto arrojable
		if (this->playerIsRightOriented && !endBoom) {
			if (this->positionX < (this->receiver->getPositionX() / ratioX + (this->receiver->getWidth())* 1/5)) {
				this->positionX+= OBJECT_SPEED;
			} else {
				endBoom = true;
			}
		}
		//si esta mirando para izq
		//TODO: hacerlo colisionable, ahora corta cuando llega a la posX del personaje que recibe el objecto arrojable
		if (!this->playerIsRightOriented && !endBoom) {
			if ((this->receiver->getPositionX() / ratioX + (this->receiver->getWidth())* 3/5 < this->positionX)) {
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
}

void ThrowableObject::clean(){

}
