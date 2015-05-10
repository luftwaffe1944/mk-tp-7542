/*
 * RGBAndHSV.h
 *
 *  Created on: May 9, 2015
 *      Author: nicolas.m.outeda
 */

#ifndef RGBANDHSV_H_
#define RGBANDHSV_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h>
using namespace std;

/*typedef struct {
    static double r;       // percent
    static double g;       // percent
    static double b;       // percent
} rgb;

typedef struct {
	static double h;       // angle in degrees
	static double s;       // percent
	static double v;       // percent
} hsv;*/

class  RGBAndHSV {
public:
	static double r;
	static double g;
	static double b;
	static double h;
	static double s;
	static double v;
	static void setRGB(uint8_t r, uint8_t g, uint8_t b);
	static void convertRGBUsingShift(double shift);
	static int rgb2hsv();
	static int hsv2rgb();
};

#endif /* RGBANDHSV_H_ */
