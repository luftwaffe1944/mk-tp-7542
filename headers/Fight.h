/*
 * Fight.h
 *
 *  Created on: May 8, 2015
 *      Author: nicolas.m.outeda
 */

#ifndef FIGHT_H_
#define FIGHT_H_
#include "Character.h"

class Fight {

private:
	Character* fighterOne;
	Character* fighterTwo;


public:
	Fight();
	virtual ~Fight();
	Character* getFighterOne();
	void setFighterOne(Character* fighterOne);
	Character* getFighterTwo();
	void setFighterTwo(Character* fighterTwo);
};

#endif /* FIGHT_H_ */
