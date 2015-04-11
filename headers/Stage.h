/*
 * Stage.h
 *
 *  Created on: 28/3/2015
 *      Author: mauro
 */

#ifndef STAGE_H_
#define STAGE_H_

class Stage {
private:
	int width;
	int height;
	int yfloor;
public:
	Stage();
	Stage(int witdh, int height, int yfloor);
	virtual ~Stage();
	int getHeight();
	int getWidth();
};

#endif /* STAGE_H_ */
