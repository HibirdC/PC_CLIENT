/****************************************************************************
** Meta object code from reading C++ file 'TNNoticeUpdater.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNNoticeUpdater.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNNoticeUpdater.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNNoticeUpdater_t {
    QByteArrayData data[28];
    char stringdata0[414];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNNoticeUpdater_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNNoticeUpdater_t qt_meta_stringdata_TNNoticeUpdater = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TNNoticeUpdater"
QT_MOC_LITERAL(1, 16, 15), // "UpdateRefreshUI"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 4), // "type"
QT_MOC_LITERAL(4, 38, 4), // "info"
QT_MOC_LITERAL(5, 43, 14), // "FinishedThread"
QT_MOC_LITERAL(6, 58, 17), // "AllUpdateFinished"
QT_MOC_LITERAL(7, 76, 21), // "companyUpdateFinished"
QT_MOC_LITERAL(8, 98, 13), // "StartUpdateDb"
QT_MOC_LITERAL(9, 112, 18), // "StartUpdateCompany"
QT_MOC_LITERAL(10, 131, 17), // "startUpdateReMark"
QT_MOC_LITERAL(11, 149, 17), // "OnFinishLoadSlots"
QT_MOC_LITERAL(12, 167, 19), // "QList<UINotifyData>"
QT_MOC_LITERAL(13, 187, 8), // "dataList"
QT_MOC_LITERAL(14, 196, 17), // "OnUpdateRefreshUI"
QT_MOC_LITERAL(15, 214, 17), // "StartUpdateThread"
QT_MOC_LITERAL(16, 232, 10), // "onTimerout"
QT_MOC_LITERAL(17, 243, 25), // "companyUpdateFinishedSlot"
QT_MOC_LITERAL(18, 269, 14), // "monitorHttpApi"
QT_MOC_LITERAL(19, 284, 14), // "TNHttpBaseApi*"
QT_MOC_LITERAL(20, 299, 7), // "httpApi"
QT_MOC_LITERAL(21, 307, 15), // "onHttpApiReturn"
QT_MOC_LITERAL(22, 323, 15), // "onNewFeedGetApi"
QT_MOC_LITERAL(23, 339, 21), // "TNHttpObtainFeedList*"
QT_MOC_LITERAL(24, 361, 22), // "StartUpdateCompanySlot"
QT_MOC_LITERAL(25, 384, 21), // "startUpdateReMarkSlot"
QT_MOC_LITERAL(26, 406, 4), // "from"
QT_MOC_LITERAL(27, 411, 2) // "to"

    },
    "TNNoticeUpdater\0UpdateRefreshUI\0\0type\0"
    "info\0FinishedThread\0AllUpdateFinished\0"
    "companyUpdateFinished\0StartUpdateDb\0"
    "StartUpdateCompany\0startUpdateReMark\0"
    "OnFinishLoadSlots\0QList<UINotifyData>\0"
    "dataList\0OnUpdateRefreshUI\0StartUpdateThread\0"
    "onTimerout\0companyUpdateFinishedSlot\0"
    "monitorHttpApi\0TNHttpBaseApi*\0httpApi\0"
    "onHttpApiReturn\0onNewFeedGetApi\0"
    "TNHttpObtainFeedList*\0StartUpdateCompanySlot\0"
    "startUpdateReMarkSlot\0from\0to"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNNoticeUpdater[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   99,    2, 0x06 /* Public */,
       5,    0,  104,    2, 0x06 /* Public */,
       6,    0,  105,    2, 0x06 /* Public */,
       7,    0,  106,    2, 0x06 /* Public */,
       8,    0,  107,    2, 0x06 /* Public */,
       9,    0,  108,    2, 0x06 /* Public */,
      10,    2,  109,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,  114,    2, 0x0a /* Public */,
      14,    2,  119,    2, 0x0a /* Public */,
      15,    0,  124,    2, 0x0a /* Public */,
      16,    0,  125,    2, 0x0a /* Public */,
      17,    0,  126,    2, 0x08 /* Private */,
      18,    1,  127,    2, 0x08 /* Private */,
      21,    1,  130,    2, 0x08 /* Private */,
      22,    1,  133,    2, 0x08 /* Private */,
      24,    0,  136,    2, 0x08 /* Private */,
      25,    2,  137,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12,    3,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, 0x80000000 | 23,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   26,   27,

       0        // eod
};

void TNNoticeUpdater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNNoticeUpdater *_t = static_cast<TNNoticeUpdater *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateRefreshUI((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->FinishedThread(); break;
        case 2: _t->AllUpdateFinished(); break;
        case 3: _t->companyUpdateFinished(); break;
        case 4: _t->StartUpdateDb(); break;
        case 5: _t->StartUpdateCompany(); break;
        case 6: _t->startUpdateReMark((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->OnFinishLoadSlots((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QList<UINotifyData>(*)>(_a[2]))); break;
        case 8: _t->OnUpdateRefreshUI((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 9: _t->StartUpdateThread(); break;
        case 10: _t->onTimerout(); break;
        case 11: _t->companyUpdateFinishedSlot(); break;
        case 12: _t->monitorHttpApi((*reinterpret_cast< TNHttpBaseApi*(*)>(_a[1]))); break;
        case 13: _t->onHttpApiReturn((*reinterpret_cast< TNHttpBaseApi*(*)>(_a[1]))); break;
        case 14: _t->onNewFeedGetApi((*reinterpret_cast< TNHttpObtainFeedList*(*)>(_a[1]))); break;
        case 15: _t->StartUpdateCompanySlot(); break;
        case 16: _t->startUpdateReMarkSlot((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TNHttpBaseApi* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TNHttpBaseApi* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNNoticeUpdater::*_t)(int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeUpdater::UpdateRefreshUI)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNNoticeUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeUpdater::FinishedThread)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNNoticeUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeUpdater::AllUpdateFinished)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TNNoticeUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeUpdater::companyUpdateFinished)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (TNNoticeUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeUpdater::StartUpdateDb)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (TNNoticeUpdater::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeUpdater::StartUpdateCompany)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (TNNoticeUpdater::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeUpdater::startUpdateReMark)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject TNNoticeUpdater::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TNNoticeUpdater.data,
      qt_meta_data_TNNoticeUpdater,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNNoticeUpdater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNNoticeUpdater::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNNoticeUpdater.stringdata0))
        return static_cast<void*>(const_cast< TNNoticeUpdater*>(this));
    return QObject::qt_metacast(_clname);
}

int TNNoticeUpdater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void TNNoticeUpdater::UpdateRefreshUI(int _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TNNoticeUpdater::FinishedThread()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void TNNoticeUpdater::AllUpdateFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void TNNoticeUpdater::companyUpdateFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void TNNoticeUpdater::StartUpdateDb()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void TNNoticeUpdater::StartUpdateCompany()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void TNNoticeUpdater::startUpdateReMark(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
