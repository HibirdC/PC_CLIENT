/****************************************************************************
** Meta object code from reading C++ file 'noticelistdelegate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../list_notice/noticelistdelegate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'noticelistdelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NoticeListDelegate_t {
    QByteArrayData data[6];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NoticeListDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NoticeListDelegate_t qt_meta_stringdata_NoticeListDelegate = {
    {
QT_MOC_LITERAL(0, 0, 18), // "NoticeListDelegate"
QT_MOC_LITERAL(1, 19, 14), // "downLoadAvator"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 20), // "TNMessageListAdapter"
QT_MOC_LITERAL(4, 56, 7), // "adapter"
QT_MOC_LITERAL(5, 64, 16) // "onDownLoadAvator"

    },
    "NoticeListDelegate\0downLoadAvator\0\0"
    "TNMessageListAdapter\0adapter\0"
    "onDownLoadAvator"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoticeListDelegate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void NoticeListDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NoticeListDelegate *_t = static_cast<NoticeListDelegate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downLoadAvator((*reinterpret_cast< const TNMessageListAdapter(*)>(_a[1]))); break;
        case 1: _t->onDownLoadAvator((*reinterpret_cast< const TNMessageListAdapter(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NoticeListDelegate::*_t)(const TNMessageListAdapter & ) const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListDelegate::downLoadAvator)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject NoticeListDelegate::staticMetaObject = {
    { &QStyledItemDelegate::staticMetaObject, qt_meta_stringdata_NoticeListDelegate.data,
      qt_meta_data_NoticeListDelegate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NoticeListDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoticeListDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NoticeListDelegate.stringdata0))
        return static_cast<void*>(const_cast< NoticeListDelegate*>(this));
    return QStyledItemDelegate::qt_metacast(_clname);
}

int NoticeListDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void NoticeListDelegate::downLoadAvator(const TNMessageListAdapter & _t1)const
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< NoticeListDelegate *>(this), &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
