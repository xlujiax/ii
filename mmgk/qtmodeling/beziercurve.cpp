#include "beziercurve.h"

BSplineCurve::BSplineCurve(BackgroundScene *s) : scene(s)
{
    drawControl = true;
    drawHull = true;
}

QPointF BSplineCurve::eval(float t)
{
    const int n = controlPoints.size();

    QPointF c[4][4];

    int j;
    for(j = 0; j < n; ++j)
        if(j <= t * n && t * n <= j+1)
            break;

    assert(j <= t * n && t * n <= j+1);

    for(int i = 0; i <= 3; ++i)
    {
        int index = i + j - 3;
        if(index < 0)
            c[i][0] = controlPoints[0]->pos();
        else
        {
            assert(0 <= index && index <= n);
            c[i][0] = controlPoints[index]->pos();
        }
    }

    for(int k = 1; k <= 3; ++k)
        for(int i = k; i <= 3; ++i)
        {
        float tleft = std::max(0.0f, float(j - 3 + i) / float(n));
        float tright = std::min(1.0f, float(j + i + 1 - k) / float(n));
        c[i][k] = ((t - tleft) * c[i][k-1] + (tright - t)*c[i-1][k-1]) / (tright - tleft);
    }

    return c[3][3];
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

    QVector<QPointF> pts = pointsOnCurve();

    QPainterPath path;
    path.moveTo(pts[0]);
    QPointF p;
    foreach(p, pts)
        path.lineTo(p);

    painter->drawPath(path);
}

QVector<QPointF> BSplineCurve::pointsOnCurve()
{
    const int intervals = controlPoints.size() - 1;

    if(intervals > 0)
    {
        const float segments = 20; // segments per interval

        QVector<QPointF> pts;
        pts.resize(intervals * segments + 1);


        for(int s = 0; s < segments; ++s)
        {
            float eps = float(s) / float(intervals * segments);


            const int n = controlPoints.size();
            QPointF c[8 + intervals][4];

            int j;
            for(j = 0; j < n; ++j)
                if(float(j) <= float(eps * intervals) && float(eps * intervals) < float(j+1))
                    break;

            assert(j == 0);


            // wypełnienie całego pierwszego wiersza
            for(int i = 0; i <= 7 + intervals; ++i)
            {
                int index = i + j - 3;
                if(index < 0)
                    c[i][0] = controlPoints[0]->pos();
                else if(index > n - 1)
                    c[i][0] = controlPoints[n-1]->pos();
                else
                {
                    assert(0 <= index && index < n);
                    c[i][0] = controlPoints[index]->pos();
                }
            }

            // wypełnienie górnego trójkąta
            for(int k = 1; k <= 3; ++k)
                for(int i = k; i <= 2; ++i)
                {
                float tleft = std::max(0.0f, float(j - 3 + i) / float(n));
                float tright = std::min(1.0f, float(j + i + 1 - k) / float(n));
                c[i][k] = ((eps - tleft) * c[i][k-1] + (tright - eps)*c[i-1][k-1]) / (tright - tleft);
            }

            for(int it = 0; it < intervals; ++it)
            {
                float t = float(it) / float(intervals) + eps;
                assert(0.0f <= t && t <= 1.0f);
                assert(it*segments + s < intervals * segments + 1);
                for(int k = 1; k <= 3; ++k)
                {
                    float tleft = std::max(0.0f, float(j - 3 + 3) / float(n));
                    float tright = std::min(1.0f, float(j + 3 + 1 - k) / float(n));
                    c[3 + it][k] = ((t - tleft) * c[3 + it][k-1] + (tright - t)*c[3-it-1][k-1]) / (tright - tleft);
                }

                pts[it*segments + s] = eval(t);//c[3+it][3];
            }
        }

        pts[intervals * segments] = eval(1);

        return pts;
    }
    else
        return QVector<QPointF>();
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

QPolygonF BSplineCurve::convex(QVector<QPointF> cp)
{
    QPolygonF poly;
    QPointF c1;
    QPointF c2;
    QPointF c3;
    foreach(c1, cp)
    {
        foreach(c2, cp)
        {
            foreach(c3, cp)
            {
                QVector<QPointF> p;
                p.append(c1);
                p.append(c2);
                p.append(c3);

                poly = poly.united(QPolygonF(p));
            }
        }
    }
    return poly;
}

void BSplineCurve::updateHull()
{
    hull = QPolygonF();
    if(controlPoints.size() < 3)
    {
    }
    else if(controlPoints.size() == 3)
    {
        QVector<QPointF> p;
        p.append(controlPoints[0]->pos());
        p.append(controlPoints[1]->pos());
        p.append(controlPoints[2]->pos());
        p.append(controlPoints[0]->pos());
        hull = QPolygonF(p);
    }
    else
    {
        for(int i = 0; i < controlPoints.size() - 3; ++i)
        {
            QVector<QPointF> p;
            p.append(controlPoints[i]->pos());
            p.append(controlPoints[i+1]->pos());
            p.append(controlPoints[i+2]->pos());
            p.append(controlPoints[i+3]->pos());
            p.append(controlPoints[i]->pos());

            hull = hull.united(convex(p));
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
    else if(selectedAction == saveAction)
    {
        saveCurve();
    }
    else if(selectedAction == loadAction)
    {
        loadCurve();
    }
}
