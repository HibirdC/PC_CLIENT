/****************************************************************************
** Meta object code from reading C++ file 'TNNewFriendCard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNNewFriendCard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNNewFriendCard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNNewFriendCard_t {
    QByteArrayData data[11];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNNewFriendCard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNNewFriendCard_t qt_meta_stringdata_TNNewFriendCard = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TNNewFriendCard"
QT_MOC_LITERAL(1, 16, 10), // "slotAccept"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 10), // "slotReject"
QT_MOC_LITERAL(4, 39, 11), // "slotShowUrl"
QT_MOC_LITERAL(5, 51, 16), // "slotShowHerFrame"
QT_MOC_LITERAL(6, 68, 17), // "slotShowMineFrame"
QT_MOC_LITERAL(7, 86, 22), // "onAvatarDownLoadFinish"
QT_MOC_LITERAL(8, 109, 7), // "success"
QT_MOC_LITERAL(9, 117, 9), // "file_path"
QT_MOC_LITERAL(10, 127, 9) // "sessionId"

    },
    "TNNewFriendCard\0slotAccept\0\0slotReject\0"
    "slotShowUrl\0slotShowHerFrame\0"
    "slotShowMineFrame\0onAvatarDownLoadFinish\0"
    "success\0file_path\0sessionId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNNewFriendCard[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    3,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,    8,    9,   10,

       0        // eod
};

void TNNewFriendCard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNNewFriendCard *_t = static_cast<TNNewFriendCard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotAccept(); break;
        case 1: _t->slotReject(); break;
        case 2: _t->slotShowUrl(); break;
        case 3: _t->slotShowHerFrame(); break;
        case 4: _t->slotShowMineFrame(); break;
        case 5: _t->onAvatarDownLoadFinish((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject TNNewFriendCard::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TNNewFriendCard.data,
      qt_meta_data_TNNewFriendCard,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNNewFriendCard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNNewFriendCard::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNNewFriendCard.stringdata0))
        return static_cast<void*>(const_cast< TNNewFriendCard*>(this));
    return QWidget::qt_metacast(_clname);
}

int TNNewFriendCard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
