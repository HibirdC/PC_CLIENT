/****************************************************************************
** Meta object code from reading C++ file 'login.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../login.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Login_t {
    QByteArrayData data[12];
    char stringdata0[185];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Login_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Login_t qt_meta_stringdata_Login = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Login"
QT_MOC_LITERAL(1, 6, 21), // "SendPluginParamSignal"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "TNPluginParamPtr"
QT_MOC_LITERAL(4, 46, 5), // "param"
QT_MOC_LITERAL(5, 52, 21), // "autoLoginFromErrByPwd"
QT_MOC_LITERAL(6, 74, 22), // "autoLoginFromErrByCode"
QT_MOC_LITERAL(7, 97, 16), // "autoLoginFromErr"
QT_MOC_LITERAL(8, 114, 18), // "destroyLoginWidget"
QT_MOC_LITERAL(9, 133, 12), // "showLoginMin"
QT_MOC_LITERAL(10, 146, 17), // "OnPluginParamSlot"
QT_MOC_LITERAL(11, 164, 20) // "autoLoginFromErrSlot"

    },
    "Login\0SendPluginParamSignal\0\0"
    "TNPluginParamPtr\0param\0autoLoginFromErrByPwd\0"
    "autoLoginFromErrByCode\0autoLoginFromErr\0"
    "destroyLoginWidget\0showLoginMin\0"
    "OnPluginParamSlot\0autoLoginFromErrSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Login[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    0,   58,    2, 0x06 /* Public */,
       7,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,
      10,    1,   62,    2, 0x08 /* Private */,
      11,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void Login::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Login *_t = static_cast<Login *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendPluginParamSignal((*reinterpret_cast< TNPluginParamPtr(*)>(_a[1]))); break;
        case 1: _t->autoLoginFromErrByPwd(); break;
        case 2: _t->autoLoginFromErrByCode(); break;
        case 3: _t->autoLoginFromErr(); break;
        case 4: _t->destroyLoginWidget(); break;
        case 5: _t->showLoginMin(); break;
        case 6: _t->OnPluginParamSlot((*reinterpret_cast< TNPluginParamPtr(*)>(_a[1]))); break;
        case 7: _t->autoLoginFromErrSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Login::*_t)(TNPluginParamPtr );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Login::SendPluginParamSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Login::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Login::autoLoginFromErrByPwd)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Login::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Login::autoLoginFromErrByCode)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Login::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Login::autoLoginFromErr)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject Login::staticMetaObject = {
    { &DropShadowWidget::staticMetaObject, qt_meta_stringdata_Login.data,
      qt_meta_data_Login,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Login::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Login::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Login.stringdata0))
        return static_cast<void*>(const_cast< Login*>(this));
    return DropShadowWidget::qt_metacast(_clname);
}

int Login::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DropShadowWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Login::SendPluginParamSignal(TNPluginParamPtr _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Login::autoLoginFromErrByPwd()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Login::autoLoginFromErrByCode()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Login::autoLoginFromErr()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
