/****************************************************************************
** Meta object code from reading C++ file 'gamemenumanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Nils/GameMenu/gamemenumanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamemenumanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GameMenuManager_t {
    QByteArrayData data[8];
    char stringdata[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameMenuManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameMenuManager_t qt_meta_stringdata_GameMenuManager = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 12),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 15),
QT_MOC_LITERAL(4, 46, 17),
QT_MOC_LITERAL(5, 64, 8),
QT_MOC_LITERAL(6, 73, 12),
QT_MOC_LITERAL(7, 86, 2)
    },
    "GameMenuManager\0returnToMenu\0\0"
    "goToLobbyAsHost\0goToLobbyAsClient\0"
    "goToGame\0GameContext*\0gc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameMenuManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    1,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void GameMenuManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameMenuManager *_t = static_cast<GameMenuManager *>(_o);
        switch (_id) {
        case 0: _t->returnToMenu(); break;
        case 1: _t->goToLobbyAsHost(); break;
        case 2: _t->goToLobbyAsClient(); break;
        case 3: _t->goToGame((*reinterpret_cast< GameContext*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject GameMenuManager::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GameMenuManager.data,
      qt_meta_data_GameMenuManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *GameMenuManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameMenuManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameMenuManager.stringdata))
        return static_cast<void*>(const_cast< GameMenuManager*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GameMenuManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
