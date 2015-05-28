/*
 * AIMovement.h
 *
 *  Created on: 27/5/2015
 *      Author: uje
 */

#ifndef AIMOVEMENT_H_
#define AIMOVEMENT_H_

#include "CharacterManager.h"

class AIMovement {
public:
	static AIMovement* Instance();
	virtual ~AIMovement() {
		delete(cm_pInstance);
		cm_pInstance = 0;
	}
	void setAIMovement();

private:
	AIMovement();
	static AIMovement* cm_pInstance;

};

#endif /* AIMOVEMENT_H_ */
