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

	scale(qreal(0.8), qreal(0.8));
	setMinimumSize(400, 400);
	setWindowTitle(tr("Bezier Curves"));
}

MainWindow::~MainWindow()
{

}
