#ifndef LINK_H
#define LINK_H

#ifdef LINKDLL_EXPORTS
#define LINKDLL_API __declspec(dllexport) 
#else
#define LINKDLL_API __declspec(dllimport) 
#endif


/* Link class to contain the private data members necessary to draw individual Link. Unlike
a generic link which contains only length information, this class is designed as a "VisualLink" class
which also contains information about screen placement and spatial orientation. A four bar class will
be used to manage a set of 4 link objects*/

#include "Point2D.h"

class Link
{
public:
	LINKDLL_API Link(double len = 0.2, double ang = 0); //default length and angle
	LINKDLL_API virtual void setLength(double);
	LINKDLL_API virtual void setPos(Point2D);
	LINKDLL_API virtual void setPos(double x, double y);
	LINKDLL_API virtual void setAngle(double);

	LINKDLL_API virtual double getLength();
	LINKDLL_API virtual double getAngle();

	LINKDLL_API virtual Point2D getPos1(); // equal to position
	LINKDLL_API virtual Point2D getPos2(); // equal to position + length @angle

	LINKDLL_API virtual void draw();

protected:

	double length;
	double angle;
	Point2D position;

};

#endif