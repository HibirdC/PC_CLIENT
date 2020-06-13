/****************************************************************************
** Meta object code from reading C++ file 'tnnoticeatarea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AtSearch/tnnoticeatarea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tnnoticeatarea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_tnnoticeatarea_t {
    QByteArrayData data[13];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_tnnoticeatarea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_tnnoticeatarea_t qt_meta_stringdata_tnnoticeatarea = {
    {
QT_MOC_LITERAL(0, 0, 14), // "tnnoticeatarea"
QT_MOC_LITERAL(1, 15, 11), // "ItemClicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "text"
QT_MOC_LITERAL(4, 33, 6), // "feedId"
QT_MOC_LITERAL(5, 40, 8), // "nickName"
QT_MOC_LITERAL(6, 49, 21), // "OnListAreaClickedSlot"
QT_MOC_LITERAL(7, 71, 5), // "index"
QT_MOC_LITERAL(8, 77, 20), // "onItemCreateFinished"
QT_MOC_LITERAL(9, 98, 22), // "onAvatarDownLoadFinish"
QT_MOC_LITERAL(10, 121, 7), // "success"
QT_MOC_LITERAL(11, 129, 3), // "url"
QT_MOC_LITERAL(12, 133, 10) // "ShowDialog"

    },
    "tnnoticeatarea\0ItemClicked\0\0text\0"
    "feedId\0nickName\0OnListAreaClickedSlot\0"
    "index\0onItemCreateFinished\0"
    "onAvatarDownLoadFinish\0success\0url\0"
    "ShowDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_tnnoticeatarea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   46,    2, 0x0a /* Public */,
       8,    1,   49,    2, 0x0a /* Public */,
       9,    3,   52,    2, 0x0a /* Public */,
      12,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,   10,   11,    4,
    QMetaType::Void,

       0        // eod
};

void tnnoticeatarea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        tnnoticeatarea *_t = static_cast<tnnoticeatarea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ItemClicked((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->OnListAreaClickedSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->onItemCreateFinished((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->onAvatarDownLoadFinish((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 4: _t->ShowDialog(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (tnnoticeatarea::*_t)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&tnnoticeatarea::ItemClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject tnnoticeatarea::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_tnnoticeatarea.data,
      qt_meta_data_tnnoticeatarea,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *tnnoticeatarea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *tnnoticeatarea::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_tnnoticeatarea.stringdata0))
        return static_cast<void*>(const_cast< tnnoticeatarea*>(this));
    return QWidget::qt_metacast(_clname);
}

int tnnoticeatarea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void tnnoticeatarea::ItemClicked(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
