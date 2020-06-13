/****************************************************************************
** Meta object code from reading C++ file 'SendFowardSelectContactDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SendFowardSelectContactDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SendFowardSelectContactDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SendFowardSelectContactDialog_t {
    QByteArrayData data[15];
    char stringdata0[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SendFowardSelectContactDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SendFowardSelectContactDialog_t qt_meta_stringdata_SendFowardSelectContactDialog = {
    {
QT_MOC_LITERAL(0, 0, 29), // "SendFowardSelectContactDialog"
QT_MOC_LITERAL(1, 30, 14), // "selectFinished"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 27), // "QList<TNMessageListAdapter>"
QT_MOC_LITERAL(4, 74, 14), // "selectSessions"
QT_MOC_LITERAL(5, 89, 15), // "QList<TNFriend>"
QT_MOC_LITERAL(6, 105, 13), // "selectFriends"
QT_MOC_LITERAL(7, 119, 24), // "QList<TNStructGroupChat>"
QT_MOC_LITERAL(8, 144, 16), // "selectGroupChats"
QT_MOC_LITERAL(9, 161, 6), // "accept"
QT_MOC_LITERAL(10, 168, 10), // "slotSearch"
QT_MOC_LITERAL(11, 179, 4), // "text"
QT_MOC_LITERAL(12, 184, 19), // "slotLeftItemClicked"
QT_MOC_LITERAL(13, 204, 5), // "index"
QT_MOC_LITERAL(14, 210, 20) // "slotRightItemClicked"

    },
    "SendFowardSelectContactDialog\0"
    "selectFinished\0\0QList<TNMessageListAdapter>\0"
    "selectSessions\0QList<TNFriend>\0"
    "selectFriends\0QList<TNStructGroupChat>\0"
    "selectGroupChats\0accept\0slotSearch\0"
    "text\0slotLeftItemClicked\0index\0"
    "slotRightItemClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SendFowardSelectContactDialog[] = {

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
       9,    0,   46,    2, 0x0a /* Public */,
      10,    1,   47,    2, 0x08 /* Private */,
      12,    1,   50,    2, 0x08 /* Private */,
      14,    1,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QModelIndex,   13,
    QMetaType::Void, QMetaType::QModelIndex,   13,

       0        // eod
};

void SendFowardSelectContactDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SendFowardSelectContactDialog *_t = static_cast<SendFowardSelectContactDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectFinished((*reinterpret_cast< QList<TNMessageListAdapter>(*)>(_a[1])),(*reinterpret_cast< QList<TNFriend>(*)>(_a[2])),(*reinterpret_cast< QList<TNStructGroupChat>(*)>(_a[3]))); break;
        case 1: _t->accept(); break;
        case 2: _t->slotSearch((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slotLeftItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->slotRightItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<TNFriend> >(); break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<TNStructGroupChat> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SendFowardSelectContactDialog::*_t)(QList<TNMessageListAdapter> , QList<TNFriend> , QList<TNStructGroupChat> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SendFowardSelectContactDialog::selectFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject SendFowardSelectContactDialog::staticMetaObject = {
    { &DropShadowWidget::staticMetaObject, qt_meta_stringdata_SendFowardSelectContactDialog.data,
      qt_meta_data_SendFowardSelectContactDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SendFowardSelectContactDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SendFowardSelectContactDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SendFowardSelectContactDialog.stringdata0))
        return static_cast<void*>(const_cast< SendFowardSelectContactDialog*>(this));
    return DropShadowWidget::qt_metacast(_clname);
}

int SendFowardSelectContactDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SendFowardSelectContactDialog::selectFinished(QList<TNMessageListAdapter> _t1, QList<TNFriend> _t2, QList<TNStructGroupChat> _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
