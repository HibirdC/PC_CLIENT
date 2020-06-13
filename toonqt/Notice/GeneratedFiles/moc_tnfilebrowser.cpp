/****************************************************************************
** Meta object code from reading C++ file 'tnfilebrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../details_notice/tnfilebrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tnfilebrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNFileBrowser_t {
    QByteArrayData data[10];
    char stringdata0[143];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNFileBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNFileBrowser_t qt_meta_stringdata_TNFileBrowser = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TNFileBrowser"
QT_MOC_LITERAL(1, 14, 12), // "actionRevote"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 17), // "actionSendForward"
QT_MOC_LITERAL(4, 46, 10), // "delFileMsg"
QT_MOC_LITERAL(5, 57, 25), // "cancelFileDownOrUploading"
QT_MOC_LITERAL(6, 83, 6), // "upload"
QT_MOC_LITERAL(7, 90, 17), // "onClickedOpenfile"
QT_MOC_LITERAL(8, 108, 16), // "onClickedOpendir"
QT_MOC_LITERAL(9, 125, 17) // "onCancelUploading"

    },
    "TNFileBrowser\0actionRevote\0\0"
    "actionSendForward\0delFileMsg\0"
    "cancelFileDownOrUploading\0upload\0"
    "onClickedOpenfile\0onClickedOpendir\0"
    "onCancelUploading"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNFileBrowser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       5,    0,   60,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   61,    2, 0x08 /* Private */,
       8,    0,   62,    2, 0x08 /* Private */,
       9,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TNFileBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNFileBrowser *_t = static_cast<TNFileBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->actionRevote(); break;
        case 1: _t->actionSendForward(); break;
        case 2: _t->delFileMsg(); break;
        case 3: _t->cancelFileDownOrUploading((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->cancelFileDownOrUploading(); break;
        case 5: _t->onClickedOpenfile(); break;
        case 6: _t->onClickedOpendir(); break;
        case 7: _t->onCancelUploading(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNFileBrowser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNFileBrowser::actionRevote)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNFileBrowser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNFileBrowser::actionSendForward)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNFileBrowser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNFileBrowser::delFileMsg)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TNFileBrowser::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNFileBrowser::cancelFileDownOrUploading)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TNFileBrowser::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TNFileBrowser.data,
      qt_meta_data_TNFileBrowser,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNFileBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNFileBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNFileBrowser.stringdata0))
        return static_cast<void*>(const_cast< TNFileBrowser*>(this));
    return QWidget::qt_metacast(_clname);
}

int TNFileBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void TNFileBrowser::actionRevote()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TNFileBrowser::actionSendForward()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void TNFileBrowser::delFileMsg()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void TNFileBrowser::cancelFileDownOrUploading(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
