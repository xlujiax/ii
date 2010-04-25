#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <QGraphicsItem>
#include <QVector>
#include "controlpoint.h"

class BezierCurve : public QGraphicsItem
{
private:
	QVector<ControlPoint*> controlPoints;
public:
    BezierCurve();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void append_control(ControlPoint*);

	QRectF boundingRect() const;
};

#endif // BEZIERCURVE_H
