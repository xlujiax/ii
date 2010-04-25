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

class ControlPoint : public QGraphicsItem
{
public:
    ControlPoint();

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
};

#endif // CONTROLPOINT_H
