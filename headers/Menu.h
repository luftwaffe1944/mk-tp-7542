#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"
#include "SDL.h"
#include "SDL_Mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include "GameGUI.h"


class Menu
{
public:
	Menu(int no_of_items, std::string * strings, int start_x, int start_y, SDL_Renderer*);
	void show(int alpha);
	std::string identify_event();
	virtual ~Menu();
	std::string clicked(int mouse_x, int mouse_y);
	SDL_Renderer* render;

private:
	MenuItem * start;
	MenuItem * selected;
	SDL_Texture * background;
	Mix_Chunk * sound;
	void draw(SDL_Texture*);
};

#endif // MENU_H