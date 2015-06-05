#include "../headers/Menu.h"


void Menu::initFlag() {
	//musica desactivada por defecto
	this->music = false;
	this->musicStarted = false;
	//menu de texto por defecto
	this->textMenu = true;
}

void Menu::createMenuItemList(int no_of_items, std::string * strings, int x, int y, int width, int height) {

	start = new MenuItem(x, y, width, height, strings[0]);
	y = y + 50;
	start->previous = NULL;
	MenuItem * temp1 = start;
	MenuItem * temp2 = start;

	int i = 1;
	while (i<no_of_items)
	{
		temp2 = new MenuItem(x, y, 150, 50, strings[i]);
		temp1->next = temp2;
		temp2->previous = temp1;
		temp1 = temp2;
		y = y + 50;
		i++;
	}

	temp2->next = NULL;
	selected = start;
	selected->setTextColor(255, 255, 255);
}

void Menu::loadBackgroundImage(std::string path) {
	SDL_Surface* pTempSurface = IMG_Load(path.c_str());
	background = SDL_CreateTextureFromSurface(this->render, pTempSurface);
	SDL_FreeSurface(pTempSurface);
}

void Menu::loadSoundEffect(std::string path) {
	sound = Mix_LoadWAV(path.c_str());
}

void Menu::setMusicPath(std::string path) {
	this->musicMenu = Mix_LoadMUS(path.c_str());
	this->music = true;
}

Menu::Menu(int no_of_items, std::string * strings, int start_x, int start_y, int width, int height, SDL_Renderer* rd)
{
	this->render = rd;

	this->initFlag();

	this->loadSoundEffect("sounds/menu.wav");

	this->createMenuItemList(no_of_items, strings, start_x, start_y, width, height);

	this->loadBackgroundImage("images/mk-bg-menu.jpg");
}

void Menu::draw(SDL_Texture* tx) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = 1920;
	srcRect.h = 1080;

	destRect.w = GameGUI::getInstance()->getWindow()->getWidthPx();
	destRect.h = GameGUI::getInstance()->getWindow()->getHeightPx();
	destRect.x = 0;
	destRect.y = 0;

	SDL_RenderCopyEx(render, tx, &srcRect, &destRect, 0, 0,
		SDL_FLIP_NONE);
}

void Menu::show(int alpha)
{
	SDL_SetTextureAlphaMod(background, alpha);

	if (alpha != 250)
		this->draw(background);

	MenuItem * temp = start;
	while (temp != 0)
	{
		temp->show(render);
		temp = temp->next;
	}
}

std::string Menu::clicked(int mouse_x, int mouse_y)
{
	MenuItem * next = start;
	while (next != 0)
	{
		if (next->checkBounds(mouse_x, mouse_y))
			return next->text;
		next = next->next;
	}
	return "None";
}

std::string Menu::identify_event()
{
	if (music && !musicStarted) {
		Mix_PlayMusic(musicMenu, -1);
		musicStarted = true;
	}

	std::string temp;
	SDL_Event event;
	while (1) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return "Exit";

			if (event.type == SDL_KEYDOWN) {

				switch (event.key.keysym.sym) {
				case SDLK_UP:
					if (selected->previous != NULL) {
						Mix_PlayChannel(-1, sound, 0);

						selected->setTextColor(150, 150, 150);
						selected->show(render);
						selected = selected->previous;
						selected->setTextColor(255, 255, 255);
						selected->show(render);
					}
					break;

				case SDLK_DOWN:
					if (selected->next != NULL) {
						Mix_PlayChannel(-1, sound, 0);
						selected->setTextColor(150, 150, 150);
						selected->show(render);
						selected = selected->next;
						selected->setTextColor(255, 255, 255);
						selected->show(render);
					}
					break;

				case SDLK_RETURN:
					return selected->text;

				default:
					break;
				}
			}
		}
	}
}

Menu::~Menu() {
	delete this->start;
}