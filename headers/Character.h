/*
 * Character.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_
#include <string>
#include <SDL.h>


class Character {
private:
	std::string name;
	int width;
	int height;
	int zindex;
	std::string orientation;
public:
	Character();
	Character(int width, int height, int zindex, std::string orientation);
	Character(std::string name, int width, int height, int zindex, std::string orientation);
	bool load(SDL_Renderer* render);
	void render(SDL_Renderer* render);
	virtual ~Character();
};

#endif /* CHARACTER_H_ */
