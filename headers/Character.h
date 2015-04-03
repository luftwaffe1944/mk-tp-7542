/*
 * Character.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_
#include <string>
#include "SDLObjectGUI.h"


class Character : public SDLObjectGUI {
private:
	int width;
	int height;
	int zindex;
	std::string orientation;
public:
	Character();
	Character(int width, int height, int zindex, std::string orientation);
	virtual ~Character();
	Character(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

};

#endif /* CHARACTER_H_ */
