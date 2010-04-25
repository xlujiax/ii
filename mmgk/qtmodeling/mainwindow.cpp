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

	BezierCurve* bc = new BezierCurve;

	{
		ControlPoint *cp1 = new ControlPoint();
		scene->addItem(cp1);
		cp1->setPos(-50, -50);
		bc->append_control(cp1);
	}

	{
		ControlPoint *cp1 = new ControlPoint();
		scene->addItem(cp1);
		cp1->setPos(0, -50);
		bc->append_control(cp1);
	}

	{
		ControlPoint *cp1 = new ControlPoint();
		scene->addItem(cp1);
		cp1->setPos(0, 0);
		bc->append_control(cp1);
	}

	scene->addItem(bc);

	scale(qreal(0.8), qreal(0.8));
	setMinimumSize(400, 400);
	setWindowTitle(tr("Elastic Nodes"));
}

MainWindow::~MainWindow()
{

}
