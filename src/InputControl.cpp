/*
 * InputControl.h
 *
 *  Created on: 31/03/2015
 *      Author: Diego Serra
 *
 * llamar al metodo refreshInputs para obtener los nuevos estados de las entradas,
 * hacer la llamada luego del ciclo de vacia la lista de eventos de SDL, while (SDL_PollEvent(&event))
 *
 *
 */

#include "../headers/InputControl.h"
#include "SDL.h"
#include "../headers/MKGame.h"
#include <stddef.h>

void InputControl::refreshInputs() {

	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			MKGame::Instance()->quit();
		}
	}

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL);

	this->firstPlayerMove = NO_INPUT;
	this->secondPlayerMove = NO_INPUT;
	this->controlOption = NO_INPUT;

	if ((currentKeyStates[SDL_SCANCODE_R])) {
		this->controlOption = RESET;
	} else if ((currentKeyStates[SDL_SCANCODE_UP])
			&& !(currentKeyStates[SDL_SCANCODE_DOWN])
			&& (currentKeyStates[SDL_SCANCODE_LEFT])
			&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_LEFT;
	} else if ((currentKeyStates[SDL_SCANCODE_UP])
			&& !(currentKeyStates[SDL_SCANCODE_DOWN])
			&& !(currentKeyStates[SDL_SCANCODE_LEFT])
			&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_RIGHT;
	} else if (!(currentKeyStates[SDL_SCANCODE_UP])
			&& (currentKeyStates[SDL_SCANCODE_DOWN])
			&& !(currentKeyStates[SDL_SCANCODE_LEFT])
			&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_RIGHT;
	} else if (!(currentKeyStates[SDL_SCANCODE_UP])
			&& (currentKeyStates[SDL_SCANCODE_DOWN])
			&& (currentKeyStates[SDL_SCANCODE_LEFT])
			&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_LEFT;
	} else if ((currentKeyStates[SDL_SCANCODE_UP])
			&& !(currentKeyStates[SDL_SCANCODE_DOWN])
			&& !(currentKeyStates[SDL_SCANCODE_LEFT])
			&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_UP;
	} else if (!(currentKeyStates[SDL_SCANCODE_UP])
			&& (currentKeyStates[SDL_SCANCODE_DOWN])
			&& !(currentKeyStates[SDL_SCANCODE_LEFT])
			&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN;
	} else if (!(currentKeyStates[SDL_SCANCODE_UP])
			&& !(currentKeyStates[SDL_SCANCODE_DOWN])
			&& (currentKeyStates[SDL_SCANCODE_LEFT])
			&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_LEFT;
	} else if (!(currentKeyStates[SDL_SCANCODE_UP])
			&& !(currentKeyStates[SDL_SCANCODE_DOWN])
			&& !(currentKeyStates[SDL_SCANCODE_LEFT])
			&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
		this->firstPlayerMove = FIRST_PLAYER_MOVE_RIGHT;
	}
}

InputCommand InputControl::getFirstPlayerMove() {
	return this->firstPlayerMove;
}

InputCommand InputControl::getSecondPlayerMove() {
	return this->secondPlayerMove;
}

InputCommand InputControl::getControlOption() {
	return this->controlOption;
}
