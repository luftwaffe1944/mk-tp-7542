/*
 * RGBAndHSV.cpp
 *
 *  Created on: May 9, 2015
 *      Author: nicolas.m.outeda
 */

#include "../headers/RGBAndHSV.h"
#include <stdint.h>

double RGBAndHSV::r;
double RGBAndHSV::g;
double RGBAndHSV::b;
double RGBAndHSV::h;
double RGBAndHSV::s;
double RGBAndHSV::v;


int RGBAndHSV::rgb2hsv()
{
    double      min, max, delta;

    min = RGBAndHSV::r < RGBAndHSV::g ? RGBAndHSV::r : RGBAndHSV::g;
    min = min  < RGBAndHSV::b ? min  : RGBAndHSV::b;

    max = RGBAndHSV::r > RGBAndHSV::g ? RGBAndHSV::r : RGBAndHSV::g;
    max = max  > RGBAndHSV::b ? max  : RGBAndHSV::b;

    RGBAndHSV::v = max;                                // v
    delta = max - min;
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        RGBAndHSV::s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0
            // s = 0, v is undefined
        RGBAndHSV::s = 0.0;
        RGBAndHSV::h = 0.0;                            // its now undefined
        return 1;
    }
    if( RGBAndHSV::r >= max )                           // > is bogus, just keeps compilor happy
        RGBAndHSV::h = ( RGBAndHSV::g - RGBAndHSV::b ) / delta;        // between yellow & magenta
    else
    if( RGBAndHSV::g >= max )
        RGBAndHSV::h = 2.0 + ( RGBAndHSV::b - RGBAndHSV::r ) / delta;  // between cyan & yellow
    else
        RGBAndHSV::h = 4.0 + ( RGBAndHSV::r - RGBAndHSV::g ) / delta;  // between magenta & cyan

    RGBAndHSV::h *= 60.0;                              // degrees

    if( RGBAndHSV::h < 0.0 )
        RGBAndHSV::h += 360.0;
    return 1;
}


int RGBAndHSV::hsv2rgb()
{
    double      hh, p, q, t, ff;
    long        i;

    if(RGBAndHSV::s <= 0.0) {       // < is bogus, just shuts up warnings
        RGBAndHSV::r = RGBAndHSV::v;
        RGBAndHSV::g = RGBAndHSV::v;
        RGBAndHSV::b = RGBAndHSV::v;
        return 1;
    }
    hh = RGBAndHSV::h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = RGBAndHSV::v * (1.0 - RGBAndHSV::s);
    q = RGBAndHSV::v * (1.0 - (RGBAndHSV::s * ff));
    t = RGBAndHSV::v * (1.0 - (RGBAndHSV::s * (1.0 - ff)));

    switch(i) {
    case 0:
        RGBAndHSV::r = RGBAndHSV::v;
        RGBAndHSV::g = t;
        RGBAndHSV::b = p;
        break;
    case 1:
        RGBAndHSV::r = q;
        RGBAndHSV::g = RGBAndHSV::v;
        RGBAndHSV::b = p;
        break;
    case 2:
        RGBAndHSV::r = p;
        RGBAndHSV::g = RGBAndHSV::v;
        RGBAndHSV::b = t;
        break;

    case 3:
        RGBAndHSV::r = p;
        RGBAndHSV::g = q;
        RGBAndHSV::b = RGBAndHSV::v;
        break;
    case 4:
        RGBAndHSV::r = t;
        RGBAndHSV::g = p;
        RGBAndHSV::b = RGBAndHSV::v;
        break;
    case 5:
    default:
        RGBAndHSV::r = RGBAndHSV::v;
        RGBAndHSV::g = p;
        RGBAndHSV::b = q;
        break;
    }
    return 1;
}

void RGBAndHSV::setRGB(uint8_t r, uint8_t g, uint8_t b) {
	RGBAndHSV::r = r;
	RGBAndHSV::g = g;
	RGBAndHSV::b = b;
}

void RGBAndHSV::convertRGBUsingShift(double shift) {
	RGBAndHSV::rgb2hsv();
	RGBAndHSV::h = RGBAndHSV::h + shift;
	RGBAndHSV::hsv2rgb();
}
