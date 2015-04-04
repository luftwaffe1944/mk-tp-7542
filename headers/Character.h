/*
 * Character.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_
#include <string>


class Character {
private:
	int name;
	int width;
	int height;
	int zindex;
	std::string orientation;
public:
	Character();
	Character(int width, int height, int zindex, std::string orientation);
	Character(int name, int width, int height, int zindex, std::string orientation);
	virtual ~Character();
};

#endif /* CHARACTER_H_ */
