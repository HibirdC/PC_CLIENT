/****************************************************************************
** Meta object code from reading C++ file 'ListAreaBase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ListAreaBase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ListAreaBase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ListAreaBase_t {
    QByteArrayData data[8];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ListAreaBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ListAreaBase_t qt_meta_stringdata_ListAreaBase = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ListAreaBase"
QT_MOC_LITERAL(1, 13, 13), // "OnMessageSlot"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "TNMessageListAdapter"
QT_MOC_LITERAL(4, 49, 18), // "messageListAdapter"
QT_MOC_LITERAL(5, 68, 14), // "showDetailArea"
QT_MOC_LITERAL(6, 83, 16), // "OnUnreadedUpdate"
QT_MOC_LITERAL(7, 100, 8) // "toFeedId"

    },
    "ListAreaBase\0OnMessageSlot\0\0"
    "TNMessageListAdapter\0messageListAdapter\0"
    "showDetailArea\0OnUnreadedUpdate\0"
    "toFeedId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListAreaBase[] = {

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
       6,    1,   29,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void ListAreaBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ListAreaBase *_t = static_cast<ListAreaBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnMessageSlot((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->OnUnreadedUpdate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ListAreaBase::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ListAreaBase.data,
      qt_meta_data_ListAreaBase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ListAreaBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ListAreaBase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ListAreaBase.stringdata0))
        return static_cast<void*>(const_cast< ListAreaBase*>(this));
    return QWidget::qt_metacast(_clname);
}

int ListAreaBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
