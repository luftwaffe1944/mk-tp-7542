/*
 * Window.h
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#ifndef WINDOW_H_
#define WINDOW_H_

class Window {
private:
	int widthPx;
	int heightPx;
	int width;

public:
	Window();
	Window(int widthPx, int heightPx, int width);
	virtual ~Window();
};

#endif /* WINDOW_H_ */
