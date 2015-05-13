/*
 * CharacterManager.cpp
 *
 *  Created on: 12/5/2015
 *      Author: mauro
 */

#include "../headers/CharacterManager.h"

CharacterManager* CharacterManager::cm_pInstance = 0;

CharacterManager::CharacterManager() {
	// TODO Auto-generated constructor stub

}

CharacterManager* CharacterManager::Instance() {
	if (!cm_pInstance) {
		cm_pInstance = new CharacterManager();
		return cm_pInstance;
	} else {
		return cm_pInstance;
	}
}


void CharacterManager::solveMovesBeignHint(){

	Character* character2 = GameGUI::getInstance()->getCharacters().at(1);
	character2->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);

}

void CharacterManager::solveMovesBeignHint(DamageObject* actualObj, DamageObject* nextObj){

	Character* character1;

	Character* character2;

	if (actualObj->isCharacter()){
		character1 = dynamic_cast<Character*>(actualObj);
	}

	if (nextObj->isCharacter()){
		character2 = dynamic_cast<Character*>(nextObj);
	}


	if (character1->getMovement() == PUNCHING_HIGH_MOVEMENT){
		character2->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);
	}
	else if (character1->getMovement() == PUNCHING_LOW_MOVEMENT){
		character2->setMovement(BEING_HINT_STANCE_DOWN_MOVEMENT);
	}

//	Character* character2 = GameGUI::getInstance()->getCharacters().at(1);
//	character2->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);

}

