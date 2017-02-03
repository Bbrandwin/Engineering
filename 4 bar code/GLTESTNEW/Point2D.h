

#ifdef POINT2DDLL_EXPORTS
#define POINT2D_API __declspec(dllexport) 
#else
#define POINT2DDLL_API __declspec(dllimport) 
#endif

// point2D.h
// point2D class definition

#ifndef POINT2D_H
#define POINT2D_H


class Point2D
{
public:
	POINT2DDLL_API Point2D(double=0.0, double=0.0);
	POINT2DDLL_API double getPx(void);
	POINT2DDLL_API double getPy(void);
	POINT2DDLL_API void setPx(double);
	POINT2DDLL_API void setPy(double);
	

private:
	double x, y;
};

#endif