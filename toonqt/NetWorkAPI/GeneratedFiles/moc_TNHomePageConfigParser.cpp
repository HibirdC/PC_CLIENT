/****************************************************************************
** Meta object code from reading C++ file 'TNHomePageConfigParser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNHomePageConfigParser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNHomePageConfigParser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNHomePageConfigParser_t {
    QByteArrayData data[9];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNHomePageConfigParser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNHomePageConfigParser_t qt_meta_stringdata_TNHomePageConfigParser = {
    {
QT_MOC_LITERAL(0, 0, 22), // "TNHomePageConfigParser"
QT_MOC_LITERAL(1, 23, 14), // "parserFinished"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 26), // "slotServiceRequestFinished"
QT_MOC_LITERAL(4, 66, 14), // "QNetworkReply*"
QT_MOC_LITERAL(5, 81, 5), // "reply"
QT_MOC_LITERAL(6, 87, 11), // "slotOnError"
QT_MOC_LITERAL(7, 99, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(8, 127, 4) // "code"

    },
    "TNHomePageConfigParser\0parserFinished\0"
    "\0slotServiceRequestFinished\0QNetworkReply*\0"
    "reply\0slotOnError\0QNetworkReply::NetworkError\0"
    "code"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNHomePageConfigParser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   30,    2, 0x0a /* Public */,
       6,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void TNHomePageConfigParser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNHomePageConfigParser *_t = static_cast<TNHomePageConfigParser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->parserFinished(); break;
        case 1: _t->slotServiceRequestFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->slotOnError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNHomePageConfigParser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNHomePageConfigParser::parserFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TNHomePageConfigParser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TNHomePageConfigParser.data,
      qt_meta_data_TNHomePageConfigParser,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNHomePageConfigParser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNHomePageConfigParser::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNHomePageConfigParser.stringdata0))
        return static_cast<void*>(const_cast< TNHomePageConfigParser*>(this));
    return QObject::qt_metacast(_clname);
}

int TNHomePageConfigParser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TNHomePageConfigParser::parserFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
