/****************************************************************************
** Meta object code from reading C++ file 'TNQRCodeLogin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNQRCodeLogin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNQRCodeLogin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNQRCodeLogin_t {
    QByteArrayData data[9];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNQRCodeLogin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNQRCodeLogin_t qt_meta_stringdata_TNQRCodeLogin = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TNQRCodeLogin"
QT_MOC_LITERAL(1, 14, 17), // "DownQRCodeSuccess"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 4), // "path"
QT_MOC_LITERAL(4, 38, 17), // "GetScanCodeStatus"
QT_MOC_LITERAL(5, 56, 6), // "status"
QT_MOC_LITERAL(6, 63, 15), // "CancelScanLogin"
QT_MOC_LITERAL(7, 79, 20), // "CurrentQRcodeInvalid"
QT_MOC_LITERAL(8, 100, 16) // "onTimerGetStatus"

    },
    "TNQRCodeLogin\0DownQRCodeSuccess\0\0path\0"
    "GetScanCodeStatus\0status\0CancelScanLogin\0"
    "CurrentQRcodeInvalid\0onTimerGetStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNQRCodeLogin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       6,    0,   45,    2, 0x06 /* Public */,
       7,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void TNQRCodeLogin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNQRCodeLogin *_t = static_cast<TNQRCodeLogin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DownQRCodeSuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->GetScanCodeStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->CancelScanLogin(); break;
        case 3: _t->CurrentQRcodeInvalid(); break;
        case 4: _t->onTimerGetStatus(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNQRCodeLogin::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNQRCodeLogin::DownQRCodeSuccess)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNQRCodeLogin::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNQRCodeLogin::GetScanCodeStatus)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNQRCodeLogin::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNQRCodeLogin::CancelScanLogin)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TNQRCodeLogin::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNQRCodeLogin::CurrentQRcodeInvalid)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TNQRCodeLogin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TNQRCodeLogin.data,
      qt_meta_data_TNQRCodeLogin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNQRCodeLogin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNQRCodeLogin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNQRCodeLogin.stringdata0))
        return static_cast<void*>(const_cast< TNQRCodeLogin*>(this));
    return QObject::qt_metacast(_clname);
}

int TNQRCodeLogin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TNQRCodeLogin::DownQRCodeSuccess(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TNQRCodeLogin::GetScanCodeStatus(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TNQRCodeLogin::CancelScanLogin()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void TNQRCodeLogin::CurrentQRcodeInvalid()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
