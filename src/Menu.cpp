#include "../headers/Menu.h"


void Menu::initFlag() {
	//musica desactivada por defecto
	this->music = false;
	this->musicStarted = false;
}

void Menu::createMenuItemList(int no_of_items, std::string * strings, int x, int y, int width, int height) {

	start = new MenuItem(x, y, width, height, strings[0]);
	y = y + height;
	start->previous = NULL;
	MenuItem * temp1 = start;
	MenuItem * temp2 = start;

	int i = 1;
	while (i < no_of_items) {
		temp2 = new MenuItem(x, y, width, height, strings[i]);
		temp1->next = temp2;
		temp2->previous = temp1;
		temp1 = temp2;
		y = y + height;
		i++;
	}

	temp2->next = NULL;
	selected = start;
	selected->setColor(255, 255, 255, 255);
}

void Menu::createGridCharacters(int no_of_items, std::string * strings, int x, int y, int width, int height) {

	start = new MenuItem(x, y, width, height, strings[0]);
	start->previous = NULL;
	MenuItem * temp1 = start;
	MenuItem * temp2 = start;

	int i = 1;
	int j = 2;
	int auxX = x + width;
	while (i < no_of_items) {
		while (j < 5 && i < no_of_items) {
			temp2 = new MenuItem(auxX, y, width, height, strings[i]);
			temp1->next = temp2;
			temp2->previous = temp1;
			temp1 = temp2;
			auxX = auxX + width;
			i++;
			j++;
		}
		y = y + height;
		auxX = x;
		j = 1;
	}

	temp2->next = NULL;
	selected = start;
	selected->setColor(0, 255, 0, 255);
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

Menu::Menu(int no_of_items, std::string * strings, int start_x, int start_y, int width, int height, SDL_Renderer* rd, bool tm) {
	this->textMenu = tm;
	this->render = rd;

	this->initFlag();

	this->loadSoundEffect("sounds/menu.wav");

	if (textMenu) 
		this->createMenuItemList(no_of_items, strings, start_x, start_y, width, height);
	else 
		this->createGridCharacters(no_of_items, strings, start_x, start_y, width, height);

	this->loadBackgroundImage("images/mk-bg-menu.jpg");
}

void Menu::draw(SDL_Texture* tx) {
	SDL_Rect destRect;

	destRect.w = GameGUI::getInstance()->getWindow()->getWidthPx();
	destRect.h = GameGUI::getInstance()->getWindow()->getHeightPx();
	destRect.x = 0;
	destRect.y = 0;

	SDL_RenderCopyEx(render, tx, NULL, &destRect, 0, 0,
		SDL_FLIP_NONE);
}

SDL_Texture* Menu::loadImgCharacter(SDL_Renderer* render) {
	std::string path = "images/" + selected->text + "/stance.png";
	SDL_Surface* pTempSurface = IMG_Load(path.c_str());
	SDL_Texture* cTexture;
	cTexture = SDL_CreateTextureFromSurface(this->render, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	return cTexture;
}

void Menu::drawCharacterStance(SDL_Renderer* render) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = SPRITE_WIDTH / 3;
	srcRect.y = 0;
	srcRect.w = SPRITE_WIDTH / 3;
	srcRect.h = SPRITE_HEIGHT;

	destRect.w = GameGUI::getInstance()->getWindow()->getWidthPx() / 6 * 0.90;
	destRect.h = GameGUI::getInstance()->getWindow()->getHeightPx() * 0.60;
	destRect.x = 0;
	destRect.y = GameGUI::getInstance()->getWindow()->getHeightPx() * 0.35;
	resetCharacterRender(render);
	SDL_RenderCopyEx(render, loadImgCharacter(render), &srcRect, &destRect, 0, 0,
		SDL_FLIP_NONE);
}

void Menu::show(int alpha) {
	SDL_SetTextureAlphaMod(background, alpha);

	if (alpha != 250)
		this->draw(background);

	MenuItem * temp = start;
	while (temp != 0) {
		if (textMenu) {
			temp->show(render);
			temp = temp->next;
		}
		else {
			this->drawCharacterStance(render);
			temp->drawBox(render);
			temp = temp->next;
		}
	}
}

std::string Menu::clicked(int mouse_x, int mouse_y) {
	MenuItem * next = start;
	while (next != 0) {
		if (next->checkBounds(mouse_x, mouse_y))
			return next->text;
		next = next->next;
	}
	return "None";
}

void Menu::resetCharacterRender(SDL_Renderer* render) {
	int windowsWidthPx = GameGUI::getInstance()->getWindow()->getWidthPx();
	int windowsHeightPx = GameGUI::getInstance()->getWindow()->getHeightPx();
	SDL_Texture* target_texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, windowsWidthPx, windowsHeightPx);
	SDL_SetRenderTarget(render, target_texture);

	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = windowsWidthPx;
	dst.h = windowsHeightPx;

	SDL_RenderCopy(render, background, NULL, &dst);
	SDL_RenderPresent(render);
	SDL_SetRenderTarget(render, NULL);
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = windowsWidthPx / 6;
	src.h = windowsHeightPx;
	this->columCharacterOne.x = 0;
	this->columCharacterOne.y = 0;
	this->columCharacterOne.w = windowsWidthPx /6;
	this->columCharacterOne.h = windowsHeightPx;

	this->columCharacterTwo.x = windowsWidthPx * 5 / 6;
	this->columCharacterTwo.y = 0;
	this->columCharacterTwo.w = windowsWidthPx / 6;
	this->columCharacterTwo.h = windowsHeightPx;

	SDL_RenderCopyEx(render, target_texture, &src, &columCharacterOne, 0, 0,
		SDL_FLIP_NONE);
	src.x = windowsWidthPx * 5 / 6;
	src.y = 0;
	src.w = windowsWidthPx / 6;
	src.h = windowsHeightPx;
	SDL_RenderCopyEx(render, target_texture, &src, &columCharacterTwo, 0, 0,
		SDL_FLIP_NONE);
	SDL_DestroyTexture(target_texture);
}

std::string Menu::identify_event() {
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
					if (textMenu) {
						if (selected->previous != NULL) {
							Mix_PlayChannel(-1, sound, 0);
							selected->setColor(150, 150, 150,255);
							selected->show(render);
							selected = selected->previous;
							selected->setColor(255, 255, 255,255);
							selected->show(render);
						}
					}
					else {
						if (selected->positionY - selected->height >= start->positionY) {
							selected->setColor(150, 150, 150,0);
							selected->drawBox(render);
							selected = selected->previous;
							selected = selected->previous;
							selected = selected->previous;
							selected = selected->previous;
							selected->setColor(0, 255, 0,255);
							this->drawCharacterStance(render);
							selected->drawBox(render);
						}
					}

					break;

				case SDLK_DOWN:
					if (textMenu) {
						if (selected->next != NULL) {
							Mix_PlayChannel(-1, sound, 0);
							selected->setColor(150, 150, 150,255);
							selected->show(render);
							selected = selected->next;
							selected->setColor(255, 255, 255,255);
							selected->show(render);
						}
					}
					else {
						if (selected->positionY + selected->height < start->positionY + start->height*3) {
							selected->setColor(150, 150, 150,0);
							selected->drawBox(render);
							selected = selected->next;
							selected = selected->next;
							selected = selected->next;
							selected = selected->next;
							selected->setColor(0, 255, 0,255);
							this->drawCharacterStance(render);
							selected->drawBox(render);
						}
					}

					break;

				case SDLK_LEFT:
					if (!textMenu) {
						if (selected->positionX - selected->width >= start->positionX) {
							selected->setColor(150, 150, 150,255);
							selected->drawBox(render);
							selected = selected->previous;
							selected->setColor(0, 255, 0,255);
							this->drawCharacterStance(render);
							selected->drawBox(render);
						}
					}

					break;
				case SDLK_RIGHT:
					if (!textMenu) {
						if (selected->positionX + selected->width < start->positionX + start->width * 4) {
							selected->setColor(150, 150, 150,0);
							selected->drawBox(render);
							selected = selected->next;
							selected->setColor(0, 255, 0,255);
							this->drawCharacterStance(render);
							selected->drawBox(render);
						}
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