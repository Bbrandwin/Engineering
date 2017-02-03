#include "FourierTransform.h"
#include <math.h>
#include <vector>
#include "Point2D.h"

FourierTransform::FourierTransform(vector<Point2D> &in)
{
	input = in;
	output.resize(input.size());
}

FourierTransform::FourierTransform(vector<Point2D> &in, vector<Point2D> &out)
{
	input = in;
	output = out;

	

	for (int i=0;i<output.size();i++)
	{
		output[i].setPx(0.0);
		output[i].setPy(0.0);
	}
}

double FourierTransform::getAngleChange(int k)
{
	vector<double> Angle;
	vector<double> dAngle;

	for (int i=0;i<input.size();i++)
	{
		if (input[i].getPy() > 0) //first and second quadrant
		{
			Angle.push_back(atan(input[i].getPy()/input[i].getPx()));
		}
		else if (input[i].getPy() < 0) //third and fourth quadrant
		{
			Angle.push_back(-atan(input[i].getPy()/input[i].getPx()));
		}
		else if (input[i].getPy() == 0 & input[i].getPx() > 0)
		{
			Angle.push_back(0);
		}
		else if (input[i].getPy() == 0 & input[i].getPx() < 0)
		{
			Angle.push_back(acos(-1.0));
		}
	}

	for (int i=0; i<input.size() - 1;i++)
	{
		dAngle.push_back(Angle[i+1]-Angle[i]);
	}

	dAngle.push_back(Angle[0] - Angle[Angle.size()-1]);

	Angle.resize(input.size());
	dAngle.resize(input.size());

	return dAngle[k];
}

double FourierTransform::getCurveLength(int k)
{
	vector<double> currentLength;
	double length = 0.0;
	double temp = 0.0;

	for (int i=0;i<input.size()-1;i++)
	{
		temp = sqrt(pow(input[i+1].getPx() - input[i].getPx(),2) +  pow(input[i+1].getPy() - input[i].getPy(),2));
		length += temp;
		currentLength.push_back(length);
	}
	temp = sqrt(pow(input[0].getPx() - input[input.size()-1].getPx(),2) +  pow(input[0].getPy() - input[input.size()-1].getPy(),2));
	length += temp;
	currentLength.push_back(length);

	return currentLength[k];

}

double FourierTransform::getTotalLength()
{
	double length = 0.0;
	double temp = 0.0;

	for (int i=0;i<input.size()-1;i++)
	{
		temp = sqrt(pow(input[i+1].getPx() - input[i].getPx(),2) +  pow(input[i+1].getPy() - input[i].getPy(),2));
		length += temp;
	}
	temp = sqrt(pow(input[0].getPx() - input[input.size()-1].getPx(),2) +  pow(input[0].getPy() - input[input.size()-1].getPy(),2));
	length += temp;

	return length;
}


void FourierTransform::forward()
{
	for (int k=0;k<input.size();k++)
	{
		for (int i=0;i<(input.size());i++)
		{
			output[k].setPx(output[k].getPx() - 1/(k*acos(-1.0))*getAngleChange(i)*sin(2*acos(-1.0)*k*getCurveLength(i)/getTotalLength())); 
			output[k].setPy(output[k].getPy() + 1/(k*acos(-1.0))*getAngleChange(i)*cos(2*acos(-1.0)*k*getCurveLength(i)/getTotalLength())); 


		}
		vector<double> Amplitude;
		vector<double> Angle;
		for (int i=0;i<input.size();i++)
		{
			Amplitude.push_back(sqrt(pow(output[k].getPx(),2) + pow(output[k].getPy(),2)));

			if (output[k].getPy() > 0) //first and second quadrant
			{
				Angle.push_back(atan(output[k].getPy()/output[k].getPx()));
			}
			else if (output[k].getPy() < 0) //third and fourth quadrant
			{
				Angle.push_back(acos(-1.0) + atan(output[k].getPy()/output[k].getPx()));
			}
			else if (output[k].getPy() == 0 & output[k].getPx() > 0)
			{
				Angle.push_back(0);
			}
			else if (output[k].getPy() == 0 & output[k].getPx() < 0)
			{
				Angle.push_back(acos(-1.0));
			}

			output[k].setPx(Amplitude[k]);
			output[k].setPy(Angle[k]);
		}
	}
}

vector<Point2D> FourierTransform::getOuput()
{
	return output;
}
/*void FourierTransform::inverse()
{
	double u0;

	u0 = -acos(-1.0);

	for (int i=0;i<input.size();i++)
	{
		u0 -= (1/getTotalLength())*getCurveLength(i)*getAngleChange(i);
	}

	for (int i=0;i<output.size();i++)
	{
		output[i].setPx(u0);
		output[i].setPy(u0);
	}

	for (int k=0;k<input.size();k++)
	{
		for (int i=0;i<(input.size());i++)
		{
			double ak, bk;

			double l = getCurveLength(i);
			double L = getTotalLength();
			double t = 2*acos(-1.0)*l/L;

			output[k].setPx(output[k].getPx() - 1/(k*acos(-1.0))*getAngleChange(i)*sin(2*acos(-1.0)*k*getCurveLength(i)/getTotalLength())); 
			output[k].setPx(output[k].getPx() + 1/(k*acos(-1.0))*getAngleChange(i)*cos(2*acos(-1.0)*k*getCurveLength(i)/getTotalLength())); 
		}
	}
}*/



