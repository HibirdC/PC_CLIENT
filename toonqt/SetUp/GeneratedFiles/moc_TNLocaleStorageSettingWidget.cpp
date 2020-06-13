/****************************************************************************
** Meta object code from reading C++ file 'TNLocaleStorageSettingWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNLocaleStorageSettingWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNLocaleStorageSettingWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNLocaleStorageSettingWidget_t {
    QByteArrayData data[18];
    char stringdata0[280];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNLocaleStorageSettingWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNLocaleStorageSettingWidget_t qt_meta_stringdata_TNLocaleStorageSettingWidget = {
    {
QT_MOC_LITERAL(0, 0, 28), // "TNLocaleStorageSettingWidget"
QT_MOC_LITERAL(1, 29, 19), // "updateSettingStatus"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 10), // "slotBootUp"
QT_MOC_LITERAL(4, 61, 5), // "state"
QT_MOC_LITERAL(5, 67, 13), // "slotNoDisturb"
QT_MOC_LITERAL(6, 81, 13), // "slotAutoLogin"
QT_MOC_LITERAL(7, 95, 26), // "slotCurrentLanguageChanged"
QT_MOC_LITERAL(8, 122, 5), // "index"
QT_MOC_LITERAL(9, 128, 20), // "slotChangePathDialog"
QT_MOC_LITERAL(10, 149, 21), // "slotOpenDirFileDialog"
QT_MOC_LITERAL(11, 171, 15), // "onHotKeyChanged"
QT_MOC_LITERAL(12, 187, 3), // "key"
QT_MOC_LITERAL(13, 191, 25), // "slotShortCutSettingDialog"
QT_MOC_LITERAL(14, 217, 22), // "onCheckBoxStateChanged"
QT_MOC_LITERAL(15, 240, 15), // "onScreenShotKey"
QT_MOC_LITERAL(16, 256, 18), // "QxtGlobalShortcut*"
QT_MOC_LITERAL(17, 275, 4) // "self"

    },
    "TNLocaleStorageSettingWidget\0"
    "updateSettingStatus\0\0slotBootUp\0state\0"
    "slotNoDisturb\0slotAutoLogin\0"
    "slotCurrentLanguageChanged\0index\0"
    "slotChangePathDialog\0slotOpenDirFileDialog\0"
    "onHotKeyChanged\0key\0slotShortCutSettingDialog\0"
    "onCheckBoxStateChanged\0onScreenShotKey\0"
    "QxtGlobalShortcut*\0self"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNLocaleStorageSettingWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   74,    2, 0x08 /* Private */,
       5,    1,   77,    2, 0x08 /* Private */,
       6,    1,   80,    2, 0x08 /* Private */,
       7,    1,   83,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    1,   88,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    1,   92,    2, 0x08 /* Private */,
      15,    1,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void TNLocaleStorageSettingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNLocaleStorageSettingWidget *_t = static_cast<TNLocaleStorageSettingWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateSettingStatus((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->slotBootUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotNoDisturb((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotAutoLogin((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotCurrentLanguageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slotChangePathDialog(); break;
        case 6: _t->slotOpenDirFileDialog(); break;
        case 7: _t->onHotKeyChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->slotShortCutSettingDialog(); break;
        case 9: _t->onCheckBoxStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->onScreenShotKey((*reinterpret_cast< QxtGlobalShortcut*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNLocaleStorageSettingWidget::*_t)(QString , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNLocaleStorageSettingWidget::updateSettingStatus)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TNLocaleStorageSettingWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TNLocaleStorageSettingWidget.data,
      qt_meta_data_TNLocaleStorageSettingWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNLocaleStorageSettingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNLocaleStorageSettingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNLocaleStorageSettingWidget.stringdata0))
        return static_cast<void*>(const_cast< TNLocaleStorageSettingWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TNLocaleStorageSettingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void TNLocaleStorageSettingWidget::updateSettingStatus(QString _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
