
#include <math.h>
#include "Coupler.h"
#include <GL/glut.h>



Coupler::Coupler(double len, double ang, double cLen, double cAng)
	: Link(len, ang)
{

	couplerLength = cLen;
	couplerAngle = cAng;

	cAngleTransform();
}

void Coupler::setLength(double len)
{
	length = len;
	cAngleTransform();
}

void Coupler::setAngle(double ang)
{
	angle = ang;
	cAngleTransform();
}

void Coupler::setCLength(double len)
{
	couplerLength = len;
	cAngleTransform();
}

void Coupler::setCAngle(double ang)
{
	couplerAngle = ang;
	cAngleTransform();
}

double Coupler::getCLength()
{
	return couplerLength;
}

double Coupler::getCAngle()
{
	return couplerAngle;
}

Point2D Coupler::getPos3()
{
	//cAngleTransform();
	return pos3;
}


void Coupler::draw()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	{
	    glVertex3f(getPos1().getPx(), getPos1().getPy(), 0.0f);
	    glVertex3f(getPos2().getPx(), getPos2().getPy(), 0.0f);
	    glVertex3f(getPos3().getPx(), getPos3().getPy(), 0.0f);
	}glEnd();

}


void Coupler::cAngleTransform()
{
	double xPoint, yPoint, xPrime, yPrime;

	xPoint = couplerLength*cos(couplerAngle);
	yPoint = couplerLength*sin(couplerAngle);

	xPrime = (xPoint*cos(angle) - yPoint*sin(angle));
	yPrime = (xPoint*sin(angle) + yPoint*cos(angle));

	pos3.setPx(getPos2().getPx() + xPrime);
	pos3.setPy(getPos2().getPy() + yPrime);

} 

