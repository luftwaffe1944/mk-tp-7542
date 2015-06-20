/*
 * AIMovement.h
 *
 *  Created on: 27/5/2015
 *      Author: uje
 */

#ifndef AIMOVEMENT_H_
#define AIMOVEMENT_H_

#include "CharacterManager.h"
#include "Constants.h"


class AIMovement {
public:
	static AIMovement* Instance();
	virtual ~AIMovement() {
		delete(cm_pInstance);
		cm_pInstance = 0;
	}
	bool isInitialized = false;
	void init();
	void solveAIMovement();
	void setMovementBySituation(std::string situation);
	InputCommand getMovementBySituation(std::string situation);
	InputCommand fixMovementOrientation(InputCommand movement);
	void clean();
private:
	AIMovement();
	static AIMovement* cm_pInstance;
	Character* character;
	Character* opponent;
	InputCommand lastAction;
	int chanceOfIdle = IDLE_CHANCE;
	/* Array para la toma de decisiones
	 * Sé que es horrible pero para ahorrar validaciones de orientación en los movimientos _R y _L, uso como convención _R
	 * como movimiento hacia adelante y _L como movimiento hacia atrás
	 */

	std::map<std::string,std::vector<InputCommand> > movementMap;
	bool createMovementMap(std::map<std::string,std::vector<InputCommand> > &aMovementMap) {

		aMovementMap["farDistance"].push_back(FIRST_PLAYER_AIR_LOW_kICK_L);
		aMovementMap["farDistance"].push_back(FIRST_PLAYER_AIR_LOW_kICK_R);
		aMovementMap["farDistance"].push_back(FIRST_PLAYER_AIR_PUNCH_L);
		aMovementMap["farDistance"].push_back(FIRST_PLAYER_AIR_PUNCH_R);
		aMovementMap["farDistance"].push_back(FIRST_PLAYER_FIRE);

		aMovementMap["mediumDistance"].push_back(FIRST_PLAYER_AIR_LOW_kICK_L);
		aMovementMap["mediumDistance"].push_back(FIRST_PLAYER_AIR_LOW_kICK_R);
		aMovementMap["mediumDistance"].push_back(FIRST_PLAYER_AIR_PUNCH_L);
		aMovementMap["mediumDistance"].push_back(FIRST_PLAYER_AIR_PUNCH_R);
		aMovementMap["mediumDistance"].push_back(FIRST_PLAYER_AIR_PUNCH);
		aMovementMap["mediumDistance"].push_back(FIRST_PLAYER_AIR_HIGH_kICK);
		aMovementMap["mediumDistance"].push_back(FIRST_PLAYER_FIRE);

		aMovementMap["kickDistance"].push_back(FIRST_PLAYER_BLOCK);
		aMovementMap["kickDistance"].push_back(FIRST_PLAYER_LOW_KICK);
		aMovementMap["kickDistance"].push_back(FIRST_PLAYER_HIGH_KICK);
		aMovementMap["kickDistance"].push_back(FIRST_PLAYER_MOVE_RIGHT);
		aMovementMap["kickDistance"].push_back(FIRST_PLAYER_UNDER_KICK);
		aMovementMap["kickDistance"].push_back(FIRST_PLAYER_SUPER_kICK);
		aMovementMap["kickDistance"].push_back(FIRST_PLAYER_AIR_PUNCH_L);
		aMovementMap["kickDistance"].push_back(FIRST_PLAYER_AIR_LOW_kICK_L);
		aMovementMap["kickDistance"].push_back(FIRST_PLAYER_MOVE_RIGHT);



		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_DUCK_HIGH_kICK);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_DUCK_LOW_kICK);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_UPPERCUT);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_HI_PUNCH);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_LO_PUNCH);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_DUCK_PUNCH);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_AIR_PUNCH);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_AIR_HIGH_kICK);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_BLOCK);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_LOW_KICK);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_HIGH_KICK);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_UNDER_KICK);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_DUCK_HIGH_kICK);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_SUPER_kICK);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_AIR_PUNCH_L);
		aMovementMap["punchDistance"].push_back(FIRST_PLAYER_AIR_LOW_kICK_L);


		aMovementMap["underKickDistance"].push_back(FIRST_PLAYER_MOVE_RIGHT);
		aMovementMap["underKickDistance"].push_back(FIRST_PLAYER_UNDER_KICK);

		aMovementMap["closeDistanceBlocking"].push_back(FIRST_PLAYER_UNDER_KICK);
		aMovementMap["closingUp"].push_back(FIRST_PLAYER_AIR_LOW_kICK_R);
		aMovementMap["closingUp"].push_back(FIRST_PLAYER_AIR_PUNCH_R);
		aMovementMap["none"].push_back(NO_INPUT);

		return true;

	}
};

#endif /* AIMOVEMENT_H_ */
