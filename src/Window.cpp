/*
 * Window.cpp
 *
 *  Created on: 29/3/2015
 *      Author: mauro
 */

#include "../headers/Window.h"

Window::Window() {
	// TODO Auto-generated constructor stub

}
Window::Window(int widthPx, int heightPx, int width) {

	this->widthPx = widthPx;
	this->heightPx = heightPx;
	this->width = width;
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
	// TODO Auto-generated destructor stub
}

