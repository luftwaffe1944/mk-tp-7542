/*
 * Character.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

class Character {
private:
	int width;
	int height;
	int zindex;
public:
	Character();
	Character(int width, int height, int zindex);
	virtual ~Character();
};

#endif /* CHARACTER_H_ */
