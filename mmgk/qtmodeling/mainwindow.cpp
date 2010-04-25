#include "mainwindow.h"

MainWindow::MainWindow()
{
	QGraphicsScene *scene = new BackgroundScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	scene->setSceneRect(0, 0, 400, 400);
	setScene(scene);
	//setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
	setResizeAnchor(AnchorViewCenter);

	BezierCurve* bc = new BezierCurve(scene);

	{
		ControlPoint *cp1 = new ControlPoint(bc);
		bc->addPoint(cp1);
		cp1->setPos(50, 50);
	}

	{
		ControlPoint *cp1 = new ControlPoint(bc);
		bc->addPoint(cp1);
		cp1->setPos(20, 50);
	}

	{
		ControlPoint *cp1 = new ControlPoint(bc);
		bc->addPoint(cp1);
		cp1->setPos(50, 20);
	}

	scene->addItem(bc);

	scale(qreal(0.8), qreal(0.8));
	setMinimumSize(400, 400);
	setWindowTitle(tr("Bezier Curves"));
}

MainWindow::~MainWindow()
{

}
