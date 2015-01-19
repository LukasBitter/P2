/****************************************************************************
** Meta object code from reading C++ file 'powerinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Nils/GameComponent/GameInterface/powerinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'powerinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PowerInterface_t {
    QByteArrayData data[17];
    char stringdata[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PowerInterface_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PowerInterface_t qt_meta_stringdata_PowerInterface = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 12),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 10),
QT_MOC_LITERAL(4, 40, 4),
QT_MOC_LITERAL(5, 45, 15),
QT_MOC_LITERAL(6, 61, 5),
QT_MOC_LITERAL(7, 67, 1),
QT_MOC_LITERAL(8, 69, 21),
QT_MOC_LITERAL(9, 91, 21),
QT_MOC_LITERAL(10, 113, 4),
QT_MOC_LITERAL(11, 118, 2),
QT_MOC_LITERAL(12, 121, 14),
QT_MOC_LITERAL(13, 136, 21),
QT_MOC_LITERAL(14, 158, 27),
QT_MOC_LITERAL(15, 186, 27),
QT_MOC_LITERAL(16, 214, 20)
    },
    "PowerInterface\0powerPressed\0\0POWER_NAME\0"
    "name\0usePowerDestroy\0Node*\0n\0"
    "usePowerInvincibility\0usePowerTeleportation\0"
    "from\0to\0usePowerArmore\0btPowerDestroyPressed\0"
    "btPowerInvincibilityPressed\0"
    "btPowerTeleportationPressed\0"
    "btPowerArmorePressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PowerInterface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   62,    2, 0x0a /* Public */,
       8,    1,   65,    2, 0x0a /* Public */,
       9,    2,   68,    2, 0x0a /* Public */,
      12,    1,   73,    2, 0x0a /* Public */,
      13,    0,   76,    2, 0x08 /* Private */,
      14,    0,   77,    2, 0x08 /* Private */,
      15,    0,   78,    2, 0x08 /* Private */,
      16,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,   10,   11,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PowerInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PowerInterface *_t = static_cast<PowerInterface *>(_o);
        switch (_id) {
        case 0: _t->powerPressed((*reinterpret_cast< POWER_NAME(*)>(_a[1]))); break;
        case 1: _t->usePowerDestroy((*reinterpret_cast< Node*(*)>(_a[1]))); break;
        case 2: _t->usePowerInvincibility((*reinterpret_cast< Node*(*)>(_a[1]))); break;
        case 3: _t->usePowerTeleportation((*reinterpret_cast< Node*(*)>(_a[1])),(*reinterpret_cast< Node*(*)>(_a[2]))); break;
        case 4: _t->usePowerArmore((*reinterpret_cast< Node*(*)>(_a[1]))); break;
        case 5: _t->btPowerDestroyPressed(); break;
        case 6: _t->btPowerInvincibilityPressed(); break;
        case 7: _t->btPowerTeleportationPressed(); break;
        case 8: _t->btPowerArmorePressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PowerInterface::*_t)(POWER_NAME ) const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PowerInterface::powerPressed)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject PowerInterface::staticMetaObject = {
    { &QGraphicsWidget::staticMetaObject, qt_meta_stringdata_PowerInterface.data,
      qt_meta_data_PowerInterface,  qt_static_metacall, 0, 0}
};


const QMetaObject *PowerInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PowerInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PowerInterface.stringdata))
        return static_cast<void*>(const_cast< PowerInterface*>(this));
    return QGraphicsWidget::qt_metacast(_clname);
}

int PowerInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void PowerInterface::powerPressed(POWER_NAME _t1)const
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< PowerInterface *>(this), &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
