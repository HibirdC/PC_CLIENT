/****************************************************************************
** Meta object code from reading C++ file 'TNIMCoreClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNIMCoreClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNIMCoreClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNIMCoreClient_t {
    QByteArrayData data[9];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNIMCoreClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNIMCoreClient_t qt_meta_stringdata_TNIMCoreClient = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TNIMCoreClient"
QT_MOC_LITERAL(1, 15, 21), // "onSendNetDetectStatus"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 9), // "NetStatus"
QT_MOC_LITERAL(4, 48, 6), // "status"
QT_MOC_LITERAL(5, 55, 30), // "UpdateOrgGroupAndRelationSlots"
QT_MOC_LITERAL(6, 86, 23), // "UpdateFriendReMarkSlots"
QT_MOC_LITERAL(7, 110, 4), // "from"
QT_MOC_LITERAL(8, 115, 2) // "to"

    },
    "TNIMCoreClient\0onSendNetDetectStatus\0"
    "\0NetStatus\0status\0UpdateOrgGroupAndRelationSlots\0"
    "UpdateFriendReMarkSlots\0from\0to"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNIMCoreClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       5,    0,   32,    2, 0x0a /* Public */,
       6,    2,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,

       0        // eod
};

void TNIMCoreClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNIMCoreClient *_t = static_cast<TNIMCoreClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSendNetDetectStatus((*reinterpret_cast< NetStatus(*)>(_a[1]))); break;
        case 1: _t->UpdateOrgGroupAndRelationSlots(); break;
        case 2: _t->UpdateFriendReMarkSlots((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject TNIMCoreClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TNIMCoreClient.data,
      qt_meta_data_TNIMCoreClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNIMCoreClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNIMCoreClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNIMCoreClient.stringdata0))
        return static_cast<void*>(const_cast< TNIMCoreClient*>(this));
    return QObject::qt_metacast(_clname);
}

int TNIMCoreClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
