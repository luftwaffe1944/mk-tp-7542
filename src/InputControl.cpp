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

	const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL);

	this->firstPlayerMove = NO_INPUT;
	this->secondPlayerMove = NO_INPUT;
	this->controlOption = NO_INPUT;

	if ((currentKeyStates[SDL_SCANCODE_R])) {
		this->controlOption = RESET;

		//COMBINATION WITH UP
	} else if (currentKeyStates[SDL_SCANCODE_UP]) {

		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_UP_RIGHT;
		}

		//COMBINATION WITH DOWN
	} else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		if (currentKeyStates[SDL_SCANCODE_A]) {
			this->firstPlayerMove = FIRST_PLAYER_DUCK_PUNCH;
		} else if (currentKeyStates[SDL_SCANCODE_S]) {
			this->firstPlayerMove = FIRST_PLAYER_UPPERCUT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& (currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_RIGHT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& (currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN_LEFT;
		} else if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_DOWN;

		}
		//COMBINATION WITH LEFT
	} else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_LEFT;
		}
		//COMBINATION WITH RIGHT
	} else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		if (!(currentKeyStates[SDL_SCANCODE_UP])
				&& !(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])) {
			this->firstPlayerMove = FIRST_PLAYER_MOVE_RIGHT;
		}
		//COMBINATION WITH S
	} else if (currentKeyStates[SDL_SCANCODE_S]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_HI_PUNCH;
		}
		//COMBINATION WITH A
	} else if (currentKeyStates[SDL_SCANCODE_A]) {
		if (!(currentKeyStates[SDL_SCANCODE_DOWN])
				&& !(currentKeyStates[SDL_SCANCODE_LEFT])
				&& !(currentKeyStates[SDL_SCANCODE_RIGHT])) {
			this->firstPlayerMove = FIRST_PLAYER_LO_PUNCH;
		}

	} else if (currentKeyStates[SDL_SCANCODE_X]) {
		this->firstPlayerMove = FIRST_PLAYER_HIGH_KICK;
	}

	else if (currentKeyStates[SDL_SCANCODE_Z]) {
		this->firstPlayerMove = FIRST_PLAYER_LOW_KICK;
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
