#include "controlpoint.h"

ControlPoint::ControlPoint(BezierCurve* bc) : bezierCurve(bc)
{
     setFlag(ItemIsMovable);
     //setCacheMode(DeviceCoordinateCache);
     setAcceptHoverEvents(true);
     setAcceptDrops(true);

	 setZValue(1);

	 secondBezierCurve = 0;
	 linkedCp = 0;

	 size = 10;
     hover = false;
	 selected = false;
}

QRectF ControlPoint::boundingRect() const
 {
     return QRectF(-size / 2, -size / 2,
                   size, size);
 }

 QPainterPath ControlPoint::shape() const
 {
     QPainterPath path;
     path.addEllipse(-size / 2, -size / 2, size, size);
     return path;
 }

 void ControlPoint::split()
 {
	 int find = bezierCurve->controlPoints.indexOf(this);
	 assert(find != -1);
	 ControlPoint* cp;

	 BezierCurve* left = new BezierCurve(bezierCurve->scene);
	 BezierCurve* right = new BezierCurve(bezierCurve->scene);

	 QRectF r = bezierCurve->boundingRect();

	 for(int i = 0; i < bezierCurve->controlPoints.size(); ++i)
	 {
		 if(i <= find)
			 left->controlPoints.append(bezierCurve->controlPoints[i]);
		 if(i >= find)
			 right->controlPoints.append(bezierCurve->controlPoints[i]);
		 bezierCurve->scene->removeItem(bezierCurve->controlPoints[i]);
	 }

	 bezierCurve->scene->removeItem(bezierCurve);
	 bezierCurve->scene->update(r);

	 foreach(cp, left->controlPoints)
	 {
		 cp->bezierCurve = left;
		 bezierCurve->scene->addItem(cp);
	 }
	 left->updateHull();
	 bezierCurve->scene->addItem(left);


	 foreach(cp, right->controlPoints)
	 {
		 cp->bezierCurve = right;
		 bezierCurve->scene->addItem(cp);
	 }
	 right->updateHull();
	 bezierCurve->scene->addItem(right);

	 bezierCurve = left;
	 secondBezierCurve = right;

	 left->controlPoints.at(left->controlPoints.size() - 2)->linkedCp = right->controlPoints.at(1);
	 right->controlPoints.at(1)->linkedCp = left->controlPoints.at(left->controlPoints.size() - 2);
 }

 void ControlPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
 {
	painter->setRenderHint(QPainter::Antialiasing);
     if(selected)
        painter->setBrush(Qt::red);
     else
     {
         if(hover)
			painter->setBrush(Qt::yellow);
         else
            painter->setBrush(Qt::white);
     }
	painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-size / 2, -size / 2, size, size);
 }

void ControlPoint::hoverEnterEvent(QGraphicsSceneHoverEvent * )
{
    hover = true;
    update(-size / 2, -size / 2, size, size);
}
void ControlPoint::hoverLeaveEvent(QGraphicsSceneHoverEvent * )
{
    hover = false;
    update(-size / 2, -size / 2, size, size);
}
void ControlPoint::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	//selected = !selected;
	//update(-size / 2, -size / 2, size, size);

	event->accept();
}

void ControlPoint::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	int find = bezierCurve->controlPoints.indexOf(this);
	bool outer = false;
	if(find == 0 || find == bezierCurve->controlPoints.size() - 1)
		outer = true;

	QMenu menu;
	QAction *removeAction = menu.addAction("Remove point");
	QAction *addAction = menu.addAction("Add point");
	QAction *splitAction = 0;
	if(!outer)
		splitAction = menu.addAction("Split and join");
    QAction *selectedAction = menu.exec(event->screenPos());

	if(selectedAction == removeAction)
	{
		removeFromCurve();
	}
	else if(selectedAction == addAction)
	{
		bezierCurve->degreeRaise();
	}
	else if(selectedAction == splitAction && !outer)
	{
		split();
	}
}

void ControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsItem::mouseMoveEvent(event);
	bezierCurve->updateHull();
	bezierCurve->scene->update(bezierCurve->boundingRect());

	if(secondBezierCurve)
	{
		secondBezierCurve->updateHull();
		secondBezierCurve->scene->update(secondBezierCurve->boundingRect());
	}
	event->accept();
}

void ControlPoint::removeFromCurve()
{
	bezierCurve->removePoint(this);
	bezierCurve->updateHull();
	update(boundingRect());
}
