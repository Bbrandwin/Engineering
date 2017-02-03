#ifndef GLTESTNEW_H
#define GLTESTNEW_H

#include <QtGui/QMainWindow>
#include "ui_gltestnew.h"

class GLTESTNEW : public QMainWindow
{
	Q_OBJECT

public:
	GLTESTNEW(QWidget *parent = 0, Qt::WFlags flags = 0);
	~GLTESTNEW();

private:
	Ui::GLTESTNEWClass ui;
};

#endif // GLTESTNEW_H
