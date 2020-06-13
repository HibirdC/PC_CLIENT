/****************************************************************************
** Meta object code from reading C++ file 'HomePageListArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HomePageListArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HomePageListArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HomePageListArea_t {
    QByteArrayData data[9];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HomePageListArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HomePageListArea_t qt_meta_stringdata_HomePageListArea = {
    {
QT_MOC_LITERAL(0, 0, 16), // "HomePageListArea"
QT_MOC_LITERAL(1, 17, 11), // "clickedItem"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "title"
QT_MOC_LITERAL(4, 36, 3), // "url"
QT_MOC_LITERAL(5, 40, 21), // "slotOnClickedTreeView"
QT_MOC_LITERAL(6, 62, 5), // "index"
QT_MOC_LITERAL(7, 68, 22), // "slotClickedArrowButton"
QT_MOC_LITERAL(8, 91, 8) // "expanded"

    },
    "HomePageListArea\0clickedItem\0\0title\0"
    "url\0slotOnClickedTreeView\0index\0"
    "slotClickedArrowButton\0expanded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HomePageListArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   34,    2, 0x0a /* Public */,
       7,    2,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    6,
    QMetaType::Void, QMetaType::QModelIndex, QMetaType::Bool,    6,    8,

       0        // eod
};

void HomePageListArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HomePageListArea *_t = static_cast<HomePageListArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clickedItem((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->slotOnClickedTreeView((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->slotClickedArrowButton((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HomePageListArea::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HomePageListArea::clickedItem)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject HomePageListArea::staticMetaObject = {
    { &ListAreaBase::staticMetaObject, qt_meta_stringdata_HomePageListArea.data,
      qt_meta_data_HomePageListArea,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HomePageListArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HomePageListArea::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HomePageListArea.stringdata0))
        return static_cast<void*>(const_cast< HomePageListArea*>(this));
    return ListAreaBase::qt_metacast(_clname);
}

int HomePageListArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ListAreaBase::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void HomePageListArea::clickedItem(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
