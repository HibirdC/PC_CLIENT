/****************************************************************************
** Meta object code from reading C++ file 'MineDetailsArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MineDetailsArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MineDetailsArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MineDetailsArea_t {
    QByteArrayData data[4];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MineDetailsArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MineDetailsArea_t qt_meta_stringdata_MineDetailsArea = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MineDetailsArea"
QT_MOC_LITERAL(1, 16, 21), // "OnListAreaClickedSlot"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5) // "index"

    },
    "MineDetailsArea\0OnListAreaClickedSlot\0"
    "\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MineDetailsArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,

       0        // eod
};

void MineDetailsArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MineDetailsArea *_t = static_cast<MineDetailsArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnListAreaClickedSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MineDetailsArea::staticMetaObject = {
    { &TNWebViewDetailsArea::staticMetaObject, qt_meta_stringdata_MineDetailsArea.data,
      qt_meta_data_MineDetailsArea,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MineDetailsArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MineDetailsArea::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MineDetailsArea.stringdata0))
        return static_cast<void*>(const_cast< MineDetailsArea*>(this));
    return TNWebViewDetailsArea::qt_metacast(_clname);
}

int MineDetailsArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TNWebViewDetailsArea::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
