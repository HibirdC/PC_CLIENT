/****************************************************************************
** Meta object code from reading C++ file 'TNHttpUploadCloud.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNHttpUploadCloud.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNHttpUploadCloud.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNHttpUploadCloud_t {
    QByteArrayData data[5];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNHttpUploadCloud_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNHttpUploadCloud_t qt_meta_stringdata_TNHttpUploadCloud = {
    {
QT_MOC_LITERAL(0, 0, 17), // "TNHttpUploadCloud"
QT_MOC_LITERAL(1, 18, 19), // "UpLoadProgressCloud"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "msgId"
QT_MOC_LITERAL(4, 45, 22) // "On_UploadProgressCloud"

    },
    "TNHttpUploadCloud\0UpLoadProgressCloud\0"
    "\0msgId\0On_UploadProgressCloud"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNHttpUploadCloud[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::QString,    2,    2,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,

       0        // eod
};

void TNHttpUploadCloud::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNHttpUploadCloud *_t = static_cast<TNHttpUploadCloud *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpLoadProgressCloud((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->On_UploadProgressCloud((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNHttpUploadCloud::*_t)(qint64 , qint64 , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNHttpUploadCloud::UpLoadProgressCloud)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TNHttpUploadCloud::staticMetaObject = {
    { &TNHttpBaseApi::staticMetaObject, qt_meta_stringdata_TNHttpUploadCloud.data,
      qt_meta_data_TNHttpUploadCloud,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNHttpUploadCloud::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNHttpUploadCloud::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNHttpUploadCloud.stringdata0))
        return static_cast<void*>(const_cast< TNHttpUploadCloud*>(this));
    return TNHttpBaseApi::qt_metacast(_clname);
}

int TNHttpUploadCloud::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TNHttpBaseApi::qt_metacall(_c, _id, _a);
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
void TNHttpUploadCloud::UpLoadProgressCloud(qint64 _t1, qint64 _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
