
#ifndef BOX_H_
#define BOX_H_


#include <string>
#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;

class Box {
private:
	int height;
	int width;
	float centerX;
	float centerY;
	bool active;

public:
	Box();
	Box(float X, float Y,float W,float H,bool active);
	virtual ~Box();
	void setHeight(float H);
	void setWidth(float W);
	void setCenter(float X, float Y);
	void setActive(bool active);
	float getTopY();
	float getBottomY();
	float getLeftX();
	float getRightX();
	bool isActive();
	bool isColliding(Box* box);
	Box* cloneBox();
	void resizeBox(float newX, float newY);
};

#endif /* BOX_H_ */
