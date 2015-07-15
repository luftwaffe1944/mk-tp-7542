/*
 * Friendship.cpp
 *
 *  Created on: 15/6/2015
 *      Author: mauro
 */

#include "../headers/Friendship.h"
#include "../headers/SoundManager.h"

Character* getVictim(std::string name);
Character* getWinner(std::string name);

Friendship::Friendship(): FinishMove() {
	// TODO Auto-generated constructor stub

}


Friendship::~Friendship() {
	// TODO Auto-generated destructor stub
}

void sleepSafe(int limit);

void Friendship::onPreFinish(std::string name){
	SoundManager::Instance()->playSoundOnce("pre_friendship", 0);
	SDL_Delay(1000);
	Character* victim = getVictim(name);
	Character* winner = getWinner(name);

	winner->setMovement(FRIENDSHIP_MOVEMENT);
	winner->setCurrentSprite();
	winner->isFriendship = true;
}

void Friendship::onFinish(std::string name){
	Character* victim = getVictim(name);
	victim->setMovement(FALLING_MOVEMENT);
	victim->isFalling = true;
	victim->setCurrentSprite();
	SoundManager::Instance()->playSoundOnce("friendship", 0);
}

void Friendship::onPostFinish(std::string name){
	SDL_Delay(2000);
	SoundManager::Instance()->playSoundOnce("friendship_voice", 0);
}

int Friendship::getID(){
	return 2;
}
