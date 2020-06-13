/****************************************************************************
** Meta object code from reading C++ file 'TNAboutUsWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNAboutUsWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNAboutUsWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNAboutUsWidget_t {
    QByteArrayData data[11];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNAboutUsWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNAboutUsWidget_t qt_meta_stringdata_TNAboutUsWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TNAboutUsWidget"
QT_MOC_LITERAL(1, 16, 20), // "checkVersionFinished"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 27), // "slotCheckUpdateButtonDialog"
QT_MOC_LITERAL(4, 66, 26), // "slotFeedBackProposalDialog"
QT_MOC_LITERAL(5, 93, 29), // "on_notifyCheckVersionFinished"
QT_MOC_LITERAL(6, 123, 13), // "isNeedUpgrade"
QT_MOC_LITERAL(7, 137, 14), // "isForceUpgrade"
QT_MOC_LITERAL(8, 152, 11), // "downLoadURL"
QT_MOC_LITERAL(9, 164, 10), // "nCheckType"
QT_MOC_LITERAL(10, 175, 11) // "versionDesc"

    },
    "TNAboutUsWidget\0checkVersionFinished\0"
    "\0slotCheckUpdateButtonDialog\0"
    "slotFeedBackProposalDialog\0"
    "on_notifyCheckVersionFinished\0"
    "isNeedUpgrade\0isForceUpgrade\0downLoadURL\0"
    "nCheckType\0versionDesc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNAboutUsWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    5,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::QString, QMetaType::Int, QMetaType::QString,    6,    7,    8,    9,   10,

       0        // eod
};

void TNAboutUsWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNAboutUsWidget *_t = static_cast<TNAboutUsWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->checkVersionFinished(); break;
        case 1: _t->slotCheckUpdateButtonDialog(); break;
        case 2: _t->slotFeedBackProposalDialog(); break;
        case 3: _t->on_notifyCheckVersionFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNAboutUsWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNAboutUsWidget::checkVersionFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TNAboutUsWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TNAboutUsWidget.data,
      qt_meta_data_TNAboutUsWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNAboutUsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNAboutUsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNAboutUsWidget.stringdata0))
        return static_cast<void*>(const_cast< TNAboutUsWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TNAboutUsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TNAboutUsWidget::checkVersionFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
