/****************************************************************************
** Meta object code from reading C++ file 'TNNoticeDetailTableWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNNoticeDetailTableWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNNoticeDetailTableWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNNoticeDetailTableWidget_t {
    QByteArrayData data[9];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNNoticeDetailTableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNNoticeDetailTableWidget_t qt_meta_stringdata_TNNoticeDetailTableWidget = {
    {
QT_MOC_LITERAL(0, 0, 25), // "TNNoticeDetailTableWidget"
QT_MOC_LITERAL(1, 26, 20), // "readSessionUnreadNum"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 9), // "sessionId"
QT_MOC_LITERAL(4, 58, 6), // "number"
QT_MOC_LITERAL(5, 65, 16), // "updateTrayUnRead"
QT_MOC_LITERAL(6, 82, 30), // "VerticalScrollBaScrollToBottom"
QT_MOC_LITERAL(7, 113, 22), // "VerticalScrollbarMoved"
QT_MOC_LITERAL(8, 136, 17) // "onFocuseInTimeOut"

    },
    "TNNoticeDetailTableWidget\0"
    "readSessionUnreadNum\0\0sessionId\0number\0"
    "updateTrayUnRead\0VerticalScrollBaScrollToBottom\0"
    "VerticalScrollbarMoved\0onFocuseInTimeOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNNoticeDetailTableWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       5,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   47,    2, 0x08 /* Private */,
       7,    1,   52,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void TNNoticeDetailTableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNNoticeDetailTableWidget *_t = static_cast<TNNoticeDetailTableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readSessionUnreadNum((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->updateTrayUnRead((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->VerticalScrollBaScrollToBottom((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->VerticalScrollbarMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onFocuseInTimeOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNNoticeDetailTableWidget::*_t)(const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeDetailTableWidget::readSessionUnreadNum)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNNoticeDetailTableWidget::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNNoticeDetailTableWidget::updateTrayUnRead)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject TNNoticeDetailTableWidget::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_TNNoticeDetailTableWidget.data,
      qt_meta_data_TNNoticeDetailTableWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNNoticeDetailTableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNNoticeDetailTableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNNoticeDetailTableWidget.stringdata0))
        return static_cast<void*>(const_cast< TNNoticeDetailTableWidget*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int TNNoticeDetailTableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
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
void TNNoticeDetailTableWidget::readSessionUnreadNum(const QString & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TNNoticeDetailTableWidget::updateTrayUnRead(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
