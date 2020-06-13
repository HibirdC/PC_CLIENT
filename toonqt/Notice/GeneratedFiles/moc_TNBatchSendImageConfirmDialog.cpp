/****************************************************************************
** Meta object code from reading C++ file 'TNBatchSendImageConfirmDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNBatchSendImageConfirmDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNBatchSendImageConfirmDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_XPushButton_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_XPushButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_XPushButton_t qt_meta_stringdata_XPushButton = {
    {
QT_MOC_LITERAL(0, 0, 11) // "XPushButton"

    },
    "XPushButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_XPushButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void XPushButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject XPushButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_XPushButton.data,
      qt_meta_data_XPushButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *XPushButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *XPushButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_XPushButton.stringdata0))
        return static_cast<void*>(const_cast< XPushButton*>(this));
    return QPushButton::qt_metacast(_clname);
}

int XPushButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_ImageToolButton_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageToolButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageToolButton_t qt_meta_stringdata_ImageToolButton = {
    {
QT_MOC_LITERAL(0, 0, 15) // "ImageToolButton"

    },
    "ImageToolButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageToolButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ImageToolButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ImageToolButton::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata_ImageToolButton.data,
      qt_meta_data_ImageToolButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ImageToolButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageToolButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ImageToolButton.stringdata0))
        return static_cast<void*>(const_cast< ImageToolButton*>(this));
    return QToolButton::qt_metacast(_clname);
}

int ImageToolButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_TNBatchSendImageConfirmDialog_t {
    QByteArrayData data[8];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNBatchSendImageConfirmDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNBatchSendImageConfirmDialog_t qt_meta_stringdata_TNBatchSendImageConfirmDialog = {
    {
QT_MOC_LITERAL(0, 0, 29), // "TNBatchSendImageConfirmDialog"
QT_MOC_LITERAL(1, 30, 6), // "accept"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 15), // "slotRemoveImage"
QT_MOC_LITERAL(4, 54, 12), // "addThumbnail"
QT_MOC_LITERAL(5, 67, 8), // "fileName"
QT_MOC_LITERAL(6, 76, 11), // "buttonImage"
QT_MOC_LITERAL(7, 88, 9) // "showError"

    },
    "TNBatchSendImageConfirmDialog\0accept\0"
    "\0slotRemoveImage\0addThumbnail\0fileName\0"
    "buttonImage\0showError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNBatchSendImageConfirmDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    2,   36,    2, 0x08 /* Private */,
       7,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QImage,    5,    6,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void TNBatchSendImageConfirmDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNBatchSendImageConfirmDialog *_t = static_cast<TNBatchSendImageConfirmDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->slotRemoveImage(); break;
        case 2: _t->addThumbnail((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QImage(*)>(_a[2]))); break;
        case 3: _t->showError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TNBatchSendImageConfirmDialog::staticMetaObject = {
    { &DropShadowWidget::staticMetaObject, qt_meta_stringdata_TNBatchSendImageConfirmDialog.data,
      qt_meta_data_TNBatchSendImageConfirmDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNBatchSendImageConfirmDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNBatchSendImageConfirmDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNBatchSendImageConfirmDialog.stringdata0))
        return static_cast<void*>(const_cast< TNBatchSendImageConfirmDialog*>(this));
    return DropShadowWidget::qt_metacast(_clname);
}

int TNBatchSendImageConfirmDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DropShadowWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
