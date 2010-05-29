#include "beziercurve.h"

BSplineCurve::BSplineCurve(BackgroundScene *s) : scene(s)
{
	drawControl = true;
	drawHull = true;
}

QPoint BSplineCurve::eval(float t)
{
    QPoint ret;

    const int n = controlPoints.size() - 1;

    float c[4][4];

    int j;
    for(j = 0; j < n; ++j)
        if(j <= t * n && t * n <= j+1)
            break;

    for(int i = 0; i <= 3; ++i)
    {
        int index = i + j - 3;
        if(index < 0)
            c[i][0] = controlPoints[0]->x();
        else
        {
            assert(0 <= index && index <= n);
            c[i][0] = controlPoints[index]->x();
        }
    }

    for(int k = 1; k <= 3; ++k)
        for(int i = k; i <= 3; ++i)
        {
            float tleft;
            if(j - 3 + i < 0)
                tleft = controlPoints[0]->x();
            else
            {
                assert(0 <= j-3+i && j-3+i <= n);
                tleft = controlPoints[j-3+i]->x();
            }
            float tright;
            if(j + i + 1 - k > n)
                tright = controlPoints[n]->x();
            else
            {
                assert(0 <= j + i + 1 - k && j + i + 1 - k <= n);
                float tright = controlPoints[j + i + 1 - k]->x();
            }
            c[i][k] = ((t - tleft) * c[i][k-1] + (tright - t)*c[i-1][k-1]) / (tright - tleft);
        }

    ret.setX(c[j][3]);

    // y

    for(int i = 0; i <= 3; ++i)
    {
        int index = i + j - 3;
        if(index < 0)
            c[i][0] = controlPoints[0]->y();
        else
        {
            assert(0 <= index && index <= n);
            c[i][0] = controlPoints[index]->y();
        }
    }

    for(int k = 1; k <= 3; ++k)
        for(int i = k; i <= 3; ++i)
        {
            float tleft;
            if(j - 3 + i < 0)
                tleft = controlPoints[0]->y();
            else
            {
                assert(0 <= j-3+i && j-3+i <= n);
                tleft = controlPoints[j-3+i]->y();
            }
            float tright;
            if(j + i + 1 - k > n)
                tright = controlPoints[n]->y();
            else
            {
                assert(0 <= j + i + 1 - k && j + i + 1 - k <= n);
                float tright = controlPoints[j + i + 1 - k]->y();
            }
            c[i][k] = ((t - tleft) * c[i][k-1] + (tright - t)*c[i-1][k-1]) / (tright - tleft);
        }

    ret.setY(c[j][3]);

    return ret;
}

void BSplineCurve::degreeRaise()
{
    assert(false);
}

void BSplineCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

QRectF BSplineCurve::boundingRect() const
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

void BSplineCurve::updateHull()
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

void BSplineCurve::removePoint(ControlPoint* pt)
{
	assert(controlPoints.indexOf(pt) != -1);

	scene->removeItem(pt);
	controlPoints.remove(controlPoints.indexOf(pt));
	updateHull();
	update(boundingRect());
}

void BSplineCurve::addPoint(ControlPoint* pt)
{
	assert(controlPoints.indexOf(pt) == -1);

	scene->addItem(pt);
	controlPoints.append(pt);
	updateHull();
	update(boundingRect());
}

void BSplineCurve::removeCurve()
{
	scene->removeItem(this);
	ControlPoint* cp;
	foreach(cp, controlPoints)
		scene->removeItem(cp);
	updateHull();
}

void BSplineCurve::saveCurve()
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
void BSplineCurve::loadCurve()
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

void BSplineCurve::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
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
