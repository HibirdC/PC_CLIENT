/****************************************************************************
** Meta object code from reading C++ file 'TNHttpDownCloud.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNHttpDownCloud.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNHttpDownCloud.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNHttpDownCloud_t {
    QByteArrayData data[7];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNHttpDownCloud_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNHttpDownCloud_t qt_meta_stringdata_TNHttpDownCloud = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TNHttpDownCloud"
QT_MOC_LITERAL(1, 16, 21), // "DownLoadProgressCloud"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "msgId"
QT_MOC_LITERAL(4, 45, 17), // "downAvatarFinshed"
QT_MOC_LITERAL(5, 63, 19), // "downAvatarFinshedEx"
QT_MOC_LITERAL(6, 83, 24) // "On_DownLoadProgressCloud"

    },
    "TNHttpDownCloud\0DownLoadProgressCloud\0"
    "\0msgId\0downAvatarFinshed\0downAvatarFinshedEx\0"
    "On_DownLoadProgressCloud"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNHttpDownCloud[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,
       4,    3,   41,    2, 0x06 /* Public */,
       5,    4,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::QStringList,    2,    2,    3,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,

       0        // eod
};

void TNHttpDownCloud::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNHttpDownCloud *_t = static_cast<TNHttpDownCloud *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DownLoadProgressCloud((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        case 1: _t->downAvatarFinshed((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->downAvatarFinshedEx((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 3: _t->On_DownLoadProgressCloud((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNHttpDownCloud::*_t)(qint64 , qint64 , QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNHttpDownCloud::DownLoadProgressCloud)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNHttpDownCloud::*_t)(bool , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNHttpDownCloud::downAvatarFinshed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNHttpDownCloud::*_t)(bool , QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNHttpDownCloud::downAvatarFinshedEx)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject TNHttpDownCloud::staticMetaObject = {
    { &TNHttpBaseApi::staticMetaObject, qt_meta_stringdata_TNHttpDownCloud.data,
      qt_meta_data_TNHttpDownCloud,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNHttpDownCloud::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNHttpDownCloud::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNHttpDownCloud.stringdata0))
        return static_cast<void*>(const_cast< TNHttpDownCloud*>(this));
    return TNHttpBaseApi::qt_metacast(_clname);
}

int TNHttpDownCloud::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TNHttpBaseApi::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TNHttpDownCloud::DownLoadProgressCloud(qint64 _t1, qint64 _t2, QStringList _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TNHttpDownCloud::downAvatarFinshed(bool _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TNHttpDownCloud::downAvatarFinshedEx(bool _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
