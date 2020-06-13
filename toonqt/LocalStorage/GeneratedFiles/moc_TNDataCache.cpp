/****************************************************************************
** Meta object code from reading C++ file 'TNDataCache.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNDataCache.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNDataCache.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNDataCache_t {
    QByteArrayData data[17];
    char stringdata0[192];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNDataCache_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNDataCache_t qt_meta_stringdata_TNDataCache = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TNDataCache"
QT_MOC_LITERAL(1, 12, 17), // "HasUpdateAllCache"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 11), // "ResetSignal"
QT_MOC_LITERAL(4, 43, 19), // "guysUpdateGroupChat"
QT_MOC_LITERAL(5, 63, 4), // "feed"
QT_MOC_LITERAL(6, 68, 14), // "guysUpdateCard"
QT_MOC_LITERAL(7, 83, 6), // "feedId"
QT_MOC_LITERAL(8, 90, 9), // "avatarUrl"
QT_MOC_LITERAL(9, 100, 5), // "title"
QT_MOC_LITERAL(10, 106, 8), // "subTitle"
QT_MOC_LITERAL(11, 115, 6), // "userId"
QT_MOC_LITERAL(12, 122, 7), // "titlePy"
QT_MOC_LITERAL(13, 130, 7), // "sources"
QT_MOC_LITERAL(14, 138, 18), // "updateAllCacheSlot"
QT_MOC_LITERAL(15, 157, 14), // "reSetCacheSlot"
QT_MOC_LITERAL(16, 172, 19) // "UpdateColleagueSlot"

    },
    "TNDataCache\0HasUpdateAllCache\0\0"
    "ResetSignal\0guysUpdateGroupChat\0feed\0"
    "guysUpdateCard\0feedId\0avatarUrl\0title\0"
    "subTitle\0userId\0titlePy\0sources\0"
    "updateAllCacheSlot\0reSetCacheSlot\0"
    "UpdateColleagueSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNDataCache[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    1,   51,    2, 0x06 /* Public */,
       6,    7,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   69,    2, 0x0a /* Public */,
      15,    0,   70,    2, 0x0a /* Public */,
      16,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    7,    8,    9,   10,   11,   12,   13,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TNDataCache::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNDataCache *_t = static_cast<TNDataCache *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->HasUpdateAllCache(); break;
        case 1: _t->ResetSignal(); break;
        case 2: _t->guysUpdateGroupChat((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->guysUpdateCard((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7]))); break;
        case 4: _t->updateAllCacheSlot(); break;
        case 5: _t->reSetCacheSlot(); break;
        case 6: _t->UpdateColleagueSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNDataCache::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNDataCache::HasUpdateAllCache)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNDataCache::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNDataCache::ResetSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNDataCache::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNDataCache::guysUpdateGroupChat)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TNDataCache::*_t)(const QString & , const QString & , const QString & , const QString & , const QString & , const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNDataCache::guysUpdateCard)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TNDataCache::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TNDataCache.data,
      qt_meta_data_TNDataCache,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNDataCache::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNDataCache::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNDataCache.stringdata0))
        return static_cast<void*>(const_cast< TNDataCache*>(this));
    return QObject::qt_metacast(_clname);
}

int TNDataCache::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TNDataCache::HasUpdateAllCache()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TNDataCache::ResetSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void TNDataCache::guysUpdateGroupChat(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TNDataCache::guysUpdateCard(const QString & _t1, const QString & _t2, const QString & _t3, const QString & _t4, const QString & _t5, const QString & _t6, int _t7)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
