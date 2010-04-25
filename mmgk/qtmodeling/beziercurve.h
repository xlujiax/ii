#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <QGraphicsItem>
#include <QVector>
#include <QObject>
#include <cassert>
#include "controlpoint.h"

class ControlPoint;

class BezierCurve : public QObject, public QGraphicsItem
{
	Q_OBJECT
private:
	QVector<ControlPoint*> controlPoints;
public:
	BezierCurve(QGraphicsScene *scene);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


	QRectF boundingRect() const;

	void removePoint(ControlPoint*);
	void addPoint(ControlPoint*);

	QGraphicsScene *scene;

	QPoint eval(float t);
	void degreeRaise();

	bool drawControl;
};

#endif // BEZIERCURVE_H
