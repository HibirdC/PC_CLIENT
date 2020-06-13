/****************************************************************************
** Meta object code from reading C++ file 'TNHomePageTreeItemDelegate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNHomePageTreeItemDelegate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNHomePageTreeItemDelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNHomePageTreeItemDelegate_t {
    QByteArrayData data[6];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNHomePageTreeItemDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNHomePageTreeItemDelegate_t qt_meta_stringdata_TNHomePageTreeItemDelegate = {
    {
QT_MOC_LITERAL(0, 0, 26), // "TNHomePageTreeItemDelegate"
QT_MOC_LITERAL(1, 27, 18), // "clickedArrowButton"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 5), // "index"
QT_MOC_LITERAL(4, 53, 8), // "expanded"
QT_MOC_LITERAL(5, 62, 20) // "clickedItemOtherArea"

    },
    "TNHomePageTreeItemDelegate\0"
    "clickedArrowButton\0\0index\0expanded\0"
    "clickedItemOtherArea"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNHomePageTreeItemDelegate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,
       5,    1,   29,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::QModelIndex,    3,

       0        // eod
};

void TNHomePageTreeItemDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNHomePageTreeItemDelegate *_t = static_cast<TNHomePageTreeItemDelegate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clickedArrowButton((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->clickedItemOtherArea((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNHomePageTreeItemDelegate::*_t)(const QModelIndex & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNHomePageTreeItemDelegate::clickedArrowButton)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNHomePageTreeItemDelegate::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNHomePageTreeItemDelegate::clickedItemOtherArea)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject TNHomePageTreeItemDelegate::staticMetaObject = {
    { &QStyledItemDelegate::staticMetaObject, qt_meta_stringdata_TNHomePageTreeItemDelegate.data,
      qt_meta_data_TNHomePageTreeItemDelegate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNHomePageTreeItemDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNHomePageTreeItemDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNHomePageTreeItemDelegate.stringdata0))
        return static_cast<void*>(const_cast< TNHomePageTreeItemDelegate*>(this));
    return QStyledItemDelegate::qt_metacast(_clname);
}

int TNHomePageTreeItemDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TNHomePageTreeItemDelegate::clickedArrowButton(const QModelIndex & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TNHomePageTreeItemDelegate::clickedItemOtherArea(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
