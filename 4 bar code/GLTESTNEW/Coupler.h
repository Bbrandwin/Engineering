#ifdef COUPLERDLL_EXPORTS
#define COUPLERDLL_API __declspec(dllexport) 
#else
#define COUPLERDLL_API __declspec(dllimport) 
#endif

#ifndef COUPLER_H
#define COUPLER_H

#include "Link.h"
#include <math.h>

class Coupler:public Link
{
public:
	COUPLERDLL_API Coupler(double len = .4, double ang = 0.0, double cLen = .65, double cAng = 2.94);
	COUPLERDLL_API void setCLength(double); // set length of coupler arm
	COUPLERDLL_API void setCAngle(double); // set coupler angle "gamma"

	COUPLERDLL_API void setLength(double);
	COUPLERDLL_API void setAngle(double);

	COUPLERDLL_API void cAngleTransform();
	COUPLERDLL_API double getCLength();
	COUPLERDLL_API double getCAngle();

	COUPLERDLL_API Point2D getPos3(); //this is the third point not defined by Pos1 or Pos2

	COUPLERDLL_API void draw();

protected:
	double couplerLength; //this refers to r7 (not r3). For r3 use getLength, r7 use getCLength
	double couplerAngle;
	Point2D pos3; // this is the position of the end effector. made into a private data member for convenince
};

#endif