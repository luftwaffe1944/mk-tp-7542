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
	void solveAIMovement();
	void setMovementBySituation(std::string movement);
	InputCommand getMovementBySituation(std::string situation);
private:
	AIMovement();
	static AIMovement* cm_pInstance;
	//std::map< std::string, std::vector<std::string> > movementMap = { "farDistance",{"block"} };
	std::map<std::string,std::vector<InputCommand>> movementMap =
		{
			{
				"farDistance",
				{FIRST_PLAYER_BLOCK}
			},
			{
				"mediumDistanace",
				{}
			},
			{
				"closeDistance",
				{
					FIRST_PLAYER_BLOCK,
					FIRST_PLAYER_HI_PUNCH,
					FIRST_PLAYER_LO_PUNCH,
					FIRST_PLAYER_DUCK_PUNCH,
					FIRST_PLAYER_DUCK_FIRE,
					FIRST_PLAYER_UPPERCUT,
					FIRST_PLAYER_LOW_KICK,
					FIRST_PLAYER_HIGH_KICK,
					FIRST_PLAYER_DUCK_LOW_kICK,
					FIRST_PLAYER_DUCK_HIGH_kICK,
					FIRST_PLAYER_SUPER_kICK
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
