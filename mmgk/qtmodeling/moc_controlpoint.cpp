/****************************************************************************
** Meta object code from reading C++ file 'controlpoint.h'
**
** Created: Sat May 29 21:46:28 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "controlpoint.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlpoint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ControlPoint[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ControlPoint[] = {
    "ControlPoint\0\0removeFromCurve()\0"
};

const QMetaObject ControlPoint::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ControlPoint,
      qt_meta_data_ControlPoint, 0 }
};

const QMetaObject *ControlPoint::metaObject() const
{
    return &staticMetaObject;
}

void *ControlPoint::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControlPoint))
        return static_cast<void*>(const_cast< ControlPoint*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< ControlPoint*>(this));
    return QObject::qt_metacast(_clname);
}

int ControlPoint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: removeFromCurve(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
