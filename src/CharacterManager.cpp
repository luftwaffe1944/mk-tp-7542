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
	if ((actualObj->isCharacter()) && (nextObj->isCharacter())){
		//GOLPES CHARACTER 1
		if (character1->getMovement() == PUNCHING_HIGH_MOVEMENT || character1->getMovement() == HIGH_KICK_MOVEMENT
				|| character1->getMovement() == AIR_PUNCH_MOVEMENT){
			character2->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);
		}
		else if (character1->getMovement() == PUNCHING_LOW_MOVEMENT || character1->getMovement() == LOW_KICK_MOVEMENT
				|| character1->getMovement() == DUCK_HIGH_KICK_MOVEMENT || character1->getMovement() == DUCK_LOW_KICK_MOVEMENT
				|| character1->getMovement() == PUNCHING_DUCK_MOVEMENT || character1->getMovement() == PUNCHING_HIGH_MOVEMENT ){
			character2->setMovement(BEING_HINT_STANCE_DOWN_MOVEMENT);
		}
		else if (character1->getMovement() == UNDER_KICK_MOVEMENT){
			character2->setMovement(BEING_HINT_FALLING_UNDER_KICK_MOVEMENT);
		}

		else if (character1->getMovement() == SUPER_KICK_MOVEMENT || character1->getMovement() == AIR_HIGH_kICK_MOVEMENT
				|| character1->getMovement() == AIR_LOW_kICK_MOVEMENT){
			character2->setMovement(HINT_FLYING_MOVEMENT);
		}

		else if (character1->getMovement() == UPPERCUT_MOVEMENT){
			character2->setMovement(HINT_FLYING_UPPER_MOVEMENT);
		}

		//GOLPES CHARACTER 2
		if (character2->getMovement() == PUNCHING_HIGH_MOVEMENT || character2->getMovement() == HIGH_KICK_MOVEMENT
				|| character2->getMovement() == AIR_PUNCH_MOVEMENT){
			character1->setMovement(BEING_HINT_STANCE_UP_MOVEMENT);
		}
		else if (character2->getMovement() == PUNCHING_LOW_MOVEMENT || character2->getMovement() == LOW_KICK_MOVEMENT
				|| character2->getMovement() == DUCK_HIGH_KICK_MOVEMENT || character2->getMovement() == DUCK_LOW_KICK_MOVEMENT
				|| character2->getMovement() == PUNCHING_DUCK_MOVEMENT || character2->getMovement() == PUNCHING_HIGH_MOVEMENT ){
			character1->setMovement(BEING_HINT_STANCE_DOWN_MOVEMENT);
		}
		else if (character2->getMovement() == UNDER_KICK_MOVEMENT){
			character1->setMovement(BEING_HINT_FALLING_UNDER_KICK_MOVEMENT);
		}

		else if (character2->getMovement() == SUPER_KICK_MOVEMENT || character2->getMovement() == AIR_HIGH_kICK_MOVEMENT
				|| character2->getMovement() == AIR_LOW_kICK_MOVEMENT){
			character1->setMovement(HINT_FLYING_MOVEMENT);
		}

		else if (character2->getMovement() == UPPERCUT_MOVEMENT){
			character1->setMovement(HINT_FLYING_UPPER_MOVEMENT);
		}

		//DON'T OVERLAP LOGIC FOR CHARACTER 2
		//FOR WALKING
		if ( character2->getMovement() == WALKING_LEFT_MOVEMENT && !character2->getIsRightOriented() ) {
			// stop walking
			character1->setPositionX(character1->getPositionX() - FRONTAL_LAYER_SPEED/2 * character1->getRatioX());
			character2->setPositionX(character1->posXBox);
		}

		if (character2->getMovement() == WALKING_RIGHT_MOVEMENT && character2->getIsRightOriented()) {
			character1->setPositionX(character1->getPositionX() + FRONTAL_LAYER_SPEED/2 * character1->getRatioX());
			character2->setPositionX(character1->posXBox - character1->widthBox*2);
		}


		//FOR JUMPING
		if ( character2->getMovement() == JUMPING_LEFT_MOVEMENT && !character2->getIsRightOriented() ) {
			//TODO: review if the jump is too close
			if ( ((character1->posYBox - character2->posYBox) < 30*character2->getRatioY())) {
				character2->setPositionX(character1->posXBox);
			} else {
				character2->setPositionX(character1->posXBox - character1->widthBox*2);
			}
		}

		if ( character2->getMovement() == JUMPING_RIGHT_MOVEMENT && character2->getIsRightOriented() ) {
			if ( ((character1->posYBox - character2->posYBox) < 30*character2->getRatioY())) {
				character2->setPositionX(character1->posXBox);
			} else {
				character2->setPositionX(character1->posXBox);
			}
		}


		//FOR AIR KICKING
		if ( character2->getIsKickingAirLowLeft() && !character2->getIsRightOriented() ) {
			//TODO: review if the jump is too close
			character2->setPositionX(character1->posXBox);
		}

		if ( character2->getIsKickingAirLowRight() && character2->getIsRightOriented() ) {
			character2->setPositionX(character1->posXBox - character1->widthBox*2);
		}


		//FOR AIR PUNCHING
		if ( character2->getIsAirPunchingLeft() && !character2->getIsRightOriented() ) {
			//TODO: review if the jump is too close
			character2->setPositionX(character1->posXBox);
		}

		if ( character2->getIsAirPunchingRight() && character2->getIsRightOriented() ) {
			character2->setPositionX(character1->posXBox - character1->widthBox*2);
		}

		//----------------------------------------------------------------------------------------------
		//DON'T OVERLAP LOGIC FOR CHARACTER 1
		//FOR WALKING
		if ( character1->getMovement() == WALKING_LEFT_MOVEMENT && !character1->getIsRightOriented() ) {
			// stop walking
			character2->setPositionX(character2->getPositionX() - FRONTAL_LAYER_SPEED/2 * character2->getRatioX());
			character1->setPositionX(character2->posXBox);
		}

		if (character1->getMovement() == WALKING_RIGHT_MOVEMENT && character1->getIsRightOriented()) {
			character2->setPositionX(character2->getPositionX() + FRONTAL_LAYER_SPEED/2 * character2->getRatioX());
			character1->setPositionX(character2->posXBox - character2->widthBox*2);
		}


		//FOR JUMPING
		if ( character1->getMovement() == JUMPING_LEFT_MOVEMENT && !character1->getIsRightOriented() ) {
			//TODO: review if the jump is too close
			if ( ((character2->posYBox - character1->posYBox) < 30*character1->getRatioY())) {
				character1->setPositionX(character2->posXBox);
			} else {
				character1->setPositionX(character2->posXBox - character2->widthBox*2);
			}
		}

		if ( character1->getMovement() == JUMPING_RIGHT_MOVEMENT && character1->getIsRightOriented() ) {
			if ( ((character2->posYBox - character1->posYBox) < 30*character1->getRatioY())) {
				character1->setPositionX(character2->posXBox);
			} else {
				character1->setPositionX(character2->posXBox);
			}
		}


		//FOR AIR KICKING
		if ( character1->getIsKickingAirLowLeft() && !character1->getIsRightOriented() ) {
			//TODO: review if the jump is too close
			character1->setPositionX(character2->posXBox);
		}

		if ( character1->getIsKickingAirLowRight() && character1->getIsRightOriented() ) {
			character1->setPositionX(character2->posXBox - character2->widthBox*2);
		}


		//FOR AIR PUNCHING
		if ( character1->getIsAirPunchingLeft() && !character1->getIsRightOriented() ) {
			//TODO: review if the jump is too close
			character1->setPositionX(character2->posXBox);
		}

		if ( character1->getIsAirPunchingRight() && character1->getIsRightOriented() ) {
			character1->setPositionX(character2->posXBox - character2->widthBox*2);
		}
	}

}

