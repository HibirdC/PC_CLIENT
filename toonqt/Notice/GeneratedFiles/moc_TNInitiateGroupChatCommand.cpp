/****************************************************************************
** Meta object code from reading C++ file 'TNInitiateGroupChatCommand.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ToonCommand/TNInitiateGroupChatCommand.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNInitiateGroupChatCommand.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNInitiateGroupChatCommand_t {
    QByteArrayData data[5];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNInitiateGroupChatCommand_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNInitiateGroupChatCommand_t qt_meta_stringdata_TNInitiateGroupChatCommand = {
    {
QT_MOC_LITERAL(0, 0, 26), // "TNInitiateGroupChatCommand"
QT_MOC_LITERAL(1, 27, 20), // "sigInitiateGroupChat"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 12), // "belongFeedId"
QT_MOC_LITERAL(4, 62, 11) // "groupChatId"

    },
    "TNInitiateGroupChatCommand\0"
    "sigInitiateGroupChat\0\0belongFeedId\0"
    "groupChatId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNInitiateGroupChatCommand[] = {

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
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

       0        // eod
};

void TNInitiateGroupChatCommand::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNInitiateGroupChatCommand *_t = static_cast<TNInitiateGroupChatCommand *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigInitiateGroupChat((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNInitiateGroupChatCommand::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNInitiateGroupChatCommand::sigInitiateGroupChat)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TNInitiateGroupChatCommand::staticMetaObject = {
    { &TNAbstractToonCommand::staticMetaObject, qt_meta_stringdata_TNInitiateGroupChatCommand.data,
      qt_meta_data_TNInitiateGroupChatCommand,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNInitiateGroupChatCommand::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNInitiateGroupChatCommand::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNInitiateGroupChatCommand.stringdata0))
        return static_cast<void*>(const_cast< TNInitiateGroupChatCommand*>(this));
    return TNAbstractToonCommand::qt_metacast(_clname);
}

int TNInitiateGroupChatCommand::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TNAbstractToonCommand::qt_metacall(_c, _id, _a);
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
void TNInitiateGroupChatCommand::sigInitiateGroupChat(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
