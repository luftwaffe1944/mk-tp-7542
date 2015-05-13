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
	bool isOjectAttacking = false;
	isOjectAttacking = (objectMovement == PUNCHING_HIGH_MOVEMENT)||(objectMovement == PUNCHING_LOW_MOVEMENT)||(objectMovement==LOW_KICK_MOVEMENT)||(objectMovement==HIGH_KICK_MOVEMENT);
	isOjectAttacking = isOjectAttacking||(objectMovement == DUCK_HIGH_KICK_MOVEMENT)||(objectMovement == DUCK_LOW_KICK_MOVEMENT)||(objectMovement==PUNCHING_DUCK_MOVEMENT)||(objectMovement==UPPERCUT_MOVEMENT);
	isOjectAttacking = isOjectAttacking||(objectMovement == SUPER_KICK_MOVEMENT)||(objectMovement == UNDER_KICK_MOVEMENT);
	isOjectAttacking = isOjectAttacking||(objectMovement == AIR_HIGH_kICK_MOVEMENT)||(objectMovement == AIR_LOW_kICK_MOVEMENT);
	isOjectAttacking = isOjectAttacking||(objectMovement == AIR_PUNCH_MOVEMENT);
	return isOjectAttacking;
}


bool DamageManager::IsObjectBlocking(DamageObject* obj){
	string objetMovement = obj->getDOMovement();
	bool isObjectBlocking = false;
	 isObjectBlocking =  (objetMovement == BLOCK_MOVEMENT) || (objetMovement == DUCK_BLOCK_MOVEMENT);
	return isObjectBlocking;
}

float DamageManager::getDamageToDo(DamageObject* obj){
	string objectMovement = obj->getDOMovement();
	float damage = 0;
    if (objectMovement==PUNCHING_HIGH_MOVEMENT){ //piña alta
    	damage = 0.01f;
    }else if (objectMovement==PUNCHING_LOW_MOVEMENT){ //piña baja
    	damage = 0.005f;
    }else if (objectMovement==LOW_KICK_MOVEMENT){ //patada baja
    	damage = 0.01f;
    }else if (objectMovement==HIGH_KICK_MOVEMENT){ //patada alta
    	damage = 0.02f;
    }else if (objectMovement==DUCK_HIGH_KICK_MOVEMENT){ //patada alta agachado
        	damage = 0.015;
    }else if (objectMovement==DUCK_LOW_KICK_MOVEMENT){ //patada baja agachado
       	damage = 0.01;
    }else if (objectMovement==PUNCHING_DUCK_MOVEMENT){ //piña agachado
      	damage = 0.01;
    }else if (objectMovement==UPPERCUT_MOVEMENT){ //gancho
       	damage = 0.04;
    }else if (objectMovement == SUPER_KICK_MOVEMENT){ //patada alta giratoria
    	damage = 0.035;
	}else if (objectMovement == UNDER_KICK_MOVEMENT){ //patada baja giratoria
		damage = 0.03;
	}else if (objectMovement == AIR_HIGH_kICK_MOVEMENT){
		damage = 0.03f;
	}else if (objectMovement == AIR_LOW_kICK_MOVEMENT){
		damage = 0.02f;
	}else if (objectMovement == AIR_PUNCH_MOVEMENT){
		damage = 0.02f;
	}
    return damage;
}

void DamageManager::solveDamage(DamageObject* firstObject, DamageObject* secondObject){

	if (firstObject->isCharacter() && secondObject->isCharacter()){
		if ((this->IsObjectAttacking(firstObject)) &&  !(this->IsObjectBlocking(secondObject)) && !(this->IsObjectAttacking(secondObject))){
			secondObject->setDamage(this->getDamageToDo(firstObject));
		}
		if ((this->IsObjectAttacking(secondObject)) &&  !(this->IsObjectBlocking(firstObject)) && !(this->IsObjectAttacking(firstObject))){
			firstObject->setDamage(this->getDamageToDo(secondObject));
		}
	}else if (firstObject->isWeapon){
		firstObject->setDamage(1.0f);
		secondObject->setDamage(0.02f);
		cout << "first" << endl;
	}else if (secondObject->isWeapon) {
		firstObject->setDamage(0.02f);
		secondObject->setDamage(1.0f);
		cout << "second" << endl;
	}
}



