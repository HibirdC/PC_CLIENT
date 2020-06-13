/****************************************************************************
** Meta object code from reading C++ file 'Toon.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Toon.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Toon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Toon_t {
    QByteArrayData data[20];
    char stringdata0[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Toon_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Toon_t qt_meta_stringdata_Toon = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Toon"
QT_MOC_LITERAL(1, 5, 14), // "SendQuitSignal"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 13), // "windowsChange"
QT_MOC_LITERAL(4, 35, 6), // "status"
QT_MOC_LITERAL(5, 42, 13), // "MessageSignal"
QT_MOC_LITERAL(6, 56, 22), // "initNoticeLocalSession"
QT_MOC_LITERAL(7, 79, 12), // "trayDClicked"
QT_MOC_LITERAL(8, 92, 21), // "onVerionCheckTimerOut"
QT_MOC_LITERAL(9, 114, 17), // "onReceivedMessage"
QT_MOC_LITERAL(10, 132, 20), // "TNMessageListAdapter"
QT_MOC_LITERAL(11, 153, 7), // "adapter"
QT_MOC_LITERAL(12, 161, 8), // "isNotice"
QT_MOC_LITERAL(13, 170, 7), // "showMax"
QT_MOC_LITERAL(14, 178, 11), // "closeWidget"
QT_MOC_LITERAL(15, 190, 10), // "showWidget"
QT_MOC_LITERAL(16, 201, 17), // "windowsChangeSlot"
QT_MOC_LITERAL(17, 219, 27), // "on_notifyCurrentFeedChanged"
QT_MOC_LITERAL(18, 247, 6), // "feedID"
QT_MOC_LITERAL(19, 254, 11) // "quitAppSlot"

    },
    "Toon\0SendQuitSignal\0\0windowsChange\0"
    "status\0MessageSignal\0initNoticeLocalSession\0"
    "trayDClicked\0onVerionCheckTimerOut\0"
    "onReceivedMessage\0TNMessageListAdapter\0"
    "adapter\0isNotice\0showMax\0closeWidget\0"
    "showWidget\0windowsChangeSlot\0"
    "on_notifyCurrentFeedChanged\0feedID\0"
    "quitAppSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Toon[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    1,   80,    2, 0x06 /* Public */,
       5,    1,   83,    2, 0x06 /* Public */,
       6,    0,   86,    2, 0x06 /* Public */,
       7,    0,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   88,    2, 0x08 /* Private */,
       9,    2,   89,    2, 0x08 /* Private */,
      13,    1,   94,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    0,   98,    2, 0x0a /* Public */,
      16,    1,   99,    2, 0x0a /* Public */,
      17,    1,  102,    2, 0x0a /* Public */,
      19,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Bool,   11,   12,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,

       0        // eod
};

void Toon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Toon *_t = static_cast<Toon *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SendQuitSignal(); break;
        case 1: _t->windowsChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->MessageSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->initNoticeLocalSession(); break;
        case 4: _t->trayDClicked(); break;
        case 5: _t->onVerionCheckTimerOut(); break;
        case 6: _t->onReceivedMessage((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->showMax((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->closeWidget(); break;
        case 9: _t->showWidget(); break;
        case 10: _t->windowsChangeSlot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_notifyCurrentFeedChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->quitAppSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Toon::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Toon::SendQuitSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Toon::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Toon::windowsChange)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Toon::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Toon::MessageSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Toon::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Toon::initNoticeLocalSession)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Toon::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Toon::trayDClicked)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject Toon::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Toon.data,
      qt_meta_data_Toon,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Toon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Toon::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Toon.stringdata0))
        return static_cast<void*>(const_cast< Toon*>(this));
    if (!strcmp(_clname, "QAbstractNativeEventFilter"))
        return static_cast< QAbstractNativeEventFilter*>(const_cast< Toon*>(this));
    return QWidget::qt_metacast(_clname);
}

int Toon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void Toon::SendQuitSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Toon::windowsChange(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Toon::MessageSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Toon::initNoticeLocalSession()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void Toon::trayDClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
