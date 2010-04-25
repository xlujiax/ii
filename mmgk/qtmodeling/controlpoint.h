#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QGraphicsItem>
#include <QStyleOption>
#include <QMenu>
#include <QDebug>

#include "mainwindow.h"
#include "beziercurve.h"

class BezierCurve;

class ControlPoint : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	ControlPoint(BezierCurve* bezierCurve);
	virtual ~ControlPoint() {}

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    float size;

    bool selected;
    bool hover;
	BezierCurve* bezierCurve;
protected:

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);

public slots:
	void removeFromCurve();
};

#endif // CONTROLPOINT_H
