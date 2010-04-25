#include "beziercurve.h"

BezierCurve::BezierCurve(QGraphicsScene *s) : scene(s)
{
	drawControl = true;
}

QPoint BezierCurve::eval(float t)
{
	QPoint ret;

	const int n = controlPoints.size();

	float b[n][n];

	{
		for(int i = 0; i < n; ++i)
			b[0][i] = controlPoints.at(i)->x();

		for(int j = 1; j < n; ++j)
			for(int i = 0; i < n - j; ++i)
				b[j][i] = (1.0f - t) * b[j-1][i] + t * b[j-1][i+1];

		ret.setX(b[n-1][0]);
	}

	{
		for(int i = 0; i < n; ++i)
			b[0][i] = controlPoints.at(i)->y();

		for(int j = 1; j < n; ++j)
			for(int i = 0; i < n - j; ++i)
				b[j][i] = (1.0f - t) * b[j-1][i] + t * b[j-1][i+1];

		ret.setY(b[n-1][0]);
	}
	return ret;
}

void BezierCurve::degreeRaise()
{
	const int n = controlPoints.size();
	const int m = n + 1;


	ControlPoint* t = new ControlPoint(this);
	t->setPos(controlPoints.at(n - 1)->pos());
	scene->addItem(t);
	controlPoints.append(t);

	for(int i = n-1; i >= 1; --i)
	{
		ControlPoint* t = new ControlPoint(this);

		float xx = (i*controlPoints.at(i-1)->x()+(m-i - 1)*controlPoints.at(i)->x())/((float)m - 1);
		float yy = (i*controlPoints.at(i-1)->y()+(m-i - 1)*controlPoints.at(i)->y())/((float)m - 1);
		t->setPos(QPoint(xx, yy));

		scene->removeItem(controlPoints.at(i));
		scene->addItem(t);
		controlPoints.replace(i, t);
	}

	update(boundingRect());
}

void BezierCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::black, 0));

	if(drawControl)
	{
		for (int i = 0; i < controlPoints.size() - 1; ++i)
			painter->drawLine(controlPoints.at(i)->pos(), controlPoints.at(i + 1)->pos());
	}

	const float prec = 0.01;

	QPoint bef = eval(0);
	for(float t = prec; t < 1; t += prec)
	{
		QPoint act = eval(t);
		painter->drawLine(bef, act);
		bef = act;
	}
	painter->drawLine(bef, eval(1));
}

QRectF BezierCurve::boundingRect() const
{
	float adjust = 10;

	if(controlPoints.empty())
		return QRect(0,0,0,0);
	else
	{
		float minx = controlPoints.at(0)->x();
		float maxx = controlPoints.at(0)->x();
		float miny = controlPoints.at(0)->y();
		float maxy = controlPoints.at(0)->y();

		ControlPoint* cp;
		foreach(cp, controlPoints)
		{
			if(cp->x() < minx)
				minx = cp->x();
			if(cp->x() > maxx)
				maxx = cp->x();
			if(cp->y() < miny)
				miny = cp->y();
			if(cp->y() > maxy)
				maxy = cp->y();
		}

		return QRect(minx - adjust, miny - adjust, maxx - minx + 2* adjust, maxy - miny + 2* adjust);
	}
}

void BezierCurve::removePoint(ControlPoint* pt)
{
	assert(controlPoints.indexOf(pt) != -1);

	scene->removeItem(pt);
	controlPoints.remove(controlPoints.indexOf(pt));
	update(boundingRect());
}
void BezierCurve::addPoint(ControlPoint* pt)
{
	assert(controlPoints.indexOf(pt) == -1);

	scene->addItem(pt);
	controlPoints.append(pt);
	update(boundingRect());
}
