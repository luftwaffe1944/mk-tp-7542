/*
 * CollitionManager.h
 *
 *  Created on: 7/5/2015
 *      Author: diego
 */

#ifndef COLLITIONMANAGER_H_
#define COLLITIONMANAGER_H_

#include <iostream>
#include <map>
#include "Collitionable.h"
#include "CharacterManager.h"
using namespace std;

class CollitionManager {
public:
	static CollitionManager* Instance();
	virtual ~CollitionManager() {
			delete(cm_pInstance);
			cm_pInstance = NULL;
		}

	void resetInstance();
	void solveCollitions(vector<Collitionable*> objects);
	bool collitionEnabled;

private:
	static CollitionManager* cm_pInstance;
	CollitionManager();

};

#endif /* COLLITIONMANAGER_H_ */
