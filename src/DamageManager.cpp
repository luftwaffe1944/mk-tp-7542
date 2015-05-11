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

bool DamageManager::IsObjectAttacking(DamageObject* obj){
	string objectMovement = obj->getDOMovement();
	bool isOjectAttacking = (objectMovement == PUNCHING_HIGH_MOVEMENT)||(objectMovement == PUNCHING_LOW_MOVEMENT)||(objectMovement==LOW_KICK_MOVEMENT)||(objectMovement==HIGH_KICK_MOVEMENT);
	return isOjectAttacking;
}

bool DamageManager::IsObjectBlocking(DamageObject* obj){
	string objetMovement = obj->getDOMovement();
	bool isOjectBlocking =  false;//(objetMovement == PUNCHING_HIGH_MOVEMENT) || (objetMovement == PUNCHING_LOW_MOVEMENT);
	return isOjectBlocking;
}

float DamageManager::getDamageToDo(DamageObject* obj){
	string objectMovement = obj->getDOMovement();
	float damage = 0;
    if (objectMovement==PUNCHING_HIGH_MOVEMENT){
    	damage = 0.01f;
    }else if (objectMovement==PUNCHING_LOW_MOVEMENT){
    	damage = 0.005f;
    }else if (objectMovement==LOW_KICK_MOVEMENT){
    	damage = 0.01f;
    }else if (objectMovement==HIGH_KICK_MOVEMENT){
    	damage = 0.02f;
    }
    return damage;
}

void DamageManager::solveDamage(DamageObject* firstObject, DamageObject* secondObject){

	if ((this->IsObjectAttacking(firstObject)) &&  !(this->IsObjectBlocking(secondObject)) && !(this->IsObjectAttacking(secondObject))){
		secondObject->setDamage(this->getDamageToDo(firstObject));
	}
	if ((this->IsObjectAttacking(secondObject)) &&  !(this->IsObjectBlocking(firstObject)) && !(this->IsObjectAttacking(firstObject))){
		firstObject->setDamage(this->getDamageToDo(secondObject));
	}
}



