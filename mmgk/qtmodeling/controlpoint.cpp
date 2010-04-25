#include "controlpoint.h"

ControlPoint::ControlPoint(BezierCurve* bc) : bezierCurve(bc)
{
     setFlag(ItemIsMovable);
     //setCacheMode(DeviceCoordinateCache);
     setAcceptHoverEvents(true);
     setAcceptDrops(true);

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
     if(selected)
        painter->setBrush(Qt::red);
     else
     {
         if(hover)
            painter->setBrush(Qt::darkGray);
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
    selected = !selected;
    update(-size / 2, -size / 2, size, size);

	event->accept();
}

void ControlPoint::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    QMenu menu;
    QAction *removeAction = menu.addAction("Remove");
    QAction *markAction = menu.addAction("Mark");
    QAction *selectedAction = menu.exec(event->screenPos());
}

void ControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
	QGraphicsItem::mouseMoveEvent(event);
	bezierCurve->update(bezierCurve->boundingRect());
	event->accept();
}
