/****************************************************************************
** Meta object code from reading C++ file 'downloadmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../downloadmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'downloadmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DownLoadManager_t {
    QByteArrayData data[15];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DownLoadManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DownLoadManager_t qt_meta_stringdata_DownLoadManager = {
    {
QT_MOC_LITERAL(0, 0, 15), // "DownLoadManager"
QT_MOC_LITERAL(1, 16, 21), // "signalDownloadProcess"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 19), // "signalReplyFinished"
QT_MOC_LITERAL(4, 59, 6), // "status"
QT_MOC_LITERAL(5, 66, 8), // "fileName"
QT_MOC_LITERAL(6, 75, 19), // "signalDownloadError"
QT_MOC_LITERAL(7, 95, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(8, 123, 4), // "code"
QT_MOC_LITERAL(9, 128, 18), // "onDownloadProgress"
QT_MOC_LITERAL(10, 147, 13), // "bytesReceived"
QT_MOC_LITERAL(11, 161, 10), // "bytesTotal"
QT_MOC_LITERAL(12, 172, 11), // "onReadyRead"
QT_MOC_LITERAL(13, 184, 10), // "onFinished"
QT_MOC_LITERAL(14, 195, 7) // "onError"

    },
    "DownLoadManager\0signalDownloadProcess\0"
    "\0signalReplyFinished\0status\0fileName\0"
    "signalDownloadError\0QNetworkReply::NetworkError\0"
    "code\0onDownloadProgress\0bytesReceived\0"
    "bytesTotal\0onReadyRead\0onFinished\0"
    "onError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DownLoadManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       3,    2,   54,    2, 0x06 /* Public */,
       6,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    2,   62,    2, 0x08 /* Private */,
      12,    0,   67,    2, 0x08 /* Private */,
      13,    0,   68,    2, 0x08 /* Private */,
      14,    1,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void DownLoadManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DownLoadManager *_t = static_cast<DownLoadManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalDownloadProcess((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->signalReplyFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->signalDownloadError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 3: _t->onDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->onReadyRead(); break;
        case 5: _t->onFinished(); break;
        case 6: _t->onError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DownLoadManager::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DownLoadManager::signalDownloadProcess)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DownLoadManager::*_t)(int , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DownLoadManager::signalReplyFinished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DownLoadManager::*_t)(QNetworkReply::NetworkError );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DownLoadManager::signalDownloadError)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject DownLoadManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DownLoadManager.data,
      qt_meta_data_DownLoadManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DownLoadManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DownLoadManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DownLoadManager.stringdata0))
        return static_cast<void*>(const_cast< DownLoadManager*>(this));
    return QObject::qt_metacast(_clname);
}

int DownLoadManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DownLoadManager::signalDownloadProcess(qint64 _t1, qint64 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DownLoadManager::signalReplyFinished(int _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DownLoadManager::signalDownloadError(QNetworkReply::NetworkError _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
