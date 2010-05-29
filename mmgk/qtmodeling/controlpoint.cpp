#include "controlpoint.h"

ControlPoint::ControlPoint(BSplineCurve* bc) : bsplineCurve(bc)
{
    setFlag(ItemIsMovable);
    //setCacheMode(DeviceCoordinateCache);
    setAcceptHoverEvents(true);
    setAcceptDrops(true);

    setZValue(1);


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
    assert(false);
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
    QAction *nextAction = 0;
    if(bsplineCurve->controlPoints.endsWith(this))
        nextAction = menu.addAction("Next point");
    QAction *selectedAction = menu.exec(event->screenPos());

    if(selectedAction == removeAction)
    {
        removeFromCurve();
    }

    else if(bsplineCurve->controlPoints.endsWith(this) && selectedAction == nextAction)
    {
        ControlPoint *cp = new ControlPoint(bsplineCurve);
        cp->setPos(event->scenePos());
        bsplineCurve->addPoint(cp);

        bsplineCurve->scene->secondPoint = cp;

        event->accept();
    }

    event->accept();
}

void ControlPoint::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    QGraphicsItem::mouseMoveEvent(event);
    bsplineCurve->updateHull();
    bsplineCurve->scene->update(bsplineCurve->boundingRect());

    event->accept();
}

void ControlPoint::removeFromCurve()
{
    bsplineCurve->removePoint(this);
    bsplineCurve->updateHull();
    update(boundingRect());
}
