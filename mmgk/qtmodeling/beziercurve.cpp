#include "beziercurve.h"

BezierCurve::BezierCurve()
{
}

void BezierCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::red);
    painter->setPen(QPen(Qt::black, 0));

    for (int i = 0; i < controlPoints.size() - 1; ++i)
		painter->drawLine(controlPoints.at(i)->pos(), controlPoints.at(i + 1)->pos());
}

void BezierCurve::append_control(ControlPoint* cp)
{
	controlPoints.append(cp);
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
	controlPoints.remove(controlPoints.indexOf(pt));
	update(boundingRect());
}
