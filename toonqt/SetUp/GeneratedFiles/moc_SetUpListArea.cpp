/****************************************************************************
** Meta object code from reading C++ file 'SetUpListArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SetUpListArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SetUpListArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SetUpListArea_t {
    QByteArrayData data[19];
    char stringdata0[316];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetUpListArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetUpListArea_t qt_meta_stringdata_SetUpListArea = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SetUpListArea"
QT_MOC_LITERAL(1, 14, 13), // "clickedButton"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "index"
QT_MOC_LITERAL(4, 35, 19), // "syncCatalogFinished"
QT_MOC_LITERAL(5, 55, 16), // "syncCatalogStart"
QT_MOC_LITERAL(6, 72, 20), // "slotAppearanceButton"
QT_MOC_LITERAL(7, 93, 23), // "slotLocaleStorageButton"
QT_MOC_LITERAL(8, 117, 23), // "slotUserAgreementButton"
QT_MOC_LITERAL(9, 141, 17), // "slotAboutUsButton"
QT_MOC_LITERAL(10, 159, 19), // "slotExitLoginButton"
QT_MOC_LITERAL(11, 179, 21), // "slotSyncCatalogButton"
QT_MOC_LITERAL(12, 201, 20), // "onSyncCatalogFinised"
QT_MOC_LITERAL(13, 222, 29), // "on_notifyCheckVersionFinished"
QT_MOC_LITERAL(14, 252, 13), // "isNeedUpgrade"
QT_MOC_LITERAL(15, 266, 14), // "isForceUpgrade"
QT_MOC_LITERAL(16, 281, 11), // "downLoadURL"
QT_MOC_LITERAL(17, 293, 10), // "nCheckType"
QT_MOC_LITERAL(18, 304, 11) // "versionDesc"

    },
    "SetUpListArea\0clickedButton\0\0index\0"
    "syncCatalogFinished\0syncCatalogStart\0"
    "slotAppearanceButton\0slotLocaleStorageButton\0"
    "slotUserAgreementButton\0slotAboutUsButton\0"
    "slotExitLoginButton\0slotSyncCatalogButton\0"
    "onSyncCatalogFinised\0on_notifyCheckVersionFinished\0"
    "isNeedUpgrade\0isForceUpgrade\0downLoadURL\0"
    "nCheckType\0versionDesc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetUpListArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    0,   72,    2, 0x06 /* Public */,
       5,    0,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   74,    2, 0x0a /* Public */,
       7,    0,   75,    2, 0x0a /* Public */,
       8,    0,   76,    2, 0x0a /* Public */,
       9,    0,   77,    2, 0x0a /* Public */,
      10,    0,   78,    2, 0x0a /* Public */,
      11,    0,   79,    2, 0x0a /* Public */,
      12,    0,   80,    2, 0x0a /* Public */,
      13,    5,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::QString, QMetaType::Int, QMetaType::QString,   14,   15,   16,   17,   18,

       0        // eod
};

void SetUpListArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SetUpListArea *_t = static_cast<SetUpListArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clickedButton((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->syncCatalogFinished(); break;
        case 2: _t->syncCatalogStart(); break;
        case 3: _t->slotAppearanceButton(); break;
        case 4: _t->slotLocaleStorageButton(); break;
        case 5: _t->slotUserAgreementButton(); break;
        case 6: _t->slotAboutUsButton(); break;
        case 7: _t->slotExitLoginButton(); break;
        case 8: _t->slotSyncCatalogButton(); break;
        case 9: _t->onSyncCatalogFinised(); break;
        case 10: _t->on_notifyCheckVersionFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SetUpListArea::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetUpListArea::clickedButton)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SetUpListArea::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetUpListArea::syncCatalogFinished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SetUpListArea::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SetUpListArea::syncCatalogStart)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject SetUpListArea::staticMetaObject = {
    { &ListAreaBase::staticMetaObject, qt_meta_stringdata_SetUpListArea.data,
      qt_meta_data_SetUpListArea,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SetUpListArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetUpListArea::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SetUpListArea.stringdata0))
        return static_cast<void*>(const_cast< SetUpListArea*>(this));
    return ListAreaBase::qt_metacast(_clname);
}

int SetUpListArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ListAreaBase::qt_metacall(_c, _id, _a);
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
void SetUpListArea::clickedButton(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SetUpListArea::syncCatalogFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void SetUpListArea::syncCatalogStart()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
