#include "backgroundscene.h"

BackgroundScene::BackgroundScene(QGraphicsView* v) : QGraphicsScene(v)
{
	secondPoint = 0;
	view = v;
}

void BackgroundScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
        BSplineCurve* bc = new BSplineCurve(this);

	ControlPoint *cp1 = new ControlPoint(bc);
	bc->addPoint(cp1);
	cp1->setPos(event->scenePos());

	ControlPoint *cp2 = new ControlPoint(bc);
	bc->addPoint(cp2);
	cp2->setPos(event->scenePos());

	addItem(bc);

	secondPoint = cp2;

	QGraphicsScene::mouseDoubleClickEvent(event);
}

void BackgroundScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if(secondPoint)
	{
		secondPoint->setPos(event->scenePos());

		this->update(secondPoint->bezierCurve->boundingRect());
	}

	QGraphicsScene::mouseMoveEvent(event);
}

void BackgroundScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	secondPoint = 0;

	QGraphicsScene::mousePressEvent(event);
}
