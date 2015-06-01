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

void AIMovement::solveAIMovement() {

	Character* character = GameGUI::getInstance()->getCharacters().at(1);
	Character* opponent = GameGUI::getInstance()->getCharacters().at(0);

	float distance = CharacterManager::Instance()->getCharacterDistance();
	float jumpDistance = character->getJumpDistance();
	float hitDistance = (character->getWidth() ) / 3; //ancho de la hitbox de under_kick (es la de mayor alcance)
	string opponentMovement = opponent->getMovement();


	//InputControl::Instance()->setSecondPlayerMove(FIRST_PgLAYER_HIGH_KICK);

	//Distancia lejana
	if ( distance > jumpDistance) {
//		std::cout << rand() << std::endl;
		this->setMovementBySituation("farDistance");
	}

	//Distancia media
	else if( distance > hitDistance) {

	}

	//Cerca
	else {
		this->setMovementBySituation("closeDistance");
		//this->setMovementBySituation("none");
	}

}

InputCommand AIMovement::getMovementBySituation(std::string situation) {
	int random = rand()% this->movementMap[situation].size();
	return this->movementMap[situation].at(random);
}

void AIMovement::setMovementBySituation(std::string situation) {
	//situation = "lejos";
	InputCommand movement = this->getMovementBySituation(situation);
	InputControl::Instance()->setSecondPlayerMove(movement);
}
