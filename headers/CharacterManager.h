/*
 * CharacterManager.h
 *
 *  Created on: 12/5/2015
 *      Author: mauro
 */

#ifndef CHARACTERMANAGER_H_
#define CHARACTERMANAGER_H_

#include "GameGUI.h"
#include "LayerManager.h"

using namespace std;

class CharacterManager {
public:
	static CharacterManager* Instance();
	virtual ~CharacterManager() {
		delete(cm_pInstance);
		cm_pInstance = 0;
	}

	void solveMovesBeignHint();
	void solveMovesBeignHint(DamageObject* actualObj, DamageObject* nextObj);

private:
	CharacterManager();
	static CharacterManager* cm_pInstance;
};

#endif /* CHARACTERMANAGER_H_ */
