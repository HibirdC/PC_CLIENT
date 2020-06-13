/****************************************************************************
** Meta object code from reading C++ file 'TNAvatarChoice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNAvatarChoice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNAvatarChoice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNAvatarChoice_t {
    QByteArrayData data[14];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNAvatarChoice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNAvatarChoice_t qt_meta_stringdata_TNAvatarChoice = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TNAvatarChoice"
QT_MOC_LITERAL(1, 15, 11), // "ItemClicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "type"
QT_MOC_LITERAL(4, 33, 4), // "feed"
QT_MOC_LITERAL(5, 38, 5), // "resID"
QT_MOC_LITERAL(6, 44, 10), // "avatarLink"
QT_MOC_LITERAL(7, 55, 17), // "OnListClickedSlot"
QT_MOC_LITERAL(8, 73, 5), // "index"
QT_MOC_LITERAL(9, 79, 20), // "onItemCreateFinished"
QT_MOC_LITERAL(10, 100, 22), // "onAvatarDownLoadFinish"
QT_MOC_LITERAL(11, 123, 7), // "success"
QT_MOC_LITERAL(12, 131, 3), // "url"
QT_MOC_LITERAL(13, 135, 6) // "feedId"

    },
    "TNAvatarChoice\0ItemClicked\0\0type\0feed\0"
    "resID\0avatarLink\0OnListClickedSlot\0"
    "index\0onItemCreateFinished\0"
    "onAvatarDownLoadFinish\0success\0url\0"
    "feedId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNAvatarChoice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   43,    2, 0x0a /* Public */,
       9,    1,   46,    2, 0x0a /* Public */,
      10,    3,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    8,
    QMetaType::Void, QMetaType::QModelIndex,    8,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,   11,   12,   13,

       0        // eod
};

void TNAvatarChoice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNAvatarChoice *_t = static_cast<TNAvatarChoice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ItemClicked((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 1: _t->OnListClickedSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->onItemCreateFinished((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->onAvatarDownLoadFinish((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNAvatarChoice::*_t)(const QString & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNAvatarChoice::ItemClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TNAvatarChoice::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TNAvatarChoice.data,
      qt_meta_data_TNAvatarChoice,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNAvatarChoice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNAvatarChoice::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNAvatarChoice.stringdata0))
        return static_cast<void*>(const_cast< TNAvatarChoice*>(this));
    return QWidget::qt_metacast(_clname);
}

int TNAvatarChoice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void TNAvatarChoice::ItemClicked(const QString & _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
