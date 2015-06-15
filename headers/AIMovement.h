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
	std::map<std::string,std::vector<InputCommand>> movementMap =
		{
			{
				"farDistance",
				{
					FIRST_PLAYER_AIR_LOW_kICK_L,
					FIRST_PLAYER_AIR_LOW_kICK_R,
					FIRST_PLAYER_AIR_PUNCH_L,
					FIRST_PLAYER_AIR_PUNCH_R,
					FIRST_PLAYER_FIRE
				}
			},
			{
				"mediumDistance",
				{
					FIRST_PLAYER_AIR_LOW_kICK_L,
					FIRST_PLAYER_AIR_LOW_kICK_R,
					FIRST_PLAYER_AIR_PUNCH_L,
					FIRST_PLAYER_AIR_PUNCH_R,
					FIRST_PLAYER_AIR_PUNCH,
					FIRST_PLAYER_AIR_HIGH_kICK,
					FIRST_PLAYER_FIRE

				}
			},
			{
				"kickDistance",
				{
					FIRST_PLAYER_BLOCK,
					FIRST_PLAYER_LOW_KICK,
					FIRST_PLAYER_HIGH_KICK,
					FIRST_PLAYER_MOVE_RIGHT,
					FIRST_PLAYER_UNDER_KICK,
					FIRST_PLAYER_SUPER_kICK,
					FIRST_PLAYER_AIR_PUNCH_L,
					FIRST_PLAYER_AIR_LOW_kICK_L,
					FIRST_PLAYER_MOVE_RIGHT
				}
			},
			{
				"punchDistance",
				{
						FIRST_PLAYER_DUCK_HIGH_kICK,
						FIRST_PLAYER_DUCK_LOW_kICK,
						FIRST_PLAYER_UPPERCUT,
						FIRST_PLAYER_HI_PUNCH,
						FIRST_PLAYER_LO_PUNCH,
						FIRST_PLAYER_DUCK_PUNCH,
						FIRST_PLAYER_AIR_PUNCH,
						FIRST_PLAYER_AIR_HIGH_kICK,
						FIRST_PLAYER_BLOCK,
						FIRST_PLAYER_LOW_KICK,
						FIRST_PLAYER_HIGH_KICK,
						FIRST_PLAYER_UNDER_KICK,
						FIRST_PLAYER_DUCK_HIGH_kICK,
						FIRST_PLAYER_SUPER_kICK,
						FIRST_PLAYER_AIR_PUNCH_L,
						FIRST_PLAYER_AIR_LOW_kICK_L
				}
			},
			{
				"underKickDistance",
				{
						FIRST_PLAYER_MOVE_RIGHT,
						FIRST_PLAYER_UNDER_KICK,
				}
			},
			{
				"closeDistanceBlocking",
				{
					FIRST_PLAYER_UNDER_KICK
				}
			},
			{
				"closingUp",
				{
					FIRST_PLAYER_AIR_LOW_kICK_R,
					FIRST_PLAYER_AIR_PUNCH_R
				}
			},
			{
				"none",
				{
					NO_INPUT
				}
			}
		};
};

#endif /* AIMOVEMENT_H_ */
