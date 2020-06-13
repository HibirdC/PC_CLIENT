/****************************************************************************
** Meta object code from reading C++ file 'ListArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ListArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ListArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ListArea_t {
    QByteArrayData data[10];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ListArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ListArea_t qt_meta_stringdata_ListArea = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ListArea"
QT_MOC_LITERAL(1, 9, 9), // "maxMinSet"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 6), // "status"
QT_MOC_LITERAL(4, 27, 14), // "turnPageSignal"
QT_MOC_LITERAL(5, 42, 23), // "sendCurrentSelectedPage"
QT_MOC_LITERAL(6, 66, 4), // "page"
QT_MOC_LITERAL(7, 71, 8), // "turnPage"
QT_MOC_LITERAL(8, 80, 12), // "current_page"
QT_MOC_LITERAL(9, 93, 15) // "doubleClickPage"

    },
    "ListArea\0maxMinSet\0\0status\0turnPageSignal\0"
    "sendCurrentSelectedPage\0page\0turnPage\0"
    "current_page\0doubleClickPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ListArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       5,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   48,    2, 0x0a /* Public */,
       9,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void ListArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ListArea *_t = static_cast<ListArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->maxMinSet((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->turnPageSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->sendCurrentSelectedPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->turnPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->doubleClickPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ListArea::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListArea::maxMinSet)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ListArea::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListArea::turnPageSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ListArea::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ListArea::sendCurrentSelectedPage)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject ListArea::staticMetaObject = {
    { &QStackedWidget::staticMetaObject, qt_meta_stringdata_ListArea.data,
      qt_meta_data_ListArea,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ListArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ListArea::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ListArea.stringdata0))
        return static_cast<void*>(const_cast< ListArea*>(this));
    return QStackedWidget::qt_metacast(_clname);
}

int ListArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStackedWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ListArea::maxMinSet(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ListArea::turnPageSignal(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ListArea::sendCurrentSelectedPage(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
