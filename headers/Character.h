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
#include <SDL.h>


class Character : public SDLObjectGUI {
private:
//	std::string name;
	//int width;
//	int height;
//	int zindex;
	std::string orientation;
public:
	Character();
//	Character(int width, int height, int zindex, std::string orientation);
//	Character(std::string name, int width, int height, int zindex, std::string orientation);
	bool load(SDL_Renderer* render);
	void render(SDL_Renderer* render);
	virtual ~Character();
	Character(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	int getWidth();
	int getPosX();

};

#endif /* CHARACTER_H_ */
