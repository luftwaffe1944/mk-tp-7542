/*
 * Character.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */


#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
using namespace std;

class Character {
private:
	int width;
	int height;
	int zindex;
	std::string spriteWalk;
	std::string spriteStand;
	std::string activeSprite;
	int frame;
public:
	Character();
	Character(int width, int height, int zindex);
	Character(int width, int height, int zindex, std::string spriteWalk,std::string spriteStand);
	virtual ~Character();
	std::string getActiveSprite();
	int h();
	int w();
	void setActiveSprite(std::string active);
	int getNextFrame();
};

#endif /* CHARACTER_H_ */
