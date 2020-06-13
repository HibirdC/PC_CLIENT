/****************************************************************************
** Meta object code from reading C++ file 'TNDownloadProgressDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNDownloadProgressDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNDownloadProgressDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNDownloadProgressDialog_t {
    QByteArrayData data[13];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNDownloadProgressDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNDownloadProgressDialog_t qt_meta_stringdata_TNDownloadProgressDialog = {
    {
QT_MOC_LITERAL(0, 0, 24), // "TNDownloadProgressDialog"
QT_MOC_LITERAL(1, 25, 16), // "slotDownLoaAgain"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 23), // "slotFromDesktopBrownser"
QT_MOC_LITERAL(4, 67, 17), // "onDownloadProcess"
QT_MOC_LITERAL(5, 85, 13), // "bytesReceived"
QT_MOC_LITERAL(6, 99, 10), // "bytesTotal"
QT_MOC_LITERAL(7, 110, 15), // "onReplyFinished"
QT_MOC_LITERAL(8, 126, 10), // "statusCode"
QT_MOC_LITERAL(9, 137, 11), // "zipFileName"
QT_MOC_LITERAL(10, 149, 15), // "slotHandleError"
QT_MOC_LITERAL(11, 165, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(12, 193, 4) // "code"

    },
    "TNDownloadProgressDialog\0slotDownLoaAgain\0"
    "\0slotFromDesktopBrownser\0onDownloadProcess\0"
    "bytesReceived\0bytesTotal\0onReplyFinished\0"
    "statusCode\0zipFileName\0slotHandleError\0"
    "QNetworkReply::NetworkError\0code"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNDownloadProgressDialog[] = {

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
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    2,   41,    2, 0x08 /* Private */,
       7,    2,   46,    2, 0x08 /* Private */,
      10,    1,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    5,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void TNDownloadProgressDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNDownloadProgressDialog *_t = static_cast<TNDownloadProgressDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotDownLoaAgain(); break;
        case 1: _t->slotFromDesktopBrownser(); break;
        case 2: _t->onDownloadProcess((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 3: _t->onReplyFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->slotHandleError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    }
}

const QMetaObject TNDownloadProgressDialog::staticMetaObject = {
    { &DropShadowWidget::staticMetaObject, qt_meta_stringdata_TNDownloadProgressDialog.data,
      qt_meta_data_TNDownloadProgressDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNDownloadProgressDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNDownloadProgressDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNDownloadProgressDialog.stringdata0))
        return static_cast<void*>(const_cast< TNDownloadProgressDialog*>(this));
    return DropShadowWidget::qt_metacast(_clname);
}

int TNDownloadProgressDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DropShadowWidget::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_END_MOC_NAMESPACE
