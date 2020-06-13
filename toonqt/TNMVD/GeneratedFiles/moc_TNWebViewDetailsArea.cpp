/****************************************************************************
** Meta object code from reading C++ file 'TNWebViewDetailsArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNWebViewDetailsArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNWebViewDetailsArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNWebViewDetailsArea_t {
    QByteArrayData data[12];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNWebViewDetailsArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNWebViewDetailsArea_t qt_meta_stringdata_TNWebViewDetailsArea = {
    {
QT_MOC_LITERAL(0, 0, 20), // "TNWebViewDetailsArea"
QT_MOC_LITERAL(1, 21, 33), // "slotReceiveMessageFromNewFrie..."
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 4), // "text"
QT_MOC_LITERAL(4, 61, 10), // "slotToChat"
QT_MOC_LITERAL(5, 72, 4), // "json"
QT_MOC_LITERAL(6, 77, 15), // "CloseDetailPage"
QT_MOC_LITERAL(7, 93, 6), // "feedId"
QT_MOC_LITERAL(8, 100, 8), // "belongId"
QT_MOC_LITERAL(9, 109, 25), // "slotFriendWebLoadFinished"
QT_MOC_LITERAL(10, 135, 2), // "ok"
QT_MOC_LITERAL(11, 138, 24) // "slotFrameWebLoadFinished"

    },
    "TNWebViewDetailsArea\0"
    "slotReceiveMessageFromNewFriendH5\0\0"
    "text\0slotToChat\0json\0CloseDetailPage\0"
    "feedId\0belongId\0slotFriendWebLoadFinished\0"
    "ok\0slotFrameWebLoadFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNWebViewDetailsArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       6,    2,   45,    2, 0x0a /* Public */,
       9,    1,   50,    2, 0x0a /* Public */,
      11,    1,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QJsonObject,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,

       0        // eod
};

void TNWebViewDetailsArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNWebViewDetailsArea *_t = static_cast<TNWebViewDetailsArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotReceiveMessageFromNewFriendH5((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->slotToChat((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 2: _t->CloseDetailPage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->slotFriendWebLoadFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->slotFrameWebLoadFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TNWebViewDetailsArea::staticMetaObject = {
    { &DetailsAreaBase::staticMetaObject, qt_meta_stringdata_TNWebViewDetailsArea.data,
      qt_meta_data_TNWebViewDetailsArea,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNWebViewDetailsArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNWebViewDetailsArea::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNWebViewDetailsArea.stringdata0))
        return static_cast<void*>(const_cast< TNWebViewDetailsArea*>(this));
    return DetailsAreaBase::qt_metacast(_clname);
}

int TNWebViewDetailsArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DetailsAreaBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
