#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include <algorithm>
#include <QGraphicsItem>
#include <QVector>
#include <QObject>
#include <QPolygon>
#include <QFileDialog>
#include <QString>
#include <QtAlgorithms>
#include <cassert>
#include "controlpoint.h"
#include "backgroundscene.h"

class BackgroundScene;
class ControlPoint;

class BSplineCurve : public QObject, public QGraphicsItem
{
	Q_OBJECT
private:
public:
    BSplineCurve(BackgroundScene *scene);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    QRectF boundingRect() const;

    void removePoint(ControlPoint*);
    void addPoint(ControlPoint*);

    BackgroundScene *scene;

    QPointF eval(float t);
    void degreeRaise();

    bool drawControl;
    bool drawHull;
    QVector<ControlPoint*> controlPoints;

    QPolygonF hull;
    QPolygonF convex(QVector<QPointF>);
    void updateHull();
    void removeCurve();

    void saveCurve();
    void loadCurve();

    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
};

#endif // BEZIERCURVE_H
