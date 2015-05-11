/*
 * CollitionManager.cpp
 *
 *  Created on: 7/5/2015
 *      Author: diego
 */

#include "../headers/DamageManager.h"
#include "../headers/Log.h"

DamageManager* DamageManager::dm_pInstance = NULL;

DamageManager* DamageManager::Instance() {
	if (!dm_pInstance) {
		dm_pInstance = new DamageManager();
		return dm_pInstance;
	} else {
		return dm_pInstance;
	}
}
DamageManager::DamageManager(){
}

void DamageManager::solveDamage(DamageObject* firstObject, DamageObject* secondObject){

	if ((firstObject->getDOMovement() == PUNCHING_HIGH_MOVEMENT) && (secondObject->getDOMovement() == STANCE)){
		secondObject->setDamage(0.01f);
	}
}



