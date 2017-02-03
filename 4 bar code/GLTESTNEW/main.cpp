#include "gltestnew.h"
#include <QtGui/QApplication>
#include "PlanarFourBar.h"
#include <vector>
#include <math.h>
#include "FourierTransform.h"
#include "Link.h"
#include <iostream>

using namespace std;

#include "CurveComparison.h"
#include "Point2D.h"

int main(int argc, char *argv[])
{ 
	
	QApplication a(argc, argv);
	GLTESTNEW w;
	w.show();
	return a.exec();
}
