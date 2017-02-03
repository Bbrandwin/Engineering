#ifdef PLANARFOURBARDLL_EXPORTS
#define PLANARFOURBARDLL_API __declspec(dllexport) 
#else
#define PLANARFOURBARDLL_API __declspec(dllimport) 
#endif


#include "Link.h"
#include "Coupler.h"
#include "Point2D.h"
#include <math.h>
#include <vector>
#include <QtCore/qobject.h>
using namespace std; 

class PlanarFourBar 
{
	friend class GLWidget;


public:
	// constructor takes a Point2D for the position of the crank and theta1 for ground link angle
	PLANARFOURBARDLL_API PlanarFourBar(double r = 0, double gnd = 0.4, double crnk = 0.2, double cup0 = 0.4, double rokr = 0.3, double cup1 = 0.2, double t0 = 0, double t1 = 0, double gamma = 2*acos(-1.0)/3, bool ifcrossed = 0); 
	PLANARFOURBARDLL_API PlanarFourBar(double r, Link &gnd, Link &crnk, Coupler &, Link &rokr, double theta0, double theta1, bool ifcrossed = 1);

	PLANARFOURBARDLL_API double getTheta3(bool);
	PLANARFOURBARDLL_API double getTheta4(bool);

	PLANARFOURBARDLL_API void drawMechanism(double crnkAng = acos(-1.0)/3, bool crossed = 0);
	PLANARFOURBARDLL_API void makeCurve(bool crossed = 0); //this makes a curve of size 2^13
	PLANARFOURBARDLL_API void drawCurve(bool crossed = 0); //this makes the same curve with a slight overlap to prevent visual "cuts" in the curve
	PLANARFOURBARDLL_API void animate(double speed, bool crossed = 0); //crank speed in radians/sec

	PLANARFOURBARDLL_API vector<Point2D> getCurve();

	PLANARFOURBARDLL_API void setR(double);
	PLANARFOURBARDLL_API void setTheta0(double);
	PLANARFOURBARDLL_API void setTheta1(double);
	PLANARFOURBARDLL_API void setGnd(double);
	PLANARFOURBARDLL_API void setCrnk(double);
	PLANARFOURBARDLL_API void setCplr(double L0, double gamma, double L1);
	PLANARFOURBARDLL_API void setCplrLength1(double);
	PLANARFOURBARDLL_API void setCplrLength2(double);
	PLANARFOURBARDLL_API void setCplrAngle(double);
	PLANARFOURBARDLL_API void setRokr(double);

	PLANARFOURBARDLL_API double getR(); 
	PLANARFOURBARDLL_API double getTheta0();
	PLANARFOURBARDLL_API double getTheta1();
	PLANARFOURBARDLL_API double getGnd();
	PLANARFOURBARDLL_API double getCrnk();
	PLANARFOURBARDLL_API double getCplrLength1();
	PLANARFOURBARDLL_API double getCplrLength2();
	PLANARFOURBARDLL_API double getCplrAngle();
	PLANARFOURBARDLL_API double getRokr(); 

	

private:
	double r; // = sqrt(pos.getPx()^2 + pos.getPy()^2)
	double theta0, theta1; // = angle of "pos" and angle of ground link
	Link ground;
	Link crank;
	Coupler coupler;
	Link rocker;
	bool crossed;// 1 = crossed, 0 = open
	//double theta2; // extra variable to hold crank angle

	vector<Point2D> curve; //slightly longer vector to overlap. For drawing only
	vector<Point2D> realCurve; //size = 2^13 for FFT algorithm
};
