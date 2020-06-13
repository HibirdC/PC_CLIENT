/****************************************************************************
** Meta object code from reading C++ file 'CardCaseDetailsArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CardCaseDetailsArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CardCaseDetailsArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CardCaseDetailsArea_t {
    QByteArrayData data[22];
    char stringdata0[292];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CardCaseDetailsArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CardCaseDetailsArea_t qt_meta_stringdata_CardCaseDetailsArea = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CardCaseDetailsArea"
QT_MOC_LITERAL(1, 20, 23), // "slotShowNewFriendNotice"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 21), // "OnListAreaClickedSlot"
QT_MOC_LITERAL(4, 67, 5), // "index"
QT_MOC_LITERAL(5, 73, 23), // "OnColleagueListAreaSlot"
QT_MOC_LITERAL(6, 97, 19), // "OnGroupListAreaSlot"
QT_MOC_LITERAL(7, 117, 23), // "OnGroupChatListAreaSlot"
QT_MOC_LITERAL(8, 141, 26), // "slotModifiedGroupChatInfos"
QT_MOC_LITERAL(9, 168, 21), // "on_notifyReMarkUpdate"
QT_MOC_LITERAL(10, 190, 4), // "from"
QT_MOC_LITERAL(11, 195, 2), // "to"
QT_MOC_LITERAL(12, 198, 6), // "remark"
QT_MOC_LITERAL(13, 205, 7), // "sources"
QT_MOC_LITERAL(14, 213, 24), // "feedCardUpdateFromCatche"
QT_MOC_LITERAL(15, 238, 6), // "feedId"
QT_MOC_LITERAL(16, 245, 8), // "avatarId"
QT_MOC_LITERAL(17, 254, 4), // "name"
QT_MOC_LITERAL(18, 259, 7), // "subName"
QT_MOC_LITERAL(19, 267, 6), // "userId"
QT_MOC_LITERAL(20, 274, 6), // "namePy"
QT_MOC_LITERAL(21, 281, 10) // "sourceType"

    },
    "CardCaseDetailsArea\0slotShowNewFriendNotice\0"
    "\0OnListAreaClickedSlot\0index\0"
    "OnColleagueListAreaSlot\0OnGroupListAreaSlot\0"
    "OnGroupChatListAreaSlot\0"
    "slotModifiedGroupChatInfos\0"
    "on_notifyReMarkUpdate\0from\0to\0remark\0"
    "sources\0feedCardUpdateFromCatche\0"
    "feedId\0avatarId\0name\0subName\0userId\0"
    "namePy\0sourceType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CardCaseDetailsArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    1,   55,    2, 0x0a /* Public */,
       5,    1,   58,    2, 0x0a /* Public */,
       6,    1,   61,    2, 0x0a /* Public */,
       7,    1,   64,    2, 0x0a /* Public */,
       8,    1,   67,    2, 0x0a /* Public */,
       9,    4,   70,    2, 0x0a /* Public */,
      14,    7,   79,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,   15,   16,   17,   18,   19,   20,   21,

       0        // eod
};

void CardCaseDetailsArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CardCaseDetailsArea *_t = static_cast<CardCaseDetailsArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotShowNewFriendNotice(); break;
        case 1: _t->OnListAreaClickedSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->OnColleagueListAreaSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->OnGroupListAreaSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->OnGroupChatListAreaSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->slotModifiedGroupChatInfos((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->on_notifyReMarkUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 7: _t->feedCardUpdateFromCatche((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7]))); break;
        default: ;
        }
    }
}

const QMetaObject CardCaseDetailsArea::staticMetaObject = {
    { &TNWebViewDetailsArea::staticMetaObject, qt_meta_stringdata_CardCaseDetailsArea.data,
      qt_meta_data_CardCaseDetailsArea,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CardCaseDetailsArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CardCaseDetailsArea::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CardCaseDetailsArea.stringdata0))
        return static_cast<void*>(const_cast< CardCaseDetailsArea*>(this));
    return TNWebViewDetailsArea::qt_metacast(_clname);
}

int CardCaseDetailsArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TNWebViewDetailsArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
