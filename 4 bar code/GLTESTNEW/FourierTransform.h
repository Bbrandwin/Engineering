#ifdef FOURIERTRANSFORMDLL_EXPORTS
#define FOURIERTRANSFORMDLL_API __declspec(dllexport) 
#else
#define FOURIERTRANSFORMDLL_API __declspec(dllimport) 
#endif

#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include <math.h>
#include <vector>
#include "Point2D.h"

using namespace std;

class FourierTransform
{
public:
	FOURIERTRANSFORMDLL_API FourierTransform(vector<Point2D> &in);
	FOURIERTRANSFORMDLL_API FourierTransform(vector<Point2D> &in, vector<Point2D> &out);


	FOURIERTRANSFORMDLL_API void forward();
	//void inverse();

	FOURIERTRANSFORMDLL_API double getTotalLength();
	FOURIERTRANSFORMDLL_API double getCurveLength(int i);
	FOURIERTRANSFORMDLL_API double getAngleChange(int i);

	FOURIERTRANSFORMDLL_API void setInput(vector<Point2D> &in);
	FOURIERTRANSFORMDLL_API void setOutpur(vector<Point2D> &out);

	FOURIERTRANSFORMDLL_API vector<Point2D> getInput(); 
	FOURIERTRANSFORMDLL_API vector<Point2D> getOuput();

private:
	vector<Point2D> input;
	vector<Point2D> output;


};

#endif
