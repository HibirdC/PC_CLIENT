/****************************************************************************
** Meta object code from reading C++ file 'TNAbstractItemDelegate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNAbstractItemDelegate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNAbstractItemDelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNAbstractItemDelegate_t {
    QByteArrayData data[7];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNAbstractItemDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNAbstractItemDelegate_t qt_meta_stringdata_TNAbstractItemDelegate = {
    {
QT_MOC_LITERAL(0, 0, 22), // "TNAbstractItemDelegate"
QT_MOC_LITERAL(1, 23, 11), // "itemClicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "index"
QT_MOC_LITERAL(4, 42, 17), // "itemDoubleClicked"
QT_MOC_LITERAL(5, 60, 13), // "onItemClicked"
QT_MOC_LITERAL(6, 74, 19) // "onItemDoubleClicked"

    },
    "TNAbstractItemDelegate\0itemClicked\0\0"
    "index\0itemDoubleClicked\0onItemClicked\0"
    "onItemDoubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNAbstractItemDelegate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   40,    2, 0x09 /* Protected */,
       6,    1,   43,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::QModelIndex,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::QModelIndex,    3,

       0        // eod
};

void TNAbstractItemDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNAbstractItemDelegate *_t = static_cast<TNAbstractItemDelegate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->itemClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->itemDoubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->onItemClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: _t->onItemDoubleClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNAbstractItemDelegate::*_t)(QModelIndex );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNAbstractItemDelegate::itemClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNAbstractItemDelegate::*_t)(QModelIndex );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNAbstractItemDelegate::itemDoubleClicked)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject TNAbstractItemDelegate::staticMetaObject = {
    { &QStyledItemDelegate::staticMetaObject, qt_meta_stringdata_TNAbstractItemDelegate.data,
      qt_meta_data_TNAbstractItemDelegate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNAbstractItemDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNAbstractItemDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNAbstractItemDelegate.stringdata0))
        return static_cast<void*>(const_cast< TNAbstractItemDelegate*>(this));
    return QStyledItemDelegate::qt_metacast(_clname);
}

int TNAbstractItemDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void TNAbstractItemDelegate::itemClicked(QModelIndex _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TNAbstractItemDelegate::itemDoubleClicked(QModelIndex _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
