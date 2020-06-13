/****************************************************************************
** Meta object code from reading C++ file 'TNUpgradeMangement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNUpgradeMangement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNUpgradeMangement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNUpgradeMangement_t {
    QByteArrayData data[8];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNUpgradeMangement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNUpgradeMangement_t qt_meta_stringdata_TNUpgradeMangement = {
    {
QT_MOC_LITERAL(0, 0, 18), // "TNUpgradeMangement"
QT_MOC_LITERAL(1, 19, 20), // "checkVersionFinished"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 13), // "isNeedupgrade"
QT_MOC_LITERAL(4, 55, 14), // "isForceUpgrade"
QT_MOC_LITERAL(5, 70, 14), // "strDownLoadURL"
QT_MOC_LITERAL(6, 85, 10), // "nCheckType"
QT_MOC_LITERAL(7, 96, 9) // "strVerDes"

    },
    "TNUpgradeMangement\0checkVersionFinished\0"
    "\0isNeedupgrade\0isForceUpgrade\0"
    "strDownLoadURL\0nCheckType\0strVerDes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNUpgradeMangement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::QString, QMetaType::Int, QMetaType::QString,    3,    4,    5,    6,    7,

       0        // eod
};

void TNUpgradeMangement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNUpgradeMangement *_t = static_cast<TNUpgradeMangement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->checkVersionFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNUpgradeMangement::*_t)(bool , bool , QString , int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNUpgradeMangement::checkVersionFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TNUpgradeMangement::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TNUpgradeMangement.data,
      qt_meta_data_TNUpgradeMangement,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNUpgradeMangement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNUpgradeMangement::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNUpgradeMangement.stringdata0))
        return static_cast<void*>(const_cast< TNUpgradeMangement*>(this));
    return QObject::qt_metacast(_clname);
}

int TNUpgradeMangement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void TNUpgradeMangement::checkVersionFinished(bool _t1, bool _t2, QString _t3, int _t4, QString _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
