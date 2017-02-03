#include "PlanarFourBar.h"
#include <math.h>
#include <time.h>


double theta2; // class wide variable.
PlanarFourBar::PlanarFourBar(double r0, double r1, double r2, double r3, double r4, double r7, double t0, double t1, double g, bool ifcrossed)
{
	crossed = ifcrossed;
	r = r0;
	ground.setLength(r1);
	crank.setLength(r2);
	coupler.setLength(r3);
	rocker.setLength(r4);
	coupler.setCLength(r7);

	theta0 = t0;
	theta1 = t1;
	ground.setAngle(t1);
	coupler.setCAngle(g);

}

PlanarFourBar::PlanarFourBar(double r0, Link &gnd, Link &crnk, Coupler &cup, Link &rokr, double t0, double t1, bool ifcrossed)
{
	crossed = ifcrossed;
	r = r0;
	theta0 = t0;
	theta1 = t1;

	ground = gnd;
	ground.setAngle(t1);
	crank = crnk;
	coupler = cup;
	rocker = rokr;
}

void PlanarFourBar::setR(double r0)
{
	r = r0;
}

void PlanarFourBar::setTheta0(double ang)
{
	theta0 = ang;
}

void PlanarFourBar::setTheta1(double ang)
{
	theta1 = ang;
}

void PlanarFourBar::setCrnk(double len)
{
	crank.setLength(len);
}

void PlanarFourBar::setGnd(double len)
{
	ground.setLength(len);
}

void PlanarFourBar::setCplr(double L0, double gamma, double L1)
{
	coupler.setLength(L0);
	coupler.setCAngle(gamma);
	coupler.setCLength(L1);
}

void PlanarFourBar::setCplrLength1(double len)
{
	coupler.setLength(len);
}

void PlanarFourBar::setCplrLength2(double len)
{
	coupler.setCLength(len);
}

void PlanarFourBar::setCplrAngle(double ang)
{
	coupler.setCAngle(ang);
}

void PlanarFourBar::setRokr(double len)
{
	rocker.setLength(len);
}

double PlanarFourBar::getR()
{
	return r;
}

double PlanarFourBar::getTheta0()
{
	return theta0;
}

double PlanarFourBar::getTheta1()
{
	return theta1;
}

double PlanarFourBar::getGnd()
{
	return ground.getLength();
}

double PlanarFourBar::getCrnk()
{
	return crank.getLength();
}

double PlanarFourBar::getCplrLength1()
{
	return coupler.getLength();
}

double PlanarFourBar::getCplrLength2()
{
	return coupler.getCLength();
}

double PlanarFourBar::getCplrAngle()
{
	return coupler.getCAngle();
}

double PlanarFourBar::getRokr()
{
	return rocker.getLength();
}

double PlanarFourBar::getTheta3(bool crossed)
{
	// parameters for four bar
	double K1, K2, K3, K4, K5;
	double A, B, C, D, E, F;

	K1 = ground.getLength()/crank.getLength();
	K2 = ground.getLength()/rocker.getLength();
	K3 = (pow(crank.getLength(),2) - pow(coupler.getLength(),2) + pow(rocker.getLength(), 2) + pow(ground.getLength(),2))/(2*crank.getLength()*rocker.getLength());
	K4 = ground.getLength()/coupler.getLength();
	K5 = (pow(rocker.getLength(),2) - pow(ground.getLength(),2) - pow(crank.getLength(),2) - pow(coupler.getLength(),2))/(2*crank.getLength()*coupler.getLength());

	A = cos(crank.getAngle() - ground.getAngle()) - K1 - K2*cos(crank.getAngle() - ground.getAngle()) + K3;
	B = -2*sin(crank.getAngle() - ground.getAngle());
	C = K1 - (K2 + 1)*cos(crank.getAngle() - ground.getAngle()) + K3;
	D = cos(crank.getAngle() - ground.getAngle()) - K1 + K4*cos(crank.getAngle() - ground.getAngle()) + K5;
	E = B;
	F = K1 + (K4 - 1)*cos(crank.getAngle() - ground.getAngle()) + K5;

	double theta3;
	if (crossed)
	{
		theta3 = 2*atan((-E + sqrt(pow(E,2) - 4*D*F))/(2*D));
	}
	else
	{
		theta3 = 2*atan((-E - sqrt(pow(E,2) - 4*D*F))/(2*D));
	}
	return theta3;
}

double PlanarFourBar::getTheta4(bool crossed)
{
	// parameters for four bar
	double K1, K2, K3, K4, K5;
	double A, B, C, D, E, F;

	K1 = ground.getLength()/crank.getLength();
	K2 = ground.getLength()/rocker.getLength();
	K3 = (pow(crank.getLength(),2) - pow(coupler.getLength(),2) + pow(rocker.getLength(), 2) + pow(ground.getLength(),2))/(2*crank.getLength()*rocker.getLength());
	K4 = ground.getLength()/coupler.getLength();
	K5 = (pow(rocker.getLength(),2) - pow(ground.getLength(),2) - pow(crank.getLength(),2) - pow(coupler.getLength(),2))/(2*crank.getLength()*coupler.getLength());

	A = cos(crank.getAngle() - ground.getAngle()) - K1 - K2*cos(crank.getAngle()- ground.getAngle()) + K3;
	B = -2*sin(crank.getAngle()- ground.getAngle());
	C = K1 - (K2 + 1)*cos(crank.getAngle() - ground.getAngle()) + K3;
	D = cos(crank.getAngle() - ground.getAngle()) - K1 + K4*cos(crank.getAngle() - ground.getAngle()) + K5;
	E = B;
	F = K1 + (K4 - 1)*cos(crank.getAngle() - ground.getAngle()) + K5;

	

	double theta4;
	if (crossed)
	{
		theta4 = 2*atan((-B + sqrt(pow(B,2) - 4*A*C))/(2*A));
	}
	else
	{
		theta4 = 2*atan((-B - sqrt(pow(B,2) - 4*A*C))/(2*A));
	}

	
		return theta4;
	

	
}

void PlanarFourBar::drawMechanism(double angle, bool ifcrossed)
{
	Point2D pos(r*cos(theta0), r*sin(theta0));
	PlanarFourBar::crank.setPos(pos);
	PlanarFourBar::ground.setPos(pos);
	PlanarFourBar::crank.setAngle(angle + ground.getAngle());
	PlanarFourBar::coupler.setPos(crank.getPos2());
	PlanarFourBar::coupler.setAngle(getTheta3(ifcrossed) + ground.getAngle());
	PlanarFourBar::rocker.setPos(ground.getPos2());
	PlanarFourBar::rocker.setAngle(getTheta4(ifcrossed) + ground.getAngle());


	//coupler.setAngle(acos(-1.0)/2);
	PlanarFourBar::crank.draw();
	PlanarFourBar::coupler.draw();
	PlanarFourBar::rocker.draw();
}

void PlanarFourBar::animate(double speed, bool ifcrossed)
{
	theta2 = acos(-1.0)/4 + speed*(((float)clock())/CLOCKS_PER_SEC);
		if (theta2 >= 2*acos(-1.0))
	{
		theta2 -= (2*acos(-1.0));
	}

	drawMechanism(theta2, ifcrossed);
	
}

void PlanarFourBar::drawCurve(bool crossed)
{

	curve.resize(8200);
	double angle;
	for (double i=0.00;i<8200.0;i++)
	{
		angle = 2*acos(-1.0)*(i/8192);
	
	Point2D pos(r*cos(theta0), r*sin(theta0));
	PlanarFourBar::crank.setPos(pos);
	PlanarFourBar::ground.setPos(pos);
	PlanarFourBar::crank.setAngle(angle + ground.getAngle());
	PlanarFourBar::coupler.setPos(crank.getPos2());
	PlanarFourBar::coupler.setAngle(getTheta3(crossed) + ground.getAngle());
	curve[i] = coupler.getPos3();
	}
	
	

	curve.resize(8200);
}

void PlanarFourBar::makeCurve(bool ifcrossed)
{
	double angle;
	for (double i=0.00;i<8192.0;i++)
	{
		angle = 2*acos(-1.0)*(i/8192);
	
	Point2D pos(r*cos(theta0), r*sin(theta0));
	PlanarFourBar::crank.setPos(pos);
	PlanarFourBar::ground.setPos(pos);
	PlanarFourBar::crank.setAngle(angle + ground.getAngle());
	PlanarFourBar::coupler.setPos(crank.getPos2());
	PlanarFourBar::coupler.setAngle(getTheta3(ifcrossed) + ground.getAngle());
	realCurve.push_back(coupler.getPos3());
	}
	

	realCurve.resize(8192);
}

vector<Point2D> PlanarFourBar::getCurve()
{
	makeCurve();
	return realCurve;
}









