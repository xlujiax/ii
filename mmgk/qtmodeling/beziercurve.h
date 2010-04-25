#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <QGraphicsItem>
#include <QVector>
#include <QObject>
#include "controlpoint.h"

class ControlPoint;

class BezierCurve : public QObject, public QGraphicsItem
{
	Q_OBJECT
private:
	QVector<ControlPoint*> controlPoints;
public:
    BezierCurve();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void append_control(ControlPoint*);

	QRectF boundingRect() const;

	void removePoint(ControlPoint*);
};

#endif // BEZIERCURVE_H
