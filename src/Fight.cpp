/*
 * Fight.cpp
 *
 *  Created on: May 8, 2015
 *      Author: nicolas.m.outeda
 */

#include "../headers/Fight.h"

Fight::Fight() {
	// TODO Auto-generated constructor stub

}

Fight::~Fight() {
	// TODO Auto-generated destructor stub
}

Character* Fight::getFighterOne(){
	return this->fighterOne;
}

void Fight::setFighterOne(Character* fighterOne){
	this->fighterOne = fighterOne;
}

Character* Fight::getFighterTwo(){
	return this->fighterTwo;
}

void Fight::setFighterTwo(Character* fighterTwo){
	this->fighterTwo = fighterTwo;
}

