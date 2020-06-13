/****************************************************************************
** Meta object code from reading C++ file 'TNGrowingTextBrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../details_notice/TNGrowingTextBrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNGrowingTextBrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNGrowingTextBrowser_t {
    QByteArrayData data[11];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNGrowingTextBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNGrowingTextBrowser_t qt_meta_stringdata_TNGrowingTextBrowser = {
    {
QT_MOC_LITERAL(0, 0, 20), // "TNGrowingTextBrowser"
QT_MOC_LITERAL(1, 21, 12), // "actionRevote"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 17), // "actionSendForward"
QT_MOC_LITERAL(4, 53, 12), // "actionSaveAs"
QT_MOC_LITERAL(5, 66, 15), // "actionDeleteMsg"
QT_MOC_LITERAL(6, 82, 10), // "customCopy"
QT_MOC_LITERAL(7, 93, 14), // "OnStartAnimate"
QT_MOC_LITERAL(8, 108, 5), // "frame"
QT_MOC_LITERAL(9, 114, 15), // "onAnchorClicked"
QT_MOC_LITERAL(10, 130, 3) // "url"

    },
    "TNGrowingTextBrowser\0actionRevote\0\0"
    "actionSendForward\0actionSaveAs\0"
    "actionDeleteMsg\0customCopy\0OnStartAnimate\0"
    "frame\0onAnchorClicked\0url"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNGrowingTextBrowser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    0,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   53,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
       9,    1,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QUrl,   10,

       0        // eod
};

void TNGrowingTextBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNGrowingTextBrowser *_t = static_cast<TNGrowingTextBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->actionRevote(); break;
        case 1: _t->actionSendForward(); break;
        case 2: _t->actionSaveAs(); break;
        case 3: _t->actionDeleteMsg(); break;
        case 4: _t->customCopy(); break;
        case 5: _t->OnStartAnimate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onAnchorClicked((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNGrowingTextBrowser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNGrowingTextBrowser::actionRevote)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNGrowingTextBrowser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNGrowingTextBrowser::actionSendForward)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNGrowingTextBrowser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNGrowingTextBrowser::actionSaveAs)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TNGrowingTextBrowser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNGrowingTextBrowser::actionDeleteMsg)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TNGrowingTextBrowser::staticMetaObject = {
    { &QTextBrowser::staticMetaObject, qt_meta_stringdata_TNGrowingTextBrowser.data,
      qt_meta_data_TNGrowingTextBrowser,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNGrowingTextBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNGrowingTextBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNGrowingTextBrowser.stringdata0))
        return static_cast<void*>(const_cast< TNGrowingTextBrowser*>(this));
    return QTextBrowser::qt_metacast(_clname);
}

int TNGrowingTextBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TNGrowingTextBrowser::actionRevote()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TNGrowingTextBrowser::actionSendForward()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void TNGrowingTextBrowser::actionSaveAs()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void TNGrowingTextBrowser::actionDeleteMsg()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
