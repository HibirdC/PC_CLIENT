/****************************************************************************
** Meta object code from reading C++ file 'TNCreateGroupChatDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GroupChat/TNCreateGroupChatDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNCreateGroupChatDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNCreateGroupChatDialog_t {
    QByteArrayData data[9];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNCreateGroupChatDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNCreateGroupChatDialog_t qt_meta_stringdata_TNCreateGroupChatDialog = {
    {
QT_MOC_LITERAL(0, 0, 23), // "TNCreateGroupChatDialog"
QT_MOC_LITERAL(1, 24, 6), // "accept"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 19), // "slotCardItemClicked"
QT_MOC_LITERAL(4, 52, 5), // "index"
QT_MOC_LITERAL(5, 58, 10), // "slotSearch"
QT_MOC_LITERAL(6, 69, 4), // "text"
QT_MOC_LITERAL(7, 74, 19), // "slotLeftItemClicked"
QT_MOC_LITERAL(8, 94, 20) // "slotRightItemClicked"

    },
    "TNCreateGroupChatDialog\0accept\0\0"
    "slotCardItemClicked\0index\0slotSearch\0"
    "text\0slotLeftItemClicked\0slotRightItemClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNCreateGroupChatDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       7,    1,   46,    2, 0x08 /* Private */,
       8,    1,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void, QMetaType::QModelIndex,    4,

       0        // eod
};

void TNCreateGroupChatDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNCreateGroupChatDialog *_t = static_cast<TNCreateGroupChatDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->slotCardItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->slotSearch((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slotLeftItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->slotRightItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TNCreateGroupChatDialog::staticMetaObject = {
    { &DropShadowWidget::staticMetaObject, qt_meta_stringdata_TNCreateGroupChatDialog.data,
      qt_meta_data_TNCreateGroupChatDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNCreateGroupChatDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNCreateGroupChatDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNCreateGroupChatDialog.stringdata0))
        return static_cast<void*>(const_cast< TNCreateGroupChatDialog*>(this));
    return DropShadowWidget::qt_metacast(_clname);
}

int TNCreateGroupChatDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DropShadowWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
