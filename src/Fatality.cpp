/*
 * Fatality.cpp
 *
 *  Created on: 15/6/2015
 *      Author: mauro
 */

#include "../headers/Fatality.h"
#include "../headers/Character.h"
#include "../headers/GameGUI.h"

Character* getVictim(std::string name);
Character* getWinner(std::string name);

Fatality::Fatality(): FinishMove() {
	// TODO Auto-generated constructor stub

}


Fatality::~Fatality() {
	// TODO Auto-generated destructor stub
}

void Fatality::onPreFinish(std::string name){

	SoundManager::Instance()->playSound("pre_fatality", 0);
	Character* victim = getVictim(name);
	Character* winner = getWinner(name);
	if (name == "subzero") {
		victim->setMovement(LAZY_MOVEMENT);
		winner->setMovement(REPTILE_MOVEMENT);
		winner->setCurrentSprite();
		winner->isReptile = true;
	}
	else {
		victim->setMovement(BURNING_MOVEMENT);
		victim->setCurrentSprite();
		victim->completeMovement();

		winner->setMovement(VICTORY_MOVEMENT);
		winner->setCurrentSprite();
		winner->isVictory = true;
	}

}

void Fatality::onFinish(std::string name){

	Character* victim = getVictim(name);
	if (name == "scorpion") {
		SoundManager::Instance()->playSoundOnce("scream", 0);
	}else {
		victim->setMovement(HEADLESS_BLOOD_MOVEMENT);
		victim->isLazy = false;
		victim->setCurrentSprite();
		victim->completeMovement();
		SoundManager::Instance()->playSoundOnce("headless_blood", 5);
	}

}

void Fatality::onPostFinish(std::string name){

	Character* victim = getVictim(name);
	Character* winner = getWinner(name);

	if (name == "scorpion") {
		SoundManager::Instance()->playSoundOnce("fatality_voice", 0);
	}

	else {
		victim->setMovement(HEADLESS_MOVEMENT);
		victim->isLazy = false;
		victim->setCurrentSprite();
		victim->completeMovement();
		SoundManager::Instance()->playSoundOnce("fatality_voice", 0);
		winner->setMovement(VICTORY_MOVEMENT);
		winner->setCurrentSprite();
		winner->isVictory = true;
		victim->isHeadless = true;
	}

}

int Fatality::getID(){
	return 0;
}

