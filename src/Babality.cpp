/*
 * Babality.cpp
 *
 *  Created on: 15/6/2015
 *      Author: mauro
 */

#include "../headers/Babality.h"
#include "../headers/GameGUI.h"

Character* getVictim(std::string name);
Character* getWinner(std::string name);

Babality::Babality(): FinishMove() {
	// TODO Auto-generated constructor stub

}

Babality::~Babality() {
	// TODO Auto-generated destructor stub
}

void sleepSafe(int limit){
	for (int i = 0; i < limit; i++){cout<<"";}
}

void Babality::onPreFinish(std::string name){
	SoundManager::Instance()->playSoundOnce("pre_babality", 0);
	sleepSafe(90000000);
	Character* victim = getVictim(name);
	Character* winner = getWinner(name);

	winner->isBabality = true;
	victim->setMovement(BABALITY_MOVEMENT);
	victim->isLazy = false;
	victim->setCurrentSprite();
	victim->isBabality = true;
}

void Babality::onFinish(std::string name){
	Character* winner = getWinner(name);
	SoundManager::Instance()->playSoundOnce("baby_cry", 0);
	winner->setMovement(VICTORY_MOVEMENT);
	winner->setCurrentSprite();
	winner->isVictory = true;

}

void Babality::onPostFinish(std::string name){
	sleepSafe(90000000);
	SoundManager::Instance()->playSoundOnce("post_babality", 0);
	sleepSafe(90000000);
	SoundManager::Instance()->playSoundOnce("babality_voice", 0);

}


int Babality::getID(){
	return 1;
}


Character* getVictim(std::string name){

	Character* character = GameGUI::getInstance()->getCharacters()[0];
	if (character->getName() == name){
		return GameGUI::getInstance()->getCharacters()[1];
	}
	return character;

}

Character* getWinner(std::string name){

	Character* character = GameGUI::getInstance()->getCharacters()[0];
	if (character->getName() == name){
		return character;
	}
	return GameGUI::getInstance()->getCharacters()[1];

}

