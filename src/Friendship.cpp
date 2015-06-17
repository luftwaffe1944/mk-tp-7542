/*
 * Friendship.cpp
 *
 *  Created on: 15/6/2015
 *      Author: mauro
 */

#include "../headers/Friendship.h"
#include "../headers/SoundManager.h"

Friendship::Friendship(): FinishMove() {
	// TODO Auto-generated constructor stub

}


Friendship::~Friendship() {
	// TODO Auto-generated destructor stub
}

void Friendship::onPreFinish(std::string name){
	SoundManager::Instance()->playSound("pre_friendship", 0);
}

void Friendship::onPostFinish(std::string name){

}

void Friendship::onFinish(std::string name){

}

int Friendship::getID(){
	return 2;
}
