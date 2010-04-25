#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "beziercurve.h"
#include "controlpoint.h"

class MainWindow : public QGraphicsView
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
};

#endif // MAINWINDOW_H
