#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include "GameGUI.h"


class Menu
{
public:
	Menu(int no_of_items, std::string * strings, int start_x, int start_y, int width, int height, SDL_Renderer*);
	void show(int alpha);
	std::string identify_event();
	virtual ~Menu();
	std::string clicked(int mouse_x, int mouse_y);
	SDL_Renderer* render;
	bool music;
	void setMusicPath(std::string);
	bool textMenu;

private:
	MenuItem * start;
	MenuItem * selected;
	SDL_Texture * background;
	Mix_Chunk * sound;
	Mix_Music * musicMenu;
	bool musicStarted;
	void draw(SDL_Texture*);
	void initFlag();
	void createMenuItemList(int nItems, std::string * strings, int x, int y, int width, int height);
	void loadBackgroundImage(std::string path);
	void loadSoundEffect(std::string path);
};

#endif // MENU_H