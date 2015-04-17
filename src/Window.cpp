/*
 * Window.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Window.h"

Window::Window() {
	this->widthPx = 0;
	this->heightPx = 0;
	this->width = 0;
	this->title = "";
	this->xpos = 0;
	this->ypos = 0;
}
Window::Window(int widthPx, int heightPx, int width) {
	this->widthPx = widthPx;
	this->heightPx = heightPx;
	this->width = width;
	this->title = "";
	this->xpos = 0;
	this->ypos = 0;
}
Window::Window(const char* title, int xpos, int ypos, int widthPx, int heightPx, int widthLg) {

	this->widthPx = widthPx;
	this->heightPx = heightPx;
	this->width = widthLg;
	this->title = title;
	this->xpos = xpos;
	this->ypos = ypos;
}

int Window::getHeightPx() {
	return this->heightPx;
}

int Window::getWidthPx() {
	return this->widthPx;
}

int Window::getWidth() {
	return this->width;
}

Window::~Window() {
}

