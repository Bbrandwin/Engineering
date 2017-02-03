#ifdef BSPLINETWEAKDLL_EXPORTS
#define BSPLINETWEAKDLL_API __declspec(dllexport) 
#else
#define BSPLINETWEAKDLL_API __declspec(dllimport) 
#endif

#ifndef BSplineTweak_H
#define BSplineTweak_H

#include <vector>
#include "Point2D.h"
#include <QtGui/QtGui> 
#include <QtOpenGL/qgl.h>
#include <QtCore/qdebug.h>
using namespace std;

class BSplineTweak {
	friend class GLWidget;

public:
	BSPLINETWEAKDLL_API BSplineTweak();
	BSPLINETWEAKDLL_API ~BSplineTweak();
	/*void setPx( int, double );  // set x in coordinate 
	double getPx( int );        // get x in coordinate
	void setPy( int, double );  // set y in coordinate
	double getPy( int ); */       // get y in coordinate
	BSPLINETWEAKDLL_API void FrPoint_algorithm( double &, double &, double ); 
	BSPLINETWEAKDLL_API vector<Point2D> splitAndTweak(int);
	
	BSPLINETWEAKDLL_API void draw();            // draw Bezier curve 
    BSPLINETWEAKDLL_API int getDegree();
	BSPLINETWEAKDLL_API void setDegree( int );
private:
	vector<Point2D> F; //Control Points
	vector<Point2D> curve;

	
	int degree;
	int size;
	int t;
};

#endif



