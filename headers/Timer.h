/*
 * Timer.h
 *
 *  Created on: 28/4/2015
 *      Author: julian
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <iostream>
#include "SDL.h"

class Timer {
public:
	//Initializes variables
	Timer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;
};

#endif /* TIMER_H_ */
