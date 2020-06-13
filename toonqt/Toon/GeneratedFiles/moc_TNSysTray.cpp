/****************************************************************************
** Meta object code from reading C++ file 'TNSysTray.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../unReadList/TNSysTray.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNSysTray.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNSysTray_t {
    QByteArrayData data[7];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNSysTray_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNSysTray_t qt_meta_stringdata_TNSysTray = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TNSysTray"
QT_MOC_LITERAL(1, 10, 10), // "showWidget"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "MessageSignal"
QT_MOC_LITERAL(4, 36, 13), // "quitAppSignal"
QT_MOC_LITERAL(5, 50, 9), // "showSetUp"
QT_MOC_LITERAL(6, 60, 10) // "showLogout"

    },
    "TNSysTray\0showWidget\0\0MessageSignal\0"
    "quitAppSignal\0showSetUp\0showLogout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNSysTray[] = {

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
       1,    0,   39,    2, 0x06 /* Public */,
       3,    1,   40,    2, 0x06 /* Public */,
       4,    0,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   44,    2, 0x08 /* Private */,
       6,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TNSysTray::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNSysTray *_t = static_cast<TNSysTray *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showWidget(); break;
        case 1: _t->MessageSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->quitAppSignal(); break;
        case 3: _t->showSetUp(); break;
        case 4: _t->showLogout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNSysTray::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNSysTray::showWidget)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNSysTray::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNSysTray::MessageSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNSysTray::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNSysTray::quitAppSignal)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject TNSysTray::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TNSysTray.data,
      qt_meta_data_TNSysTray,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNSysTray::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNSysTray::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNSysTray.stringdata0))
        return static_cast<void*>(const_cast< TNSysTray*>(this));
    return QObject::qt_metacast(_clname);
}

int TNSysTray::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void TNSysTray::showWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TNSysTray::MessageSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TNSysTray::quitAppSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
