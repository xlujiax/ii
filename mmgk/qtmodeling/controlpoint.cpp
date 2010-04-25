#include "controlpoint.h"

ControlPoint::ControlPoint(BezierCurve* bc) : bezierCurve(bc)
{
     setFlag(ItemIsMovable);
     //setCacheMode(DeviceCoordinateCache);
     setAcceptHoverEvents(true);
     setAcceptDrops(true);

	 setZValue(1);

     size = 15;
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
	QMenu menu;
	QAction *removeAction = menu.addAction("Remove point");
	QAction *addAction = menu.addAction("Add point");
    QAction *selectedAction = menu.exec(event->screenPos());

	if(selectedAction == removeAction)
	{
		removeFromCurve();
	}
	else if(selectedAction == addAction)
	{
		bezierCurve->degreeRaise();
	}
}

void ControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsItem::mouseMoveEvent(event);
	bezierCurve->update(bezierCurve->boundingRect());
	event->accept();
}

void ControlPoint::removeFromCurve()
{
	bezierCurve->removePoint(this);
	update(boundingRect());
}
