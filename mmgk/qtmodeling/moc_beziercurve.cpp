/****************************************************************************
** Meta object code from reading C++ file 'beziercurve.h'
**
** Created: Sat May 29 17:44:05 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "beziercurve.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'beziercurve.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BSplineCurve[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

       0        // eod
};

static const char qt_meta_stringdata_BSplineCurve[] = {
    "BSplineCurve\0"
};

const QMetaObject BSplineCurve::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_BSplineCurve,
      qt_meta_data_BSplineCurve, 0 }
};

const QMetaObject *BSplineCurve::metaObject() const
{
    return &staticMetaObject;
}

void *BSplineCurve::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BSplineCurve))
        return static_cast<void*>(const_cast< BSplineCurve*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< BSplineCurve*>(this));
    return QObject::qt_metacast(_clname);
}

int BSplineCurve::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
