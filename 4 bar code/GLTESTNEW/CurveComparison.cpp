#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

#include "CurveComparison.h"
#include "Complex.h"
#include "fft.h"

CurveComparison::CurveComparison(vector<Point2D> in1, vector<Point2D> in2)
{
	rCurve1 = in1;
	rCurve2 = in2;

	fCurve1 = p2dToFFT(rCurve1); 
	fCurve2 = p2dToFFT(rCurve2);
}

vector<complex> CurveComparison::p2dToFFT(vector<Point2D> curve)
{
	complex *c = new complex[curve.size()];

	for (int i=0;i<curve.size();i++)
	{
		complex temp(curve[i].getPx(), curve[i].getPy());
		c[i] = temp;
	}

	CFFT::Forward(c,curve.size());

	vector<complex> temp(curve.size());

	for (int i=0;i<curve.size();i++)
	{
		
		temp[i] = c[i];
	}
	cout << "After FFT" << temp[1].re() << ", " << temp[1].im() << endl;

	return temp;
}







	
	//complex c(curve.getPx(), curve.getPy())


