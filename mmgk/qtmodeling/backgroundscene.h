#ifndef BACKGROUNDSCENE_H
#define BACKGROUNDSCENE_H

#include <QMenu>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

#include "beziercurve.h"
#include "controlpoint.h"

class BSplineCurve;
class ControlPoint;

class BackgroundScene : public QGraphicsScene
{
	QGraphicsView* view;
public:
	BackgroundScene(QGraphicsView* view);

	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* mouseEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	ControlPoint* secondPoint;
};

#endif // BACKGROUNDSCENE_H
