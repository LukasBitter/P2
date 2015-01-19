/****************************************************************************
** Meta object code from reading C++ file 'lobbymenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Nils/GameMenu/lobbymenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lobbymenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LobbyMenu_t {
    QByteArrayData data[18];
    char stringdata[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LobbyMenu_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LobbyMenu_t qt_meta_stringdata_LobbyMenu = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 12),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 4),
QT_MOC_LITERAL(4, 29, 12),
QT_MOC_LITERAL(5, 42, 2),
QT_MOC_LITERAL(6, 45, 18),
QT_MOC_LITERAL(7, 64, 14),
QT_MOC_LITERAL(8, 79, 14),
QT_MOC_LITERAL(9, 94, 8),
QT_MOC_LITERAL(10, 103, 10),
QT_MOC_LITERAL(11, 114, 9),
QT_MOC_LITERAL(12, 124, 28),
QT_MOC_LITERAL(13, 153, 3),
QT_MOC_LITERAL(14, 157, 17),
QT_MOC_LITERAL(15, 175, 18),
QT_MOC_LITERAL(16, 194, 16),
QT_MOC_LITERAL(17, 211, 21)
    },
    "LobbyMenu\0returnToMenu\0\0play\0GameContext*\0"
    "gc\0mapSelectionUpdate\0enableClientUI\0"
    "enableServerUI\0updateUI\0launchGame\0"
    "showError\0QAbstractSocket::SocketError\0"
    "err\0onBtReturnPressed\0onBtConnectPressed\0"
    "onBtStartPressed\0onSuccessfulConnexion"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LobbyMenu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,
       6,    0,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    1,   83,    2, 0x08 /* Private */,
      14,    0,   86,    2, 0x08 /* Private */,
      15,    0,   87,    2, 0x08 /* Private */,
      16,    0,   88,    2, 0x08 /* Private */,
      17,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LobbyMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LobbyMenu *_t = static_cast<LobbyMenu *>(_o);
        switch (_id) {
        case 0: _t->returnToMenu(); break;
        case 1: _t->play((*reinterpret_cast< GameContext*(*)>(_a[1]))); break;
        case 2: _t->mapSelectionUpdate(); break;
        case 3: _t->enableClientUI(); break;
        case 4: _t->enableServerUI(); break;
        case 5: _t->updateUI(); break;
        case 6: _t->launchGame(); break;
        case 7: _t->showError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 8: _t->onBtReturnPressed(); break;
        case 9: _t->onBtConnectPressed(); break;
        case 10: _t->onBtStartPressed(); break;
        case 11: _t->onSuccessfulConnexion(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LobbyMenu::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LobbyMenu::returnToMenu)) {
                *result = 0;
            }
        }
        {
            typedef void (LobbyMenu::*_t)(GameContext * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LobbyMenu::play)) {
                *result = 1;
            }
        }
        {
            typedef void (LobbyMenu::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LobbyMenu::mapSelectionUpdate)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject LobbyMenu::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LobbyMenu.data,
      qt_meta_data_LobbyMenu,  qt_static_metacall, 0, 0}
};


const QMetaObject *LobbyMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LobbyMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LobbyMenu.stringdata))
        return static_cast<void*>(const_cast< LobbyMenu*>(this));
    return QWidget::qt_metacast(_clname);
}

int LobbyMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void LobbyMenu::returnToMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void LobbyMenu::play(GameContext * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LobbyMenu::mapSelectionUpdate()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
