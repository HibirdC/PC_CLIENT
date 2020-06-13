/****************************************************************************
** Meta object code from reading C++ file 'TNIMMsgManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNIMMsgManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNIMMsgManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNIMMsgManager_t {
    QByteArrayData data[34];
    char stringdata0[445];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNIMMsgManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNIMMsgManager_t qt_meta_stringdata_TNIMMsgManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TNIMMsgManager"
QT_MOC_LITERAL(1, 15, 8), // "waitOver"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "allOver"
QT_MOC_LITERAL(4, 33, 18), // "ProcessMsgRecvSign"
QT_MOC_LITERAL(5, 52, 4), // "type"
QT_MOC_LITERAL(6, 57, 18), // "toonim::CTNMessage"
QT_MOC_LITERAL(7, 76, 3), // "req"
QT_MOC_LITERAL(8, 80, 17), // "ProcessMsgAckSign"
QT_MOC_LITERAL(9, 98, 5), // "msgId"
QT_MOC_LITERAL(10, 104, 8), // "uint64_t"
QT_MOC_LITERAL(11, 113, 5), // "seqId"
QT_MOC_LITERAL(12, 119, 6), // "status"
QT_MOC_LITERAL(13, 126, 11), // "SendMsgSign"
QT_MOC_LITERAL(14, 138, 9), // "TNMsgData"
QT_MOC_LITERAL(15, 148, 7), // "msgData"
QT_MOC_LITERAL(16, 156, 8), // "singChat"
QT_MOC_LITERAL(17, 165, 5), // "bSend"
QT_MOC_LITERAL(18, 171, 17), // "SendRevertMsgSign"
QT_MOC_LITERAL(19, 189, 12), // "TNRevokeData"
QT_MOC_LITERAL(20, 202, 18), // "SendForwardMsgSign"
QT_MOC_LITERAL(21, 221, 21), // "QMap<QString,QString>"
QT_MOC_LITERAL(22, 243, 8), // "feedList"
QT_MOC_LITERAL(23, 252, 19), // "SendReadSessionSign"
QT_MOC_LITERAL(24, 272, 13), // "readSessionID"
QT_MOC_LITERAL(25, 286, 14), // "bRemoveSession"
QT_MOC_LITERAL(26, 301, 19), // "SendOfflineReadSign"
QT_MOC_LITERAL(27, 321, 17), // "sendAllOverSignal"
QT_MOC_LITERAL(28, 339, 18), // "ProcessMsgRevcSlot"
QT_MOC_LITERAL(29, 358, 17), // "ProcessMsgAckSlot"
QT_MOC_LITERAL(30, 376, 11), // "SendMsgSlot"
QT_MOC_LITERAL(31, 388, 17), // "SendRevertMsgSlot"
QT_MOC_LITERAL(32, 406, 18), // "SendForwardMsgSlot"
QT_MOC_LITERAL(33, 425, 19) // "SendReadSessionSlot"

    },
    "TNIMMsgManager\0waitOver\0\0allOver\0"
    "ProcessMsgRecvSign\0type\0toonim::CTNMessage\0"
    "req\0ProcessMsgAckSign\0msgId\0uint64_t\0"
    "seqId\0status\0SendMsgSign\0TNMsgData\0"
    "msgData\0singChat\0bSend\0SendRevertMsgSign\0"
    "TNRevokeData\0SendForwardMsgSign\0"
    "QMap<QString,QString>\0feedList\0"
    "SendReadSessionSign\0readSessionID\0"
    "bRemoveSession\0SendOfflineReadSign\0"
    "sendAllOverSignal\0ProcessMsgRevcSlot\0"
    "ProcessMsgAckSlot\0SendMsgSlot\0"
    "SendRevertMsgSlot\0SendForwardMsgSlot\0"
    "SendReadSessionSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNIMMsgManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    2,   96,    2, 0x06 /* Public */,
       8,    3,  101,    2, 0x06 /* Public */,
      13,    3,  108,    2, 0x06 /* Public */,
      18,    2,  115,    2, 0x06 /* Public */,
      20,    2,  120,    2, 0x06 /* Public */,
      23,    2,  125,    2, 0x06 /* Public */,
      26,    0,  130,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      27,    0,  131,    2, 0x08 /* Private */,
      28,    2,  132,    2, 0x0a /* Public */,
      29,    3,  137,    2, 0x0a /* Public */,
      30,    3,  144,    2, 0x0a /* Public */,
      31,    2,  151,    2, 0x0a /* Public */,
      32,    2,  156,    2, 0x0a /* Public */,
      33,    2,  161,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    5,    7,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 10, QMetaType::Int,    9,   11,   12,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Bool, QMetaType::Bool,   15,   16,   17,
    QMetaType::Void, 0x80000000 | 19, QMetaType::Bool,   15,   16,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 21,   15,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   24,   25,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    5,    7,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 10, QMetaType::Int,    9,   11,   12,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Bool, QMetaType::Bool,   15,   16,   17,
    QMetaType::Void, 0x80000000 | 19, QMetaType::Bool,   15,   16,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 21,   15,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   24,   25,

       0        // eod
};

void TNIMMsgManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNIMMsgManager *_t = static_cast<TNIMMsgManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->waitOver(); break;
        case 1: _t->allOver(); break;
        case 2: _t->ProcessMsgRecvSign((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< toonim::CTNMessage(*)>(_a[2]))); break;
        case 3: _t->ProcessMsgAckSign((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint64_t(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->SendMsgSign((*reinterpret_cast< TNMsgData(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 5: _t->SendRevertMsgSign((*reinterpret_cast< TNRevokeData(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->SendForwardMsgSign((*reinterpret_cast< TNMsgData(*)>(_a[1])),(*reinterpret_cast< QMap<QString,QString>(*)>(_a[2]))); break;
        case 7: _t->SendReadSessionSign((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->SendOfflineReadSign(); break;
        case 9: _t->sendAllOverSignal(); break;
        case 10: _t->ProcessMsgRevcSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< toonim::CTNMessage(*)>(_a[2]))); break;
        case 11: _t->ProcessMsgAckSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< uint64_t(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: _t->SendMsgSlot((*reinterpret_cast< TNMsgData(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 13: _t->SendRevertMsgSlot((*reinterpret_cast< TNRevokeData(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 14: _t->SendForwardMsgSlot((*reinterpret_cast< TNMsgData(*)>(_a[1])),(*reinterpret_cast< QMap<QString,QString>(*)>(_a[2]))); break;
        case 15: _t->SendReadSessionSlot((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNIMMsgManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNIMMsgManager::waitOver)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNIMMsgManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNIMMsgManager::allOver)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNIMMsgManager::*_t)(int , toonim::CTNMessage );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNIMMsgManager::ProcessMsgRecvSign)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TNIMMsgManager::*_t)(QString , uint64_t , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNIMMsgManager::ProcessMsgAckSign)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (TNIMMsgManager::*_t)(TNMsgData , bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNIMMsgManager::SendMsgSign)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (TNIMMsgManager::*_t)(TNRevokeData , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNIMMsgManager::SendRevertMsgSign)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (TNIMMsgManager::*_t)(TNMsgData , QMap<QString,QString> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNIMMsgManager::SendForwardMsgSign)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (TNIMMsgManager::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNIMMsgManager::SendReadSessionSign)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (TNIMMsgManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNIMMsgManager::SendOfflineReadSign)) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject TNIMMsgManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TNIMMsgManager.data,
      qt_meta_data_TNIMMsgManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNIMMsgManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNIMMsgManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNIMMsgManager.stringdata0))
        return static_cast<void*>(const_cast< TNIMMsgManager*>(this));
    return QObject::qt_metacast(_clname);
}

int TNIMMsgManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void TNIMMsgManager::waitOver()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TNIMMsgManager::allOver()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void TNIMMsgManager::ProcessMsgRecvSign(int _t1, toonim::CTNMessage _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TNIMMsgManager::ProcessMsgAckSign(QString _t1, uint64_t _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TNIMMsgManager::SendMsgSign(TNMsgData _t1, bool _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TNIMMsgManager::SendRevertMsgSign(TNRevokeData _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TNIMMsgManager::SendForwardMsgSign(TNMsgData _t1, QMap<QString,QString> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void TNIMMsgManager::SendReadSessionSign(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void TNIMMsgManager::SendOfflineReadSign()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
