#ifndef MENU_H
#define MENU_H

#define RATIOBOX 81
#define WIDTHBOX 48
#define HEIGHTBOX 59

#include "MenuItem.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include "GameGUI.h"
#include "Constants.h"
#include "InputControl.h"


class Menu
{
public:
	Menu(int no_of_items, std::string * strings, int start_x, int start_y, int width, int height, SDL_Renderer*, bool textMenu);
	void show(int alpha);
	std::string identify_event();
	virtual ~Menu();
	std::string clicked(int mouse_x, int mouse_y);
	SDL_Renderer* render;
	bool music;
	void setMusicPath(std::string);
	void buttonUp();
	void buttonDown();
	void buttonRight();
	void buttonLeft();
	void buttonW();
	void buttonS();
	void buttonA();
	void buttonD();


private:
	MenuItem * start;
	MenuItem * selected;
	MenuItem * selectedTwo;
	SDL_Texture * background;
	Mix_Chunk * sound;
	Mix_Music * musicMenu;
	SDL_Rect columCharacterOne;
	SDL_Rect columCharacterTwo;
	bool musicStarted;
	void draw(SDL_Texture*);
	void initFlag();
	bool textMenu;
	void createMenuItemList(int nItems, std::string * strings, int x, int y, int width, int height);
	void createGridCharacters(int nItems, std::string * strings, int x, int y, int width, int height);
	void loadBackgroundImage(std::string path);
	void loadSoundEffect(std::string path);
	void drawCharacterStance(SDL_Renderer*);
	void resetCharacterRender(SDL_Renderer*);
	SDL_Texture* loadImgCharacterOne(SDL_Renderer*);
	SDL_Texture* loadImgCharacterTwo(SDL_Renderer*);
	bool playerOneSelected;
	bool playerTwoSelected;
	void getJoystickInput(SDL_Event event);
};

#endif // MENU_H
