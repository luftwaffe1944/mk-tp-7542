/*
 * Window.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef WINDOW_H_
#define WINDOW_H_

class Window {

public:
	const char* title;
	int xpos;
	int ypos;
	int widthPx;
	int heightPx;
	int width;

	Window();
	Window(int widthPx, int heightPx, int width);
	Window(const char* title, int xpos, int ypos, int widthPx, int heightPx, int widthLg);
	virtual ~Window();
};

#endif /* WINDOW_H_ */
