/*
 * AIMovement.cpp
 *
 *  Created on: 27/5/2015
 *      Author: uje
 */

#include "../headers/AIMovement.h"

AIMovement* AIMovement::cm_pInstance = 0;

//std::vector<int> AIMovement::sarasa = {1,2,3};

AIMovement::AIMovement() {
	// TODO Auto-generated constructor stub

}

AIMovement* AIMovement::Instance() {
	if (!cm_pInstance) {
		cm_pInstance = new AIMovement();
		return cm_pInstance;
	} else {
		return cm_pInstance;
	}
}

void AIMovement::init() {
	character = GameGUI::getInstance()->getCharacters().at(1);
	opponent = GameGUI::getInstance()->getCharacters().at(0);
	isInitialized = true;
}

void AIMovement::clean() {
	isInitialized = false;
}

void AIMovement::solveAIMovement() {

	float distance = CharacterManager::Instance()->getCharacterDistance();
	float jumpDistance = character->getJumpDistance(); // Distancia en X de un salto en diagonal
	float hitDistance = (character->getWidth() ) / 3; // Ancho de la hitbox de under_kick (es la de mayor alcance)
	string opponentMovement = opponent->getMovement();


	if ( rand() % 100 < chanceOfIdle) {
		this->setMovementBySituation("none");
	}

	// Si estaba lejos y saltó hacia adelante, repito el movimiento hasta llegar al oponente
	else if ( distance > hitDistance && ( lastAction == FIRST_PLAYER_AIR_PUNCH_R || lastAction == FIRST_PLAYER_AIR_LOW_kICK_R)) {
		this->setMovementBySituation("closingUp");
	}

	//Distancia lejana
	else if ( distance > jumpDistance ) {
		this->setMovementBySituation("farDistance");
	}

	//Distancia media
	else if( distance >= hitDistance) {
		this->setMovementBySituation("mediumDistance");
	}

	//Cerca
	else if (distance < hitDistance && opponentMovement == "block") {
		this->setMovementBySituation("closeDistanceBlocking");
		//this->setMovementBySituation("none");
	} else if (distance < hitDistance) {
		this->setMovementBySituation("closeDistance");
	}

}

InputCommand AIMovement::getMovementBySituation(std::string situation) {
	int random = rand()% this->movementMap[situation].size();
	return this->movementMap[situation].at(random);
}

void AIMovement::setMovementBySituation(std::string situation) {
	InputCommand movement = this->getMovementBySituation(situation);
	InputCommand OrientationFixedMovement = fixMovementOrientation(movement);
	InputControl::Instance()->setSecondPlayerMove(OrientationFixedMovement);
}


/* Corrige la orientación del movimiento según la convención elegida en AIMovement.h:
 * Movimientos _L son reemplazados según la orientación del pj por el movimiento hacia atrás
 * Movimientos _R son movimientos hacia adelante
 */
InputCommand AIMovement::fixMovementOrientation(InputCommand movement) {

	InputCommand fixedMovement = movement;
	if (movement != NO_INPUT ) lastAction = movement;
	if ( movement == FIRST_PLAYER_AIR_PUNCH_L && !character->getIsRightOriented()) {
		fixedMovement = FIRST_PLAYER_AIR_PUNCH_R;
	} else if ( movement == FIRST_PLAYER_AIR_LOW_kICK_L && !character->getIsRightOriented()) {
		fixedMovement = FIRST_PLAYER_AIR_LOW_kICK_R;
	} else if ( movement == FIRST_PLAYER_AIR_LOW_kICK_R && !character->getIsRightOriented()) {
		fixedMovement = FIRST_PLAYER_AIR_LOW_kICK_L;
	} else if ( movement == FIRST_PLAYER_AIR_PUNCH_R && !character->getIsRightOriented()) {
		fixedMovement = FIRST_PLAYER_AIR_PUNCH_L;
	}
	return fixedMovement;
}
