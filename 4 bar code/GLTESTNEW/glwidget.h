#ifndef GLWIDGET_H
 #define GLWIDGET_H

 #include <QtOpenGl/QGLWidget>

 class QtLogo;

 class GLWidget : public QGLWidget
 {
     Q_OBJECT

 public:
     GLWidget(QWidget *parent = 0);
     ~GLWidget();

     QSize minimumSizeHint() const;
     QSize sizeHint() const;

 public slots:
     void setXRotation(int angle);
     void setYRotation(int angle);
     void setZRotation(int angle);
	 void setSpeed(double speed);
	 void setCrossed(bool);

	 //some extra slots for adjusting the mechanism
	 void setGndLength(double);
	 void setCrnkLength(double);
	 void setCplrLength(double);
	 void setCplrLength2(double);
	 void setRokrLength(double);
	 void setGndAngle(double);
	 void setCplrAngle(double);
	 void setR0(double); // length to mechanism
	 void setTheta0(double); //angle to mechanism


 signals:
     void xRotationChanged(int angle);
     void yRotationChanged(int angle);
     void zRotationChanged(int angle);
	 void speedChanged(double speed);


 protected:
     void initializeGL();
     void paintGL();
     void resizeGL(int width, int height);
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);

 private:
     //QtLogo *logo;
     int xRot;
     int yRot;
     int zRot;
	 double speed;
	 bool ifcrossed;

     QPoint lastPos;
     QColor qtGreen;
     QColor qtPurple;
 };

 #endif