/****************************************************************************
** Meta object code from reading C++ file 'loadhistorydata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../history/loadhistorydata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loadhistorydata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LoadHistoryData_t {
    QByteArrayData data[10];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoadHistoryData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoadHistoryData_t qt_meta_stringdata_LoadHistoryData = {
    {
QT_MOC_LITERAL(0, 0, 15), // "LoadHistoryData"
QT_MOC_LITERAL(1, 16, 13), // "loadMsgFinsed"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "success"
QT_MOC_LITERAL(4, 39, 4), // "file"
QT_MOC_LITERAL(5, 44, 5), // "msgId"
QT_MOC_LITERAL(6, 50, 18), // "AppandPageFinished"
QT_MOC_LITERAL(7, 69, 10), // "isLastPage"
QT_MOC_LITERAL(8, 80, 3), // "num"
QT_MOC_LITERAL(9, 84, 6) // "isJump"

    },
    "LoadHistoryData\0loadMsgFinsed\0\0success\0"
    "file\0msgId\0AppandPageFinished\0isLastPage\0"
    "num\0isJump"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoadHistoryData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,
       6,    3,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Bool,    7,    8,    9,

       0        // eod
};

void LoadHistoryData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LoadHistoryData *_t = static_cast<LoadHistoryData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadMsgFinsed((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->AppandPageFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LoadHistoryData::*_t)(bool , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoadHistoryData::loadMsgFinsed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LoadHistoryData::*_t)(bool , int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoadHistoryData::AppandPageFinished)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject LoadHistoryData::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LoadHistoryData.data,
      qt_meta_data_LoadHistoryData,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LoadHistoryData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoadHistoryData::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LoadHistoryData.stringdata0))
        return static_cast<void*>(const_cast< LoadHistoryData*>(this));
    return QObject::qt_metacast(_clname);
}

int LoadHistoryData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void LoadHistoryData::loadMsgFinsed(bool _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LoadHistoryData::AppandPageFinished(bool _t1, int _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
