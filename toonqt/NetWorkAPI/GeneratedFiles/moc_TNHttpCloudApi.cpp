/****************************************************************************
** Meta object code from reading C++ file 'TNHttpCloudApi.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNHttpCloudApi.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNHttpCloudApi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNHttpCloudApi_t {
    QByteArrayData data[9];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNHttpCloudApi_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNHttpCloudApi_t qt_meta_stringdata_TNHttpCloudApi = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TNHttpCloudApi"
QT_MOC_LITERAL(1, 15, 17), // "GetStokenFinished"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 21), // "DownLoadProgressCloud"
QT_MOC_LITERAL(4, 56, 5), // "msgId"
QT_MOC_LITERAL(5, 62, 19), // "UpLoadProgressCloud"
QT_MOC_LITERAL(6, 82, 24), // "On_DownLoadProgressCloud"
QT_MOC_LITERAL(7, 107, 22), // "On_UpLoadProgressCloud"
QT_MOC_LITERAL(8, 130, 15) // "onTokenTimerout"

    },
    "TNHttpCloudApi\0GetStokenFinished\0\0"
    "DownLoadProgressCloud\0msgId\0"
    "UpLoadProgressCloud\0On_DownLoadProgressCloud\0"
    "On_UpLoadProgressCloud\0onTokenTimerout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNHttpCloudApi[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    3,   45,    2, 0x06 /* Public */,
       5,    3,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,   59,    2, 0x0a /* Public */,
       7,    3,   66,    2, 0x0a /* Public */,
       8,    0,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::QStringList,    2,    2,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::QString,    2,    2,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::QString,    2,    2,    4,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::QString,    2,    2,    4,
    QMetaType::Void,

       0        // eod
};

void TNHttpCloudApi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNHttpCloudApi *_t = static_cast<TNHttpCloudApi *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GetStokenFinished(); break;
        case 1: _t->DownLoadProgressCloud((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        case 2: _t->UpLoadProgressCloud((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: _t->On_DownLoadProgressCloud((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: _t->On_UpLoadProgressCloud((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: _t->onTokenTimerout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNHttpCloudApi::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNHttpCloudApi::GetStokenFinished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNHttpCloudApi::*_t)(qint64 , qint64 , QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNHttpCloudApi::DownLoadProgressCloud)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNHttpCloudApi::*_t)(qint64 , qint64 , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNHttpCloudApi::UpLoadProgressCloud)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject TNHttpCloudApi::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TNHttpCloudApi.data,
      qt_meta_data_TNHttpCloudApi,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNHttpCloudApi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNHttpCloudApi::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNHttpCloudApi.stringdata0))
        return static_cast<void*>(const_cast< TNHttpCloudApi*>(this));
    return QObject::qt_metacast(_clname);
}

int TNHttpCloudApi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TNHttpCloudApi::GetStokenFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TNHttpCloudApi::DownLoadProgressCloud(qint64 _t1, qint64 _t2, QStringList _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TNHttpCloudApi::UpLoadProgressCloud(qint64 _t1, qint64 _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
