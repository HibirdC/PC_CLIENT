/****************************************************************************
** Meta object code from reading C++ file 'httpconnection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../httpserver/httpconnection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpconnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HttpConnection_t {
    QByteArrayData data[7];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HttpConnection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HttpConnection_t qt_meta_stringdata_HttpConnection = {
    {
QT_MOC_LITERAL(0, 0, 14), // "HttpConnection"
QT_MOC_LITERAL(1, 15, 10), // "newRequest"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "HttpRequest*"
QT_MOC_LITERAL(4, 40, 13), // "HttpResponse*"
QT_MOC_LITERAL(5, 54, 12), // "parseRequest"
QT_MOC_LITERAL(6, 67, 12) // "responseDone"

    },
    "HttpConnection\0newRequest\0\0HttpRequest*\0"
    "HttpResponse*\0parseRequest\0responseDone"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HttpConnection[] = {

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
       5,    0,   34,    2, 0x08 /* Private */,
       6,    0,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HttpConnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HttpConnection *_t = static_cast<HttpConnection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newRequest((*reinterpret_cast< HttpRequest*(*)>(_a[1])),(*reinterpret_cast< HttpResponse*(*)>(_a[2]))); break;
        case 1: _t->parseRequest(); break;
        case 2: _t->responseDone(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HttpConnection::*_t)(HttpRequest * , HttpResponse * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HttpConnection::newRequest)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject HttpConnection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HttpConnection.data,
      qt_meta_data_HttpConnection,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HttpConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HttpConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HttpConnection.stringdata0))
        return static_cast<void*>(const_cast< HttpConnection*>(this));
    return QObject::qt_metacast(_clname);
}

int HttpConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void HttpConnection::newRequest(HttpRequest * _t1, HttpResponse * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
