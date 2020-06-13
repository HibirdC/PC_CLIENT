/****************************************************************************
** Meta object code from reading C++ file 'TNSkinSet.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNSkinSet.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNSkinSet.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNSkinSet_t {
    QByteArrayData data[10];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNSkinSet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNSkinSet_t qt_meta_stringdata_TNSkinSet = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TNSkinSet"
QT_MOC_LITERAL(1, 10, 24), // "OnClickApplySkinBlueSlot"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 24), // "OnClickApplySkinPinkSlot"
QT_MOC_LITERAL(4, 61, 25), // "OnClickApplySkinGreenSlot"
QT_MOC_LITERAL(5, 87, 23), // "OnClickApplySkinTeaSlot"
QT_MOC_LITERAL(6, 111, 26), // "OnClickApplySkinOrangeSlot"
QT_MOC_LITERAL(7, 138, 26), // "OnClickApplySkinOrchidSlot"
QT_MOC_LITERAL(8, 165, 23), // "OnClickApplySkinBudSlot"
QT_MOC_LITERAL(9, 189, 26) // "OnClickApplySkinPurpleSlot"

    },
    "TNSkinSet\0OnClickApplySkinBlueSlot\0\0"
    "OnClickApplySkinPinkSlot\0"
    "OnClickApplySkinGreenSlot\0"
    "OnClickApplySkinTeaSlot\0"
    "OnClickApplySkinOrangeSlot\0"
    "OnClickApplySkinOrchidSlot\0"
    "OnClickApplySkinBudSlot\0"
    "OnClickApplySkinPurpleSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNSkinSet[] = {

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
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TNSkinSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNSkinSet *_t = static_cast<TNSkinSet *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnClickApplySkinBlueSlot(); break;
        case 1: _t->OnClickApplySkinPinkSlot(); break;
        case 2: _t->OnClickApplySkinGreenSlot(); break;
        case 3: _t->OnClickApplySkinTeaSlot(); break;
        case 4: _t->OnClickApplySkinOrangeSlot(); break;
        case 5: _t->OnClickApplySkinOrchidSlot(); break;
        case 6: _t->OnClickApplySkinBudSlot(); break;
        case 7: _t->OnClickApplySkinPurpleSlot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TNSkinSet::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TNSkinSet.data,
      qt_meta_data_TNSkinSet,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNSkinSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNSkinSet::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNSkinSet.stringdata0))
        return static_cast<void*>(const_cast< TNSkinSet*>(this));
    return QWidget::qt_metacast(_clname);
}

int TNSkinSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
