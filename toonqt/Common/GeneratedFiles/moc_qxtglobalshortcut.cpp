/****************************************************************************
** Meta object code from reading C++ file 'qxtglobalshortcut.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../toonsdk/qxtglobalshortcut/qxtglobalshortcut.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qxtglobalshortcut.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QxtGlobalShortcut_t {
    QByteArrayData data[11];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QxtGlobalShortcut_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QxtGlobalShortcut_t qt_meta_stringdata_QxtGlobalShortcut = {
    {
QT_MOC_LITERAL(0, 0, 17), // "QxtGlobalShortcut"
QT_MOC_LITERAL(1, 18, 9), // "activated"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 18), // "QxtGlobalShortcut*"
QT_MOC_LITERAL(4, 48, 4), // "self"
QT_MOC_LITERAL(5, 53, 10), // "setEnabled"
QT_MOC_LITERAL(6, 64, 7), // "enabled"
QT_MOC_LITERAL(7, 72, 11), // "setDisabled"
QT_MOC_LITERAL(8, 84, 8), // "disabled"
QT_MOC_LITERAL(9, 93, 5), // "valid"
QT_MOC_LITERAL(10, 99, 8) // "shortcut"

    },
    "QxtGlobalShortcut\0activated\0\0"
    "QxtGlobalShortcut*\0self\0setEnabled\0"
    "enabled\0setDisabled\0disabled\0valid\0"
    "shortcut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QxtGlobalShortcut[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       3,   50, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   42,    2, 0x0a /* Public */,
       5,    0,   45,    2, 0x2a /* Public | MethodCloned */,
       7,    1,   46,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,

 // properties: name, type, flags
       6, QMetaType::Bool, 0x00095103,
       9, QMetaType::Bool, 0x00095001,
      10, QMetaType::QKeySequence, 0x00095103,

       0        // eod
};

void QxtGlobalShortcut::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QxtGlobalShortcut *_t = static_cast<QxtGlobalShortcut *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->activated((*reinterpret_cast< QxtGlobalShortcut*(*)>(_a[1]))); break;
        case 1: _t->setEnabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setEnabled(); break;
        case 3: _t->setDisabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setDisabled(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QxtGlobalShortcut* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QxtGlobalShortcut::*_t)(QxtGlobalShortcut * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QxtGlobalShortcut::activated)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        QxtGlobalShortcut *_t = static_cast<QxtGlobalShortcut *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isEnabled(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->isValid(); break;
        case 2: *reinterpret_cast< QKeySequence*>(_v) = _t->shortcut(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        QxtGlobalShortcut *_t = static_cast<QxtGlobalShortcut *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setEnabled(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setShortcut(*reinterpret_cast< QKeySequence*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject QxtGlobalShortcut::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QxtGlobalShortcut.data,
      qt_meta_data_QxtGlobalShortcut,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QxtGlobalShortcut::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QxtGlobalShortcut::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QxtGlobalShortcut.stringdata0))
        return static_cast<void*>(const_cast< QxtGlobalShortcut*>(this));
    return QObject::qt_metacast(_clname);
}

int QxtGlobalShortcut::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QxtGlobalShortcut::activated(QxtGlobalShortcut * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
