/****************************************************************************
** Meta object code from reading C++ file 'gameclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Nils/GameConnexion/gameclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gameclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GameClient_t {
    QByteArrayData data[15];
    char stringdata[195];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GameClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GameClient_t qt_meta_stringdata_GameClient = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 12),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 28),
QT_MOC_LITERAL(4, 54, 11),
QT_MOC_LITERAL(5, 66, 11),
QT_MOC_LITERAL(6, 78, 11),
QT_MOC_LITERAL(7, 90, 12),
QT_MOC_LITERAL(8, 103, 10),
QT_MOC_LITERAL(9, 114, 14),
QT_MOC_LITERAL(10, 129, 12),
QT_MOC_LITERAL(11, 142, 14),
QT_MOC_LITERAL(12, 157, 15),
QT_MOC_LITERAL(13, 173, 3),
QT_MOC_LITERAL(14, 177, 17)
    },
    "GameClient\0errorOccured\0\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "updateLobby\0connexionOk\0switchToGame\0"
    "launchGame\0mapCreationStr\0mapUpdateStr\0"
    "onErrorOccured\0onMessageRecive\0msg\0"
    "onClientConnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GameClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    0,   58,    2, 0x06 /* Public */,
       7,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   60,    2, 0x0a /* Public */,
      11,    1,   65,    2, 0x08 /* Private */,
      12,    1,   68,    2, 0x08 /* Private */,
      14,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,

       0        // eod
};

void GameClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GameClient *_t = static_cast<GameClient *>(_o);
        switch (_id) {
        case 0: _t->errorOccured((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 1: _t->updateLobby(); break;
        case 2: _t->connexionOk(); break;
        case 3: _t->switchToGame(); break;
        case 4: _t->launchGame((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->onErrorOccured((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->onMessageRecive((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->onClientConnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 5:
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
            typedef void (GameClient::*_t)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameClient::errorOccured)) {
                *result = 0;
            }
        }
        {
            typedef void (GameClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameClient::updateLobby)) {
                *result = 1;
            }
        }
        {
            typedef void (GameClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameClient::connexionOk)) {
                *result = 2;
            }
        }
        {
            typedef void (GameClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GameClient::switchToGame)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject GameClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GameClient.data,
      qt_meta_data_GameClient,  qt_static_metacall, 0, 0}
};


const QMetaObject *GameClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GameClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GameClient.stringdata))
        return static_cast<void*>(const_cast< GameClient*>(this));
    return QObject::qt_metacast(_clname);
}

int GameClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void GameClient::errorOccured(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GameClient::updateLobby()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GameClient::connexionOk()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GameClient::switchToGame()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
