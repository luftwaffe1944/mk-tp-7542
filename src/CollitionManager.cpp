/*
 * CollitionManager.cpp
 *
 *  Created on: 7/5/2015
 *      Author: diego
 */

#include "../headers/CollitionManager.h"
#include "../headers/Log.h"

CollitionManager* CollitionManager::t_pInstance = NULL;
CollitionManager* CollitionManager::Instance() {
	if (!t_pInstance) {
		t_pInstance = new CollitionManager();
		return t_pInstance;
	} else {
		return t_pInstance;
	}
}

CollitionManager::CollitionManager() {

}

void CollitionManager::solveCollitions(){

}





