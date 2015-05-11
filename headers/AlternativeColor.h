/*
 * AlternativeColor.h
 *
 *  Created on: May 9, 2015
 *      Author: nicolas.m.outeda
 */

#ifndef ALTERNATIVECOLOR_H_
#define ALTERNATIVECOLOR_H_

class AlternativeColor {

private:
	double initial_h;
	double final_h;
	double shift;
public:
	AlternativeColor();
	AlternativeColor(double initialh, double finalH, double shift);
	virtual ~AlternativeColor();
	double getInitialH();
	double getFinalH();
	double getShift();
	void setInitialH(double initialH);
	void setFinalH(double finalH);
	void setShift(double shift);

};

#endif /* ALTERNATIVECOLOR_H_ */
