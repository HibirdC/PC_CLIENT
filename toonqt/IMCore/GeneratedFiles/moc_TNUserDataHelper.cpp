/****************************************************************************
** Meta object code from reading C++ file 'TNUserDataHelper.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNUserDataHelper.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNUserDataHelper.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNUserDataHelper_t {
    QByteArrayData data[10];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNUserDataHelper_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNUserDataHelper_t qt_meta_stringdata_TNUserDataHelper = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TNUserDataHelper"
QT_MOC_LITERAL(1, 17, 18), // "GetFeedFinishedOne"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 15), // "GetFeedFinished"
QT_MOC_LITERAL(4, 53, 4), // "type"
QT_MOC_LITERAL(5, 58, 19), // "QList<UINotifyData>"
QT_MOC_LITERAL(6, 78, 10), // "notifyData"
QT_MOC_LITERAL(7, 89, 14), // "GetAppFinished"
QT_MOC_LITERAL(8, 104, 16), // "addNewFeedGetApi"
QT_MOC_LITERAL(9, 121, 21) // "TNHttpObtainFeedList*"

    },
    "TNUserDataHelper\0GetFeedFinishedOne\0"
    "\0GetFeedFinished\0type\0QList<UINotifyData>\0"
    "notifyData\0GetAppFinished\0addNewFeedGetApi\0"
    "TNHttpObtainFeedList*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNUserDataHelper[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    2,   35,    2, 0x06 /* Public */,
       7,    0,   40,    2, 0x06 /* Public */,
       8,    1,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    4,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,

       0        // eod
};

void TNUserDataHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNUserDataHelper *_t = static_cast<TNUserDataHelper *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GetFeedFinishedOne(); break;
        case 1: _t->GetFeedFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QList<UINotifyData>(*)>(_a[2]))); break;
        case 2: _t->GetAppFinished(); break;
        case 3: _t->addNewFeedGetApi((*reinterpret_cast< TNHttpObtainFeedList*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TNHttpObtainFeedList* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNUserDataHelper::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNUserDataHelper::GetFeedFinishedOne)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNUserDataHelper::*_t)(int , QList<UINotifyData> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNUserDataHelper::GetFeedFinished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNUserDataHelper::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNUserDataHelper::GetAppFinished)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TNUserDataHelper::*_t)(TNHttpObtainFeedList * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNUserDataHelper::addNewFeedGetApi)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TNUserDataHelper::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TNUserDataHelper.data,
      qt_meta_data_TNUserDataHelper,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNUserDataHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNUserDataHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNUserDataHelper.stringdata0))
        return static_cast<void*>(const_cast< TNUserDataHelper*>(this));
    return QObject::qt_metacast(_clname);
}

int TNUserDataHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TNUserDataHelper::GetFeedFinishedOne()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TNUserDataHelper::GetFeedFinished(int _t1, QList<UINotifyData> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TNUserDataHelper::GetAppFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void TNUserDataHelper::addNewFeedGetApi(TNHttpObtainFeedList * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
