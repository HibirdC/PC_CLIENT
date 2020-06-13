/****************************************************************************
** Meta object code from reading C++ file 'MineListArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MineListArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MineListArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MineListArea_t {
    QByteArrayData data[27];
    char stringdata0[328];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MineListArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MineListArea_t qt_meta_stringdata_MineListArea = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MineListArea"
QT_MOC_LITERAL(1, 13, 21), // "ListMineToDetailEvent"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "index"
QT_MOC_LITERAL(4, 42, 15), // "CloseDetailPage"
QT_MOC_LITERAL(5, 58, 4), // "feed"
QT_MOC_LITERAL(6, 63, 10), // "belongFeed"
QT_MOC_LITERAL(7, 74, 24), // "feedCardUpdateFromCatche"
QT_MOC_LITERAL(8, 99, 6), // "feedId"
QT_MOC_LITERAL(9, 106, 8), // "avatarId"
QT_MOC_LITERAL(10, 115, 4), // "name"
QT_MOC_LITERAL(11, 120, 7), // "subName"
QT_MOC_LITERAL(12, 128, 6), // "userId"
QT_MOC_LITERAL(13, 135, 6), // "namePy"
QT_MOC_LITERAL(14, 142, 10), // "sourceType"
QT_MOC_LITERAL(15, 153, 21), // "OnListAreaClickedSlot"
QT_MOC_LITERAL(16, 175, 22), // "onAvatarDownLoadFinish"
QT_MOC_LITERAL(17, 198, 7), // "success"
QT_MOC_LITERAL(18, 206, 3), // "url"
QT_MOC_LITERAL(19, 210, 20), // "needToDownLoadAvatar"
QT_MOC_LITERAL(20, 231, 4), // "type"
QT_MOC_LITERAL(21, 236, 20), // "on_notifyKeyEventDis"
QT_MOC_LITERAL(22, 257, 8), // "keyEvent"
QT_MOC_LITERAL(23, 266, 19), // "currentSelectedPage"
QT_MOC_LITERAL(24, 286, 4), // "page"
QT_MOC_LITERAL(25, 291, 16), // "on_notifyRefresh"
QT_MOC_LITERAL(26, 308, 19) // "QList<UINotifyData>"

    },
    "MineListArea\0ListMineToDetailEvent\0\0"
    "index\0CloseDetailPage\0feed\0belongFeed\0"
    "feedCardUpdateFromCatche\0feedId\0"
    "avatarId\0name\0subName\0userId\0namePy\0"
    "sourceType\0OnListAreaClickedSlot\0"
    "onAvatarDownLoadFinish\0success\0url\0"
    "needToDownLoadAvatar\0type\0"
    "on_notifyKeyEventDis\0keyEvent\0"
    "currentSelectedPage\0page\0on_notifyRefresh\0"
    "QList<UINotifyData>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MineListArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    2,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    7,   67,    2, 0x0a /* Public */,
      15,    1,   82,    2, 0x0a /* Public */,
      16,    3,   85,    2, 0x0a /* Public */,
      19,    3,   92,    2, 0x0a /* Public */,
      21,    1,   99,    2, 0x0a /* Public */,
      23,    1,  102,    2, 0x0a /* Public */,
      25,    2,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    8,    9,   10,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,   17,   18,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    8,   18,   20,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 26,    2,    2,

       0        // eod
};

void MineListArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MineListArea *_t = static_cast<MineListArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ListMineToDetailEvent((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->CloseDetailPage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->feedCardUpdateFromCatche((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7]))); break;
        case 3: _t->OnListAreaClickedSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->onAvatarDownLoadFinish((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: _t->needToDownLoadAvatar((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->on_notifyKeyEventDis((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->currentSelectedPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_notifyRefresh((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QList<UINotifyData>(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MineListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MineListArea::ListMineToDetailEvent)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MineListArea::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MineListArea::CloseDetailPage)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MineListArea::staticMetaObject = {
    { &ListAreaBase::staticMetaObject, qt_meta_stringdata_MineListArea.data,
      qt_meta_data_MineListArea,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MineListArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MineListArea::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MineListArea.stringdata0))
        return static_cast<void*>(const_cast< MineListArea*>(this));
    return ListAreaBase::qt_metacast(_clname);
}

int MineListArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ListAreaBase::qt_metacall(_c, _id, _a);
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
void MineListArea::ListMineToDetailEvent(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MineListArea::CloseDetailPage(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
