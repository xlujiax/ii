#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <QGraphicsItem>
#include <QVector>
#include <QObject>
#include <QPolygon>
#include <QFileDialog>
#include <QString>
#include <QtAlgorithms>
#include <cassert>
#include "controlpoint.h"

class ControlPoint;

class BezierCurve : public QObject, public QGraphicsItem
{
	Q_OBJECT
private:
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
	bool drawHull;
	QVector<ControlPoint*> controlPoints;

	QPolygonF hull;
	void updateHull();
	void removeCurve();

	void saveCurve();
	void loadCurve();

	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
};

#endif // BEZIERCURVE_H
