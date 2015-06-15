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

Fatality::Fatality(): FinishMove() {
	// TODO Auto-generated constructor stub

}


Fatality::~Fatality() {
	// TODO Auto-generated destructor stub
}

void Fatality::onPreFinish(std::string name){

	SoundManager::Instance()->playSound("pre_fatality", 0);
	Character* victim = getVictim(name);
	cout << "victima: " << victim->getName() << endl;
	if (name == "subzero") {
		victim->setMovement(LAZY_MOVEMENT);
	}
	else {
		cout << "burning: " << victim->getName() << endl;
		victim->setMovement(BURNING_MOVEMENT);
		victim->setCurrentSprite();
		victim->completeMovement();
	}

}

void Fatality::onPostFinish(std::string name){

	Character* victim = getVictim(name);
	if (name == "scorpion") {
		SoundManager::Instance()->playSoundOnce("fatality_voice", 0);
	}

}

void Fatality::onFinish(std::string name){

	Character* victim = getVictim(name);
	if (name == "scorpion") {
		SoundManager::Instance()->playSoundOnce("scream", 0);
	}

}

Character* getVictim(std::string name){

	Character* character = GameGUI::getInstance()->getCharacters()[0];
	if (character->getName() == name){
		return GameGUI::getInstance()->getCharacters()[1];
	}
	return character;

}
