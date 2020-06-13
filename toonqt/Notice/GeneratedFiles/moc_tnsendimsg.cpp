/****************************************************************************
** Meta object code from reading C++ file 'tnsendimsg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../network/tnsendimsg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tnsendimsg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNSendIMsg_t {
    QByteArrayData data[34];
    char stringdata0[398];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNSendIMsg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNSendIMsg_t qt_meta_stringdata_TNSendIMsg = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TNSendIMsg"
QT_MOC_LITERAL(1, 11, 16), // "upLoadFinishSign"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 18), // "downloadFinishSign"
QT_MOC_LITERAL(4, 48, 4), // "type"
QT_MOC_LITERAL(5, 53, 6), // "is_org"
QT_MOC_LITERAL(6, 60, 13), // "notifyRefresh"
QT_MOC_LITERAL(7, 74, 8), // "statCode"
QT_MOC_LITERAL(8, 83, 8), // "statDesc"
QT_MOC_LITERAL(9, 92, 9), // "TNMsgData"
QT_MOC_LITERAL(10, 102, 7), // "msgData"
QT_MOC_LITERAL(11, 110, 13), // "TNNoticeInfo&"
QT_MOC_LITERAL(12, 124, 10), // "noticeInfo"
QT_MOC_LITERAL(13, 135, 18), // "org_image_progress"
QT_MOC_LITERAL(14, 154, 5), // "msgId"
QT_MOC_LITERAL(15, 160, 8), // "progress"
QT_MOC_LITERAL(16, 169, 19), // "orig_image_finished"
QT_MOC_LITERAL(17, 189, 9), // "file_path"
QT_MOC_LITERAL(18, 199, 16), // "on_notifyRefresh"
QT_MOC_LITERAL(19, 216, 19), // "on_notifyRefreshAck"
QT_MOC_LITERAL(20, 236, 4), // "bSuc"
QT_MOC_LITERAL(21, 241, 19), // "QList<UINotifyData>"
QT_MOC_LITERAL(22, 261, 14), // "onUpLoadFinish"
QT_MOC_LITERAL(23, 276, 7), // "success"
QT_MOC_LITERAL(24, 284, 3), // "url"
QT_MOC_LITERAL(25, 288, 9), // "sessionId"
QT_MOC_LITERAL(26, 298, 16), // "onDownLoadFinish"
QT_MOC_LITERAL(27, 315, 16), // "onUpLoadProgress"
QT_MOC_LITERAL(28, 332, 3), // "per"
QT_MOC_LITERAL(29, 336, 5), // "total"
QT_MOC_LITERAL(30, 342, 18), // "onDownLoadProgress"
QT_MOC_LITERAL(31, 361, 4), // "info"
QT_MOC_LITERAL(32, 366, 24), // "onAvatarDownLoadFinishEx"
QT_MOC_LITERAL(33, 391, 6) // "feedId"

    },
    "TNSendIMsg\0upLoadFinishSign\0\0"
    "downloadFinishSign\0type\0is_org\0"
    "notifyRefresh\0statCode\0statDesc\0"
    "TNMsgData\0msgData\0TNNoticeInfo&\0"
    "noticeInfo\0org_image_progress\0msgId\0"
    "progress\0orig_image_finished\0file_path\0"
    "on_notifyRefresh\0on_notifyRefreshAck\0"
    "bSuc\0QList<UINotifyData>\0onUpLoadFinish\0"
    "success\0url\0sessionId\0onDownLoadFinish\0"
    "onUpLoadProgress\0per\0total\0"
    "onDownLoadProgress\0info\0"
    "onAvatarDownLoadFinishEx\0feedId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNSendIMsg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   94,    2, 0x06 /* Public */,
       3,    6,  103,    2, 0x06 /* Public */,
       3,    5,  116,    2, 0x26 /* Public | MethodCloned */,
       6,    4,  127,    2, 0x06 /* Public */,
       6,    2,  136,    2, 0x06 /* Public */,
      13,    2,  141,    2, 0x06 /* Public */,
      16,    3,  146,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    4,  153,    2, 0x0a /* Public */,
      18,    2,  162,    2, 0x0a /* Public */,
      19,    2,  167,    2, 0x0a /* Public */,
      18,    2,  172,    2, 0x0a /* Public */,
      22,    4,  177,    2, 0x08 /* Private */,
      26,    6,  186,    2, 0x08 /* Private */,
      27,    3,  199,    2, 0x08 /* Private */,
      30,    3,  206,    2, 0x08 /* Private */,
      32,    4,  213,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Bool,    2,    2,    2,    2,    4,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,    2,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString, 0x80000000 | 9,    4,    7,    8,   10,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 11,    4,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   14,   15,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,    2,   14,   17,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString, 0x80000000 | 9,    4,    7,    8,   10,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 11,    4,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   14,   20,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 21,    2,    2,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString,   23,   24,   14,   25,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Bool,   23,   24,   14,   25,    4,    5,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::QString,   28,   29,   14,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::QStringList,   28,   29,   31,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString,   23,   17,   33,   14,

       0        // eod
};

void TNSendIMsg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNSendIMsg *_t = static_cast<TNSendIMsg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->upLoadFinishSign((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: _t->downloadFinishSign((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 2: _t->downloadFinishSign((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 3: _t->notifyRefresh((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< TNMsgData(*)>(_a[4]))); break;
        case 4: _t->notifyRefresh((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< TNNoticeInfo(*)>(_a[2]))); break;
        case 5: _t->org_image_progress((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->orig_image_finished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: _t->on_notifyRefresh((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< TNMsgData(*)>(_a[4]))); break;
        case 8: _t->on_notifyRefresh((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< TNNoticeInfo(*)>(_a[2]))); break;
        case 9: _t->on_notifyRefreshAck((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->on_notifyRefresh((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QList<UINotifyData>(*)>(_a[2]))); break;
        case 11: _t->onUpLoadFinish((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 12: _t->onDownLoadFinish((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 13: _t->onUpLoadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 14: _t->onDownLoadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3]))); break;
        case 15: _t->onAvatarDownLoadFinishEx((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNSendIMsg::*_t)(bool , QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNSendIMsg::upLoadFinishSign)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNSendIMsg::*_t)(bool , QString , QString , QString , int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNSendIMsg::downloadFinishSign)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNSendIMsg::*_t)(QString , int , const QString , TNMsgData );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNSendIMsg::notifyRefresh)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (TNSendIMsg::*_t)(QString , TNNoticeInfo & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNSendIMsg::notifyRefresh)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (TNSendIMsg::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNSendIMsg::org_image_progress)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (TNSendIMsg::*_t)(bool , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNSendIMsg::orig_image_finished)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject TNSendIMsg::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TNSendIMsg.data,
      qt_meta_data_TNSendIMsg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNSendIMsg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNSendIMsg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNSendIMsg.stringdata0))
        return static_cast<void*>(const_cast< TNSendIMsg*>(this));
    return QObject::qt_metacast(_clname);
}

int TNSendIMsg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TNSendIMsg::upLoadFinishSign(bool _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TNSendIMsg::downloadFinishSign(bool _t1, QString _t2, QString _t3, QString _t4, int _t5, bool _t6)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 3
void TNSendIMsg::notifyRefresh(QString _t1, int _t2, const QString _t3, TNMsgData _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TNSendIMsg::notifyRefresh(QString _t1, TNNoticeInfo & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TNSendIMsg::org_image_progress(QString _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TNSendIMsg::orig_image_finished(bool _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
