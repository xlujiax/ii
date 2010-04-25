#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QGraphicsItem>
#include <QStyleOption>
#include <QMenu>
#include <QObject>
#include <QDebug>

#include "mainwindow.h"
#include "beziercurve.h"

class BezierCurve;

class ControlPoint : public QGraphicsItem
{
private:
	BezierCurve* bezierCurve;
public:
	ControlPoint(BezierCurve* bezierCurve);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    float size;

    bool selected;
    bool hover;
protected:

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
};

#endif // CONTROLPOINT_H
