/****************************************************************************
** Meta object code from reading C++ file 'welcomemenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Nils/GameMenu/welcomemenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'welcomemenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WelcomeMenu_t {
    QByteArrayData data[8];
    char stringdata[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WelcomeMenu_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WelcomeMenu_t qt_meta_stringdata_WelcomeMenu = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 17),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 18),
QT_MOC_LITERAL(4, 50, 13),
QT_MOC_LITERAL(5, 64, 19),
QT_MOC_LITERAL(6, 84, 20),
QT_MOC_LITERAL(7, 105, 15)
    },
    "WelcomeMenu\0btHostGamePressed\0\0"
    "btJointGamePressed\0btQuitPressed\0"
    "onBtHostGamePressed\0onBtJointGamePressed\0"
    "onBtQuitPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WelcomeMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WelcomeMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WelcomeMenu *_t = static_cast<WelcomeMenu *>(_o);
        switch (_id) {
        case 0: _t->btHostGamePressed(); break;
        case 1: _t->btJointGamePressed(); break;
        case 2: _t->btQuitPressed(); break;
        case 3: _t->onBtHostGamePressed(); break;
        case 4: _t->onBtJointGamePressed(); break;
        case 5: _t->onBtQuitPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (WelcomeMenu::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WelcomeMenu::btHostGamePressed)) {
                *result = 0;
            }
        }
        {
            typedef void (WelcomeMenu::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WelcomeMenu::btJointGamePressed)) {
                *result = 1;
            }
        }
        {
            typedef void (WelcomeMenu::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&WelcomeMenu::btQuitPressed)) {
                *result = 2;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject WelcomeMenu::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_WelcomeMenu.data,
      qt_meta_data_WelcomeMenu,  qt_static_metacall, 0, 0}
};


const QMetaObject *WelcomeMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WelcomeMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WelcomeMenu.stringdata))
        return static_cast<void*>(const_cast< WelcomeMenu*>(this));
    return QWidget::qt_metacast(_clname);
}

int WelcomeMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WelcomeMenu::btHostGamePressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void WelcomeMenu::btJointGamePressed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void WelcomeMenu::btQuitPressed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
