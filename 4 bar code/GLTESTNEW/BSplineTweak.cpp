// BSplineTweak.cpp
// BSplineTweak class member function definition

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <math.h>
#include <QtGui/QtGui> 
#include <QtOpenGL/qgl.h>
#include <QtCore/qdebug.h>
using namespace std;

#include "BSplineTweak.h"
#include "Point2D.h"

extern BSplineTweak *D;
const int number_points = 20;

// constructor 


BSplineTweak::BSplineTweak()
{
	
	degree = -1;

}



// destructor
BSplineTweak::~BSplineTweak()
{

}

/*void BSplineTweak::setPx( int Number, double xValue )
{
	(F[Number]).setPx(xValue);

}

double BSplineTweak::getPx( int Number )
{
	return (F[Number]).getPx();

}

void BSplineTweak::setPy( int Number, double yValue )
{
	(F[Number]).setPy( yValue );

}

double BSplineTweak::getPy( int Number )
{
	return (F[Number]).getPy();

}*/

/*void BSplineTweak::draw() 
{
	curve = F;

	size = curve.size();

	glColor3f(0.0, 1.0, 0.0);
	glPointSize(8.0);
	glBegin(GL_POINTS);
	for (unsigned i=0; i< F.size(); i++)
	glVertex2f((F[i]).getPx(), (F[i]).getPy() );
	glEnd();

	glColor3d (1.0, 0.0, 0.0);
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	for (unsigned k = 0; k < F.size(); k++ )
	glVertex2f( (F[k]).getPx(), (F[k]).getPy() );
	glVertex2f(F[0].getPx(), F[0].getPy());

	glEnd();

	glColor3f(1.0f, 0.0f, 0.8f);
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
		if (D->degree > 1)
		
		//if (D->degree >= 1)
		//tweak(tempF, t);
		for (unsigned i=0;i<10;i++)
		{
			splitAndTweak();
			//glVertex2f(Px, Py);
		}

	//uncomment below to close the loop
	for (int i=0;i<size;i++)
	glVertex2f(curve[i].getPx(), curve[i].getPy());
	glVertex2f(curve[0].getPx(), curve[0].getPy());
	glEnd();

		
}

// FrPoint_algorithm function
/*void BSplineTweak::FrPoint_algorithm( double &x, double &y, double t )
{
	
	vector<Point2D> tempF = F;

	for (unsigned r=1; r< split().size(); r++)
		for (unsigned i=0; i<split().size()-r; i++)
		{

			tempF[i].setPx( (1.0-t)*tempF[i].getPx() + t*tempF[i+1].getPx() );
			tempF[i].setPy( (1.0-t)*tempF[i].getPy() + t*tempF[i+1].getPy() );
		}
		x = tempF[0].getPx();
		y = tempF[0].getPy();		

}*/

int BSplineTweak::getDegree() 
{
	return degree;
}

void BSplineTweak::setDegree( int d)
{
	degree = d;
}

vector<Point2D> BSplineTweak::splitAndTweak(int iteration)
{
	for (int i=0;i<iteration;i++)
	{
	double **curvePoints;

	curvePoints = new double*[size*2];
	
	for (int i=0;i<size*2;i++)
		curvePoints[i] = new double[2];


	// first iteration begin

	for (int i=0;i<size;i++)
	{
		curvePoints[2*i][0] = (F[i].getPx());
		curvePoints[2*i][1] = (F[i].getPy());
	}
	for (int i=0;i<size-1;i++)
	{
		curvePoints[2*i+1][0] = ((F[i].getPx() + F[i+1].getPx())/2);
		curvePoints[2*i+1][1] = ((F[i].getPy() + F[i+1].getPy())/2);
	}

	curvePoints[2*size-1][0] = ((F[0].getPx() + F[size-1].getPx())/2);
	curvePoints[2*size-1][1] = ((F[0].getPy() + F[size-1].getPy())/2);

	// start tweak
	curvePoints[0][0] = (curvePoints[0][0] + (curvePoints[1][0] + curvePoints[size*2-1][0])/2)/2;
	curvePoints[0][1] = (curvePoints[0][1] + (curvePoints[1][1] + curvePoints[size*2-1][1])/2)/2;
	for (int i=1;i<size;i++)
	{
		curvePoints[2*i][0] = (curvePoints[2*i][0] + (curvePoints[2*i-1][0] + curvePoints[2*i+1][0])/2)/2;
		curvePoints[2*i][1] = (curvePoints[2*i][1] + (curvePoints[2*i-1][1] + curvePoints[2*i+1][1])/2)/2;
	} 

	curve.reserve(2*size);
	for (int i=0;i<size*2;i++)
	{
	
		curve[i].setPx(curvePoints[i][0]);
		curve[i].setPy(curvePoints[i][1]);
	}

	size = size*2;
	}
	
	return curve;
}

		
