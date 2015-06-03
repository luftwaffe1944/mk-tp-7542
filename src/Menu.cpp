#include "../headers/Menu.h"


Menu::Menu(int no_of_items, std::string * strings, int start_x, int start_y, SDL_Renderer* rd)
{
	this->render = rd;
	sound = Mix_LoadWAV("sounds/menu.wav");
	if (sound == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	int x = start_x;
	int y = start_y;

	start = new MenuItem(x, y, 150, 50, strings[0]);
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

	SDL_Surface* pTempSurface = IMG_Load("images/mk-bg-menu.jpg");
	background = SDL_CreateTextureFromSurface(this->render, pTempSurface);
	SDL_FreeSurface(pTempSurface);

//	if (start_x<150)
//		background = Game::load_image("controls.JPG");
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
		SDL_FLIP_HORIZONTAL);
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
	std::string temp;
	SDL_Event event;
	while (1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				return "Exit";

			if (event.type == SDL_KEYDOWN)
			{

				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					if (selected->previous != NULL)
					{
						Mix_PlayChannel(-1, sound, 0);

						selected->setTextColor(150, 150, 150);
						selected->show(render);
						selected = selected->previous;
						selected->setTextColor(255, 255, 255);
						selected->show(render);
					}
					break;

				case SDLK_DOWN:
					if (selected->next != NULL)
					{
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

Menu::~Menu()
{

}
