/****************************************************************************
** Meta object code from reading C++ file 'StateMachine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../StateMachine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StateMachine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StateMachine_t {
    QByteArrayData data[22];
    char stringdata0[347];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StateMachine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StateMachine_t qt_meta_stringdata_StateMachine = {
    {
QT_MOC_LITERAL(0, 0, 12), // "StateMachine"
QT_MOC_LITERAL(1, 13, 15), // "connectRestored"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "OnLoginSuccessSlot"
QT_MOC_LITERAL(4, 49, 16), // "TNPluginParamPtr"
QT_MOC_LITERAL(5, 66, 11), // "pluginParam"
QT_MOC_LITERAL(6, 78, 14), // "OnLoginOutSlot"
QT_MOC_LITERAL(7, 93, 18), // "on_notifyNetStatus"
QT_MOC_LITERAL(8, 112, 22), // "onCheckVersionFinished"
QT_MOC_LITERAL(9, 135, 13), // "isNeedUpgrade"
QT_MOC_LITERAL(10, 149, 14), // "isForceUpgrade"
QT_MOC_LITERAL(11, 164, 11), // "downLoadURL"
QT_MOC_LITERAL(12, 176, 10), // "nCheckType"
QT_MOC_LITERAL(13, 187, 11), // "versionDesc"
QT_MOC_LITERAL(14, 199, 29), // "on_notifyCheckVersionFinished"
QT_MOC_LITERAL(15, 229, 20), // "SyncedWithCatcheSlot"
QT_MOC_LITERAL(16, 250, 17), // "SyncedTimeOutSlot"
QT_MOC_LITERAL(17, 268, 16), // "dbOwnerErrorSlot"
QT_MOC_LITERAL(18, 285, 6), // "dbType"
QT_MOC_LITERAL(19, 292, 27), // "slotApplicationStateChanged"
QT_MOC_LITERAL(20, 320, 20), // "Qt::ApplicationState"
QT_MOC_LITERAL(21, 341, 5) // "state"

    },
    "StateMachine\0connectRestored\0\0"
    "OnLoginSuccessSlot\0TNPluginParamPtr\0"
    "pluginParam\0OnLoginOutSlot\0"
    "on_notifyNetStatus\0onCheckVersionFinished\0"
    "isNeedUpgrade\0isForceUpgrade\0downLoadURL\0"
    "nCheckType\0versionDesc\0"
    "on_notifyCheckVersionFinished\0"
    "SyncedWithCatcheSlot\0SyncedTimeOutSlot\0"
    "dbOwnerErrorSlot\0dbType\0"
    "slotApplicationStateChanged\0"
    "Qt::ApplicationState\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StateMachine[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   65,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    1,   69,    2, 0x08 /* Private */,
       8,    5,   72,    2, 0x08 /* Private */,
      14,    5,   83,    2, 0x08 /* Private */,
      15,    0,   94,    2, 0x08 /* Private */,
      16,    0,   95,    2, 0x08 /* Private */,
      17,    1,   96,    2, 0x08 /* Private */,
      19,    1,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::QString, QMetaType::Int, QMetaType::QString,    9,   10,   11,   12,   13,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::QString, QMetaType::Int, QMetaType::QString,    9,   10,   11,   12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, 0x80000000 | 20,   21,

       0        // eod
};

void StateMachine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StateMachine *_t = static_cast<StateMachine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectRestored(); break;
        case 1: _t->OnLoginSuccessSlot((*reinterpret_cast< TNPluginParamPtr(*)>(_a[1]))); break;
        case 2: _t->OnLoginOutSlot(); break;
        case 3: _t->on_notifyNetStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onCheckVersionFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 5: _t->on_notifyCheckVersionFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 6: _t->SyncedWithCatcheSlot(); break;
        case 7: _t->SyncedTimeOutSlot(); break;
        case 8: _t->dbOwnerErrorSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->slotApplicationStateChanged((*reinterpret_cast< Qt::ApplicationState(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TNPluginParamPtr >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StateMachine::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StateMachine::connectRestored)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject StateMachine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StateMachine.data,
      qt_meta_data_StateMachine,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StateMachine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StateMachine::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StateMachine.stringdata0))
        return static_cast<void*>(const_cast< StateMachine*>(this));
    return QObject::qt_metacast(_clname);
}

int StateMachine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void StateMachine::connectRestored()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
