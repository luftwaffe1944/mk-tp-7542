/*
 * DamageManager.h
 *
 *
 *      Author: diego
 */

#ifndef DAMAGEMANAGER_H_
#define DAMAGEMANAGER_H_

#include <iostream>
#include <map>
#include "Collitionable.h"
#include "Character.h"
using namespace std;

class DamageManager {
public:
	static DamageManager* Instance();
	virtual ~DamageManager() {
			delete(dm_pInstance);
			dm_pInstance = NULL;
	}

	void solveDamage(DamageObject* firstObject, DamageObject* secondObject);
	bool IsObjectAttacking(DamageObject* obj);
	bool IsObjectBlocking(DamageObject* obj);
	float getDamageToDo(DamageObject* obj);

private:
	static DamageManager* dm_pInstance;
	DamageManager();

};

#endif /* DAMAGEMANAGER_H_ */
