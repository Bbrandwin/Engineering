
#include <math.h>
#include <GL/glut.h>

#include "Link.h"

Link::Link(double len, double ang)
{
	length = len;
	angle = ang;
	position.setPx(0);
	position.setPy(0);

}

void Link::setLength(double len)
{
	length = len;
}

void Link::setAngle(double ang)
{
	angle = ang;
}

void Link::setPos(Point2D pos)
{
	position = pos;
}

void Link::setPos(double x, double y)
{
	position.setPx(x);
	position.setPy(y);
}

double Link::getLength()
{
	return length;
}

double Link::getAngle()
{
	return angle;
}

Point2D Link::getPos1()
{
	return position;
}

// the getPos2 function allows us to easily set the next Link according to the first
Point2D Link::getPos2()
{
	Point2D pos2;

	pos2.setPx(position.getPx() + length*cos(angle));
	pos2.setPy(position.getPy() + length*sin(angle));

	return pos2;
}

void Link::draw()
{
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(3);
	glBegin(GL_LINE_STRIP);
	    glVertex3f(getPos1().getPx(),getPos1().getPy(), 0.0f);
	    glVertex3f(getPos2().getPx(),getPos2().getPy(), 0.0f);
	glEnd();

}



	



