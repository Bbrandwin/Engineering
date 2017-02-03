#include <iostream>
#include <QtGui/QtGui> 
#include <QtOpenGL/qgl.h>
#include <QtCore/qdebug.h>
#include <math.h>	
#include <GL/glut.h>
#include "BSplineTweak.h"
#include "glwidget.h" 
#include <vector>
#include "Link.h"
#include "Coupler.h"
#include "PlanarFourBar.h"
#include <time.h> 
#include "FourierTransform.h"
#include <fstream> 

using namespace std;
 //#include "qtlogo.h"

 #ifndef GL_MULTISAMPLE
 #define GL_MULTISAMPLE  0x809D
 #endif



BSplineTweak F1;
BSplineTweak *D = &F1;



Link ground(0.4);
Link crank(0.2);
Coupler coupler(0.4);
Link rocker(0.4);
static PlanarFourBar fourBar(0, ground, crank, coupler, rocker, 0, acos(-1.0)/4, 0);




 GLWidget::GLWidget(QWidget *parent)
     : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
 {
     //logo = 0;

     xRot = 0;
     yRot = 0;
     zRot = 0;

     qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
     qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
 }

 GLWidget::~GLWidget()
 {
 }

 QSize GLWidget::minimumSizeHint() const
 {
     return QSize(50, 50);
 }

 QSize GLWidget::sizeHint() const
 {
     return QSize(400, 400);
 }

 static void qNormalizeAngle(int &angle)
 {
     while (angle < 0)
         angle += 360 * 16;
     while (angle > 360 * 16)
         angle -= 360 * 16;
 }



 void GLWidget::setXRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != xRot) {
         xRot = angle;
         emit xRotationChanged(angle);
         updateGL();
     }
 }

 void GLWidget::setYRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != yRot) {
         yRot = angle;
         emit yRotationChanged(angle);
         updateGL();
     }
 }

 void GLWidget::setZRotation(int angle)
 {
     qNormalizeAngle(angle);
     if (angle != zRot) {
         zRot = angle;
         emit zRotationChanged(angle);
         updateGL();
     }
 }

 void GLWidget::initializeGL()
 {
	 
	 setCrossed(1);
	 speed = 0;
     qglClearColor(qtPurple.dark());

     //logo = new QtLogo(this, 64);
     //logo->setColor(qtGreen.dark());

     glEnable(GL_DEPTH_TEST);
     glEnable(GL_CULL_FACE);
     glShadeModel(GL_SMOOTH);
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     glEnable(GL_MULTISAMPLE);
     static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
     glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
 }

 void GLWidget::paintGL()
 {

	/* vector<Point2D> curvePoints;
	vector<Point2D> transPoints;
	curvePoints = fourBar.getCurve();
	FourierTransform T(curvePoints);
	T.forward();
	transPoints = T.getOuput();*/
	  
	 int lines;
	 
	 
	double *in = new double[10];
	ifstream Input("LinkageData.txt");
if (Input)
{
	for (int i=0;i<10;i++)
	{
		double ins;
		Input >> in[i];  
		
		
	}
}
ofstream o ("Test.txt");
if(o){
for(int y=0;y<10;y++)
{
	o << in[y] << endl;
}
o.close();
}
fourBar.setR(0);
fourBar.ground.setLength(in[0]/100);
fourBar.crank.setLength(in[1]/100);
fourBar.coupler.setLength(in[2]/100);
fourBar.rocker.setLength(in[3]/100);
fourBar.ground.setAngle(in[6]);
fourBar.coupler.setCLength(in[7]/100);
fourBar.coupler.setCAngle(in[8]);


     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     glTranslatef(-0.0, -0.0, -9.0);
     glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
     glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
	 //glRotatef(16.0 , 0.0, 0.0, ground.getAngle());
	 //glColor3f(0.0,1.0,0.0);
	 

	 fourBar.drawCurve(ifcrossed);
	 fourBar.animate(speed, ifcrossed);
	 
	 glBegin(GL_LINE_STRIP);{
	 glColor3f(1.0,0.0,0.0);
	 glLineWidth(3);
	 for (int i=0; i<fourBar.curve.size()/8;i++)
	 {
		 glVertex3f(fourBar.curve[8*i].getPx(), fourBar.curve[8*i].getPy(), 0.0f);
	 }
	 }glEnd();

	 /*glBegin(GL_LINE_STRIP);
	 glLineWidth(3);
	 if (D->F.size() >=0)
	 {
	 for (int i=0;i<D->splitAndTweak(10).size();i++)
	 {
		 glVertex3f(D->splitAndTweak(10)[i].getPx(), D->splitAndTweak(10)[i].getPy(), 0.0f);
	 }
	 }
	 glEnd();*/

	 update();
	 
	 
	 //glTranslatef(0.0, 0.2, 0.0);
	 //C1.draw();
     //logo->draw();
	//glFrontFace(GL_CW);
	//glutSolidTeapot(.2);
	//glFrontFace(GL_CCW);
	/* vector<Point2D> P2D;
	 if (D->F.size() > 0)
	 {
		// P2D = D->splitAndTweak(10); 
	 
		 glBegin(GL_LINE_STRIP);

		 for (int i=0;i<P2D.size();i++)
		 {
			 glVertex2f(D->splitAndTweak(10)[i].getPx(),D->splitAndTweak(10)[i].getPy());

		 }
		 glEnd();
	 }*/
		 //D->draw();

 }

 void GLWidget::resizeGL(int width, int height)
 {
     int side = qMin(width, height);
     glViewport((width - side) / 2, (height - side) / 2, side, side);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
 #ifdef QT_OPENGL_ES_1
     glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
 #else
     glOrtho(-side/300, +side/300, -side/300, +side/300, 4.0, 15.0);
 #endif
     glMatrixMode(GL_MODELVIEW);
 }

 void GLWidget::mousePressEvent(QMouseEvent *event)
 {
     lastPos = event->pos();
	 Point2D P2D(lastPos.x(), lastPos.y());
	 D->F.push_back(P2D);
	 
	 
 }

 void GLWidget::mouseMoveEvent(QMouseEvent *event)
 {
     int dx = event->x() - lastPos.x();
     int dy = event->y() - lastPos.y();

	/* if (event->buttons() & Qt::LeftButton & Qt::Key_Down)
	 {
		 Point2D P2D(lastPos.x(),lastPos.y());
		 D->F.push_back(P2D);
		 cout << "point added" << P2D.getPx() << ", " << P2D.getPy() << endl;
	 }*/
    /* if (event->buttons() & Qt::LeftButton) {
         setXRotation(xRot + 8 * dy);
         setYRotation(yRot + 8 * dx);
		 setZRotation(zRot + 4 * dx);
     } else if (event->buttons() & Qt::RightButton) {
         setXRotation(xRot + 8 * dy);
         setZRotation(zRot + 8 * dx);
     } 
     lastPos = event->pos();*/
 } 

 void GLWidget::setSpeed(double spd)
 {
	 speed = spd;
	 emit speedChanged(speed);
 }

 void GLWidget::setCrossed(bool crossed)
 {
	 GLWidget::ifcrossed = crossed;
 }

 void GLWidget::setGndLength(double len)
 {
	 fourBar.ground.setLength(len);
 }

 void GLWidget::setCrnkLength(double len)
 {
	 fourBar.crank.setLength(len);
 }

 void GLWidget::setCplrLength(double len)
 {
	 fourBar.coupler.setLength(len);
 }

 void GLWidget::setRokrLength(double len)
 {
	 fourBar.rocker.setLength(len);
 }

 void GLWidget::setGndAngle(double ang)
 {
	 fourBar.ground.setAngle(ang);
 }

 void GLWidget::setCplrAngle(double ang)
 {
	 fourBar.coupler.setCAngle(ang);
 }

 void GLWidget::setCplrLength2(double len)
 {
	 fourBar.coupler.setCLength(len);
 }

 void GLWidget::setR0(double len)
 {
	 fourBar.setR(len);
 }

 void GLWidget::setTheta0(double ang)
 {
	 fourBar.setTheta0(ang);
 }

