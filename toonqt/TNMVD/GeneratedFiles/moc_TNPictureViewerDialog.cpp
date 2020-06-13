/****************************************************************************
** Meta object code from reading C++ file 'TNPictureViewerDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TNPictureViewerDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNPictureViewerDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNPictureViewerDialog_t {
    QByteArrayData data[14];
    char stringdata0[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNPictureViewerDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNPictureViewerDialog_t qt_meta_stringdata_TNPictureViewerDialog = {
    {
QT_MOC_LITERAL(0, 0, 21), // "TNPictureViewerDialog"
QT_MOC_LITERAL(1, 22, 14), // "downBigPicOver"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 20), // "originalDownFinished"
QT_MOC_LITERAL(4, 59, 5), // "msgId"
QT_MOC_LITERAL(5, 65, 9), // "file_path"
QT_MOC_LITERAL(6, 75, 18), // "onZoonInBtnClicked"
QT_MOC_LITERAL(7, 94, 19), // "onZoonOutBtnClicked"
QT_MOC_LITERAL(8, 114, 18), // "onRotateBtnClicked"
QT_MOC_LITERAL(9, 133, 18), // "onSaveAsBtnClicked"
QT_MOC_LITERAL(10, 152, 20), // "onPreviousBtnClicked"
QT_MOC_LITERAL(11, 173, 16), // "onNextBtnClicked"
QT_MOC_LITERAL(12, 190, 15), // "onMaxBtnClicked"
QT_MOC_LITERAL(13, 206, 17) // "onCloseBtnClicked"

    },
    "TNPictureViewerDialog\0downBigPicOver\0"
    "\0originalDownFinished\0msgId\0file_path\0"
    "onZoonInBtnClicked\0onZoonOutBtnClicked\0"
    "onRotateBtnClicked\0onSaveAsBtnClicked\0"
    "onPreviousBtnClicked\0onNextBtnClicked\0"
    "onMaxBtnClicked\0onCloseBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNPictureViewerDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,   65,    2, 0x0a /* Public */,
       6,    0,   72,    2, 0x09 /* Protected */,
       7,    0,   73,    2, 0x09 /* Protected */,
       8,    0,   74,    2, 0x09 /* Protected */,
       9,    0,   75,    2, 0x09 /* Protected */,
      10,    0,   76,    2, 0x09 /* Protected */,
      11,    0,   77,    2, 0x09 /* Protected */,
      12,    0,   78,    2, 0x09 /* Protected */,
      13,    0,   79,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,    2,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TNPictureViewerDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNPictureViewerDialog *_t = static_cast<TNPictureViewerDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downBigPicOver(); break;
        case 1: _t->originalDownFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->onZoonInBtnClicked(); break;
        case 3: _t->onZoonOutBtnClicked(); break;
        case 4: _t->onRotateBtnClicked(); break;
        case 5: _t->onSaveAsBtnClicked(); break;
        case 6: _t->onPreviousBtnClicked(); break;
        case 7: _t->onNextBtnClicked(); break;
        case 8: _t->onMaxBtnClicked(); break;
        case 9: _t->onCloseBtnClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNPictureViewerDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNPictureViewerDialog::downBigPicOver)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TNPictureViewerDialog::staticMetaObject = {
    { &DropShadowWidget::staticMetaObject, qt_meta_stringdata_TNPictureViewerDialog.data,
      qt_meta_data_TNPictureViewerDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNPictureViewerDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNPictureViewerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNPictureViewerDialog.stringdata0))
        return static_cast<void*>(const_cast< TNPictureViewerDialog*>(this));
    return DropShadowWidget::qt_metacast(_clname);
}

int TNPictureViewerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DropShadowWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void TNPictureViewerDialog::downBigPicOver()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
