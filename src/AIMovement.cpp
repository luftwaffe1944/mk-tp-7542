/*
 * AIMovement.cpp
 *
 *  Created on: 27/5/2015
 *      Author: uje
 */

#include "../headers/AIMovement.h"

AIMovement* AIMovement::cm_pInstance = 0;


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

void AIMovement::setAIMovement() {

	Character* character = GameGUI::getInstance()->getCharacters().at(1);
	float distance = CharacterManager::Instance()->getCharacterDistance();
	float jumpDistance = character->getJumpDistance();
	//if (distance > 30) character->fire = true;
}
