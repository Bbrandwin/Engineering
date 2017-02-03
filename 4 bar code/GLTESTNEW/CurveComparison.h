#ifdef CURVECOMPARISONDLL_EXPORTS
#define CURVECOMPARISONDLL_API __declspec(dllexport) 
#else
#define CURVECOMPARISONDLL_API __declspec(dllimport) 
#endif

#ifndef CURVECOMPARISON_H
#define CURVECOMPARISON_H
#include <vector>
using namespace std;

#include "fft.h"
#include "Complex.h"
#include "Point2D.h"


class CurveComparison
{
public:
	CURVECOMPARISONDLL_API CurveComparison(vector<Point2D> in1, vector<Point2D> in2);

	CURVECOMPARISONDLL_API vector<complex> p2dToFFT(vector<Point2D>); 


private:
	vector<Point2D> rCurve1;
	vector<Point2D> rCurve2;

	vector<complex> fCurve1;
	vector<complex> fCurve2;


};

#endif

