/****************************************************************************
** Meta object code from reading C++ file 'tnaudiobrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../details_notice/tnaudiobrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tnaudiobrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNAudioBrowser_t {
    QByteArrayData data[4];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNAudioBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNAudioBrowser_t qt_meta_stringdata_TNAudioBrowser = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TNAudioBrowser"
QT_MOC_LITERAL(1, 15, 12), // "actionRevote"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 15) // "actionDeleteMsg"

    },
    "TNAudioBrowser\0actionRevote\0\0"
    "actionDeleteMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNAudioBrowser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TNAudioBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNAudioBrowser *_t = static_cast<TNAudioBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->actionRevote(); break;
        case 1: _t->actionDeleteMsg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNAudioBrowser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNAudioBrowser::actionRevote)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNAudioBrowser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNAudioBrowser::actionDeleteMsg)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TNAudioBrowser::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TNAudioBrowser.data,
      qt_meta_data_TNAudioBrowser,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNAudioBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNAudioBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNAudioBrowser.stringdata0))
        return static_cast<void*>(const_cast< TNAudioBrowser*>(this));
    return QWidget::qt_metacast(_clname);
}

int TNAudioBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TNAudioBrowser::actionRevote()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TNAudioBrowser::actionDeleteMsg()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
