/****************************************************************************
** Meta object code from reading C++ file 'CardCase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CardCase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CardCase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CardCase_t {
    QByteArrayData data[7];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CardCase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CardCase_t qt_meta_stringdata_CardCase = {
    {
QT_MOC_LITERAL(0, 0, 8), // "CardCase"
QT_MOC_LITERAL(1, 9, 16), // "on_notifyRefresh"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "type"
QT_MOC_LITERAL(4, 32, 19), // "QList<UINotifyData>"
QT_MOC_LITERAL(5, 52, 9), // "dataListo"
QT_MOC_LITERAL(6, 62, 23) // "slotUpdateNewFriendPage"

    },
    "CardCase\0on_notifyRefresh\0\0type\0"
    "QList<UINotifyData>\0dataListo\0"
    "slotUpdateNewFriendPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CardCase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x0a /* Public */,
       6,    0,   29,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void,

       0        // eod
};

void CardCase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CardCase *_t = static_cast<CardCase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_notifyRefresh((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QList<UINotifyData>(*)>(_a[2]))); break;
        case 1: _t->slotUpdateNewFriendPage(); break;
        default: ;
        }
    }
}

const QMetaObject CardCase::staticMetaObject = {
    { &PluginExportBase::staticMetaObject, qt_meta_stringdata_CardCase.data,
      qt_meta_data_CardCase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CardCase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CardCase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CardCase.stringdata0))
        return static_cast<void*>(const_cast< CardCase*>(this));
    return PluginExportBase::qt_metacast(_clname);
}

int CardCase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PluginExportBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
