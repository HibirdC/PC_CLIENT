/****************************************************************************
** Meta object code from reading C++ file 'TNMsgDetailModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../details_notice/TNMsgDetailModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNMsgDetailModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNMsgDetailModel_t {
    QByteArrayData data[5];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNMsgDetailModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNMsgDetailModel_t qt_meta_stringdata_TNMsgDetailModel = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TNMsgDetailModel"
QT_MOC_LITERAL(1, 17, 10), // "reSendData"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 18), // "TNModelUserMessage"
QT_MOC_LITERAL(4, 48, 4) // "data"

    },
    "TNMsgDetailModel\0reSendData\0\0"
    "TNModelUserMessage\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNMsgDetailModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void TNMsgDetailModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNMsgDetailModel *_t = static_cast<TNMsgDetailModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->reSendData((*reinterpret_cast< TNModelUserMessage(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNMsgDetailModel::*_t)(TNModelUserMessage );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNMsgDetailModel::reSendData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TNMsgDetailModel::staticMetaObject = {
    { &TNTableModel::staticMetaObject, qt_meta_stringdata_TNMsgDetailModel.data,
      qt_meta_data_TNMsgDetailModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNMsgDetailModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNMsgDetailModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNMsgDetailModel.stringdata0))
        return static_cast<void*>(const_cast< TNMsgDetailModel*>(this));
    return TNTableModel::qt_metacast(_clname);
}

int TNMsgDetailModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TNTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TNMsgDetailModel::reSendData(TNModelUserMessage _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
