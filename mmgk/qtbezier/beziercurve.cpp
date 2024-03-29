#include "beziercurve.h"

BezierCurve::BezierCurve(QGraphicsScene *s) : scene(s)
{
	drawControl = true;
	drawHull = true;
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

	BezierCurve *right = controlPoints.at(n - 1)->secondBezierCurve;
	BezierCurve *left = controlPoints.at(0)->secondBezierCurve;

	ControlPoint* tf = new ControlPoint(this);
	tf->setPos(controlPoints.at(n - 1)->pos());
	tf->secondBezierCurve = right;
	if(right)
		right->controlPoints.at(0)->secondBezierCurve = this;
	scene->addItem(tf);
	controlPoints.append(tf);

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

	controlPoints.at(0)->secondBezierCurve = left;
	if(left)
		left->controlPoints.at(left->controlPoints.size() - 1)->secondBezierCurve = this;

	update(boundingRect());
	updateHull();
}

void BezierCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setRenderHint(QPainter::Antialiasing);

	if(drawControl)
	{
		painter->setPen(QPen(Qt::gray, 1));
		for (int i = 0; i < controlPoints.size() - 1; ++i)
			painter->drawLine(controlPoints.at(i)->pos(), controlPoints.at(i + 1)->pos());
	}

	if(drawHull)
	{
		painter->setPen(QPen(Qt::red, 0));
		painter->drawPolyline(hull);
	}

	painter->setPen(QPen(Qt::black, 2));
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

void BezierCurve::updateHull()
{
	hull = QPolygonF();
	ControlPoint* c1;
	ControlPoint* c2;
	ControlPoint* c3;
	foreach(c1, controlPoints)
	{
		foreach(c2, controlPoints)
		{
			foreach(c3, controlPoints)
			{
				if(c1 != c2 && c2 != c3 && c1 != c3)
				{
					QVector<QPointF> p;
					p.append(c1->pos());
					p.append(c2->pos());
					p.append(c3->pos());

					hull = hull.united(QPolygonF(p));
				}
			}
		}
	}
}

void BezierCurve::removePoint(ControlPoint* pt)
{
	assert(controlPoints.indexOf(pt) != -1);

	scene->removeItem(pt);
	controlPoints.remove(controlPoints.indexOf(pt));
	updateHull();
	update(boundingRect());
}

void BezierCurve::addPoint(ControlPoint* pt)
{
	assert(controlPoints.indexOf(pt) == -1);

	scene->addItem(pt);
	controlPoints.append(pt);
	updateHull();
	update(boundingRect());
}

void BezierCurve::removeCurve()
{
	scene->removeItem(this);
	ControlPoint* cp;
	foreach(cp, controlPoints)
		scene->removeItem(cp);
	updateHull();
}

void BezierCurve::saveCurve()
{
	QString fileName = QFileDialog::getOpenFileName(0,
	 tr("Open file"), "/home/foo", tr("*.cur"));


	QFile file(fileName);
	 if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		 return;

	 QTextStream out(&file);
	 out << controlPoints.size() << '\n';
	 ControlPoint* cp;
	 foreach(cp, controlPoints)
		 out << cp->x() << ' ' << cp->y() << '\n';
}
void BezierCurve::loadCurve()
{
	QString fileName = QFileDialog::getOpenFileName(0,
	 tr("Open file"), "/home/foo", tr("*.cur"));

	QFile file(fileName);
	 if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		 return;

	 QTextStream in(&file);
	 int sz;
	 in >> sz;


	 ControlPoint* cp;
	 foreach(cp, controlPoints)
		 scene->removeItem(cp);
	 controlPoints.clear();

	 qreal x, y;
	 for(int i = 0; i < sz; ++i)
	 {
		 in >> x >> y;

		 ControlPoint *cp = new ControlPoint(this);
		 addPoint(cp);
		 cp->setPos(QPoint(x, y));
	 }
	 update(boundingRect());
}

void BezierCurve::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
	if(!hull.containsPoint(event->pos(), Qt::WindingFill))
	{
		event->ignore();
		return;

	}
	QMenu menu;
	QAction *controlAction = menu.addAction("Toggle control view");
	QAction *hullAction = menu.addAction("Toggle hull view");
	QAction *removeAction = menu.addAction("Remove curve");
	QAction *addAction = menu.addAction("Add control point");
	QAction *saveAction = menu.addAction("Save curve");
	QAction *loadAction = menu.addAction("Load curve");
	QAction *selectedAction = menu.exec(event->screenPos());

	if(selectedAction == controlAction)
	{
		drawControl = !drawControl;
		update(boundingRect());
	}
	else if(selectedAction == hullAction)
	{
		drawHull = !drawHull;
		update(boundingRect());
	}
	else if(selectedAction == removeAction)
	{
		removeCurve();
	}
	else if(selectedAction == addAction)
	{
		degreeRaise();
	}
	else if(selectedAction == saveAction)
	{
		saveCurve();
	}
	else if(selectedAction == loadAction)
	{
		loadCurve();
	}
}
