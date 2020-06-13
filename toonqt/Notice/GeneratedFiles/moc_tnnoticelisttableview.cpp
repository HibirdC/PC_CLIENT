/****************************************************************************
** Meta object code from reading C++ file 'tnnoticelisttableview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../list_notice/tnnoticelisttableview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tnnoticelisttableview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNNoticeListTableView_t {
    QByteArrayData data[14];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNNoticeListTableView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNNoticeListTableView_t qt_meta_stringdata_TNNoticeListTableView = {
    {
QT_MOC_LITERAL(0, 0, 21), // "TNNoticeListTableView"
QT_MOC_LITERAL(1, 22, 7), // "seOnTop"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "seOnNoTop"
QT_MOC_LITERAL(4, 41, 17), // "seOnRemoveSession"
QT_MOC_LITERAL(5, 59, 19), // "seOnModifyGroupName"
QT_MOC_LITERAL(6, 79, 9), // "seOnAlarm"
QT_MOC_LITERAL(7, 89, 11), // "seOnNoAlarm"
QT_MOC_LITERAL(8, 101, 5), // "onTop"
QT_MOC_LITERAL(9, 107, 7), // "onNoTop"
QT_MOC_LITERAL(10, 115, 15), // "onRemoveSession"
QT_MOC_LITERAL(11, 131, 17), // "onModifyGroupName"
QT_MOC_LITERAL(12, 149, 7), // "onAlarm"
QT_MOC_LITERAL(13, 157, 9) // "onNoAlarm"

    },
    "TNNoticeListTableView\0seOnTop\0\0seOnNoTop\0"
    "seOnRemoveSession\0seOnModifyGroupName\0"
    "seOnAlarm\0seOnNoAlarm\0onTop\0onNoTop\0"
    "onRemoveSession\0onModifyGroupName\0"
    "onAlarm\0onNoAlarm"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNNoticeListTableView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       3,    1,   77,    2, 0x06 /* Public */,
       4,    1,   80,    2, 0x06 /* Public */,
       5,    1,   83,    2, 0x06 /* Public */,
       6,    1,   86,    2, 0x06 /* Public */,
       7,    1,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   92,    2, 0x08 /* Private */,
       9,    0,   93,    2, 0x08 /* Private */,
      10,    0,   94,    2, 0x08 /* Private */,
      11,    0,   95,    2, 0x08 /* Private */,
      12,    0,   96,    2, 0x08 /* Private */,
      13,    0,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void, QMetaType::QModelIndex,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TNNoticeListTableView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNNoticeListTableView *_t = static_cast<TNNoticeListTableView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->seOnTop((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->seOnNoTop((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->seOnRemoveSession((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 3: _t->seOnModifyGroupName((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: _t->seOnAlarm((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 5: _t->seOnNoAlarm((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 6: _t->onTop(); break;
        case 7: _t->onNoTop(); break;
        case 8: _t->onRemoveSession(); break;
        case 9: _t->onModifyGroupName(); break;
        case 10: _t->onAlarm(); break;
        case 11: _t->onNoAlarm(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNNoticeListTableView::*_t)(QModelIndex );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeListTableView::seOnTop)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNNoticeListTableView::*_t)(QModelIndex );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeListTableView::seOnNoTop)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNNoticeListTableView::*_t)(QModelIndex );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeListTableView::seOnRemoveSession)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TNNoticeListTableView::*_t)(QModelIndex );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeListTableView::seOnModifyGroupName)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (TNNoticeListTableView::*_t)(QModelIndex );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeListTableView::seOnAlarm)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (TNNoticeListTableView::*_t)(QModelIndex );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeListTableView::seOnNoAlarm)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject TNNoticeListTableView::staticMetaObject = {
    { &QTableView::staticMetaObject, qt_meta_stringdata_TNNoticeListTableView.data,
      qt_meta_data_TNNoticeListTableView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNNoticeListTableView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNNoticeListTableView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNNoticeListTableView.stringdata0))
        return static_cast<void*>(const_cast< TNNoticeListTableView*>(this));
    return QTableView::qt_metacast(_clname);
}

int TNNoticeListTableView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void TNNoticeListTableView::seOnTop(QModelIndex _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TNNoticeListTableView::seOnNoTop(QModelIndex _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TNNoticeListTableView::seOnRemoveSession(QModelIndex _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TNNoticeListTableView::seOnModifyGroupName(QModelIndex _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TNNoticeListTableView::seOnAlarm(QModelIndex _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TNNoticeListTableView::seOnNoAlarm(QModelIndex _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
