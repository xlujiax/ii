#include "mainwindow.h"

MainWindow::MainWindow()
{
	QGraphicsScene *scene = new QGraphicsScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	scene->setSceneRect(-200, -200, 400, 400);
	setScene(scene);
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
	setResizeAnchor(AnchorViewCenter);

	BezierCurve* bc = new BezierCurve(scene);

	{
		ControlPoint *cp1 = new ControlPoint(bc);
		bc->addPoint(cp1);
		cp1->setPos(-50, -50);
	}

	{
		ControlPoint *cp1 = new ControlPoint(bc);
		bc->addPoint(cp1);
		cp1->setPos(0, -50);
	}

	{
		ControlPoint *cp1 = new ControlPoint(bc);
		bc->addPoint(cp1);
		cp1->setPos(0, 0);
	}

	scene->addItem(bc);

	scale(qreal(0.8), qreal(0.8));
	setMinimumSize(400, 400);
	setWindowTitle(tr("Bezier Curves"));
}

MainWindow::~MainWindow()
{

}
