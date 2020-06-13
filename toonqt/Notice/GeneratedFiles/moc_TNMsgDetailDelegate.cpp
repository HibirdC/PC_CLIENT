/****************************************************************************
** Meta object code from reading C++ file 'TNMsgDetailDelegate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../details_notice/TNMsgDetailDelegate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNMsgDetailDelegate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNMsgDetailDelegate_t {
    QByteArrayData data[14];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNMsgDetailDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNMsgDetailDelegate_t qt_meta_stringdata_TNMsgDetailDelegate = {
    {
QT_MOC_LITERAL(0, 0, 19), // "TNMsgDetailDelegate"
QT_MOC_LITERAL(1, 20, 19), // "revokeProcessSignal"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 10), // "resultType"
QT_MOC_LITERAL(4, 52, 7), // "msgType"
QT_MOC_LITERAL(5, 60, 7), // "msgTime"
QT_MOC_LITERAL(6, 68, 9), // "sessionId"
QT_MOC_LITERAL(7, 78, 5), // "msgId"
QT_MOC_LITERAL(8, 84, 8), // "pushInfo"
QT_MOC_LITERAL(9, 93, 23), // "deleteMsgSignalDelegate"
QT_MOC_LITERAL(10, 117, 21), // "jumpMsgSignalDelegate"
QT_MOC_LITERAL(11, 139, 12), // "onAutoHeight"
QT_MOC_LITERAL(12, 152, 6), // "height"
QT_MOC_LITERAL(13, 159, 5) // "index"

    },
    "TNMsgDetailDelegate\0revokeProcessSignal\0"
    "\0resultType\0msgType\0msgTime\0sessionId\0"
    "msgId\0pushInfo\0deleteMsgSignalDelegate\0"
    "jumpMsgSignalDelegate\0onAutoHeight\0"
    "height\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNMsgDetailDelegate[] = {

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
       1,    6,   34,    2, 0x06 /* Public */,
       9,    1,   47,    2, 0x06 /* Public */,
      10,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::LongLong, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QModelIndex,   12,   13,

       0        // eod
};

void TNMsgDetailDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNMsgDetailDelegate *_t = static_cast<TNMsgDetailDelegate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->revokeProcessSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6]))); break;
        case 1: _t->deleteMsgSignalDelegate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->jumpMsgSignalDelegate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onAutoHeight((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QModelIndex(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNMsgDetailDelegate::*_t)(int , int , qint64 , const QString & , const QString & , const QString & ) const;
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNMsgDetailDelegate::revokeProcessSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNMsgDetailDelegate::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNMsgDetailDelegate::deleteMsgSignalDelegate)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNMsgDetailDelegate::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNMsgDetailDelegate::jumpMsgSignalDelegate)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject TNMsgDetailDelegate::staticMetaObject = {
    { &TNAbstractItemDelegate::staticMetaObject, qt_meta_stringdata_TNMsgDetailDelegate.data,
      qt_meta_data_TNMsgDetailDelegate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNMsgDetailDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNMsgDetailDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNMsgDetailDelegate.stringdata0))
        return static_cast<void*>(const_cast< TNMsgDetailDelegate*>(this));
    return TNAbstractItemDelegate::qt_metacast(_clname);
}

int TNMsgDetailDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TNAbstractItemDelegate::qt_metacall(_c, _id, _a);
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
void TNMsgDetailDelegate::revokeProcessSignal(int _t1, int _t2, qint64 _t3, const QString & _t4, const QString & _t5, const QString & _t6)const
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(const_cast< TNMsgDetailDelegate *>(this), &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TNMsgDetailDelegate::deleteMsgSignalDelegate(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TNMsgDetailDelegate::jumpMsgSignalDelegate(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
