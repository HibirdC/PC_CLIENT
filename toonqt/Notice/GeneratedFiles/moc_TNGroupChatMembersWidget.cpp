/****************************************************************************
** Meta object code from reading C++ file 'TNGroupChatMembersWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GroupChat/TNGroupChatMembersWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TNGroupChatMembersWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TNGroupChatMembersWidget_t {
    QByteArrayData data[23];
    char stringdata0[338];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TNGroupChatMembersWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TNGroupChatMembersWidget_t qt_meta_stringdata_TNGroupChatMembersWidget = {
    {
QT_MOC_LITERAL(0, 0, 24), // "TNGroupChatMembersWidget"
QT_MOC_LITERAL(1, 25, 23), // "createGroupChatFinished"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 20), // "TNMessageListAdapter"
QT_MOC_LITERAL(4, 71, 7), // "session"
QT_MOC_LITERAL(5, 79, 21), // "exitGroupChatFinished"
QT_MOC_LITERAL(6, 101, 18), // "messageListAdapter"
QT_MOC_LITERAL(7, 120, 11), // "widgetHided"
QT_MOC_LITERAL(8, 132, 10), // "slotSearch"
QT_MOC_LITERAL(9, 143, 4), // "text"
QT_MOC_LITERAL(10, 148, 23), // "slotSelectContactDialog"
QT_MOC_LITERAL(11, 172, 31), // "slotRemoveGroupChatMemberDialog"
QT_MOC_LITERAL(12, 204, 18), // "slotSelectFinished"
QT_MOC_LITERAL(13, 223, 15), // "QList<TNFriend>"
QT_MOC_LITERAL(14, 239, 13), // "selectFriends"
QT_MOC_LITERAL(15, 253, 17), // "slotExitGroupChat"
QT_MOC_LITERAL(16, 271, 15), // "slotMemberFrame"
QT_MOC_LITERAL(17, 287, 5), // "index"
QT_MOC_LITERAL(18, 293, 21), // "on_notifyReMarkUpdate"
QT_MOC_LITERAL(19, 315, 4), // "from"
QT_MOC_LITERAL(20, 320, 2), // "to"
QT_MOC_LITERAL(21, 323, 6), // "remark"
QT_MOC_LITERAL(22, 330, 7) // "sources"

    },
    "TNGroupChatMembersWidget\0"
    "createGroupChatFinished\0\0TNMessageListAdapter\0"
    "session\0exitGroupChatFinished\0"
    "messageListAdapter\0widgetHided\0"
    "slotSearch\0text\0slotSelectContactDialog\0"
    "slotRemoveGroupChatMemberDialog\0"
    "slotSelectFinished\0QList<TNFriend>\0"
    "selectFriends\0slotExitGroupChat\0"
    "slotMemberFrame\0index\0on_notifyReMarkUpdate\0"
    "from\0to\0remark\0sources"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TNGroupChatMembersWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,
       7,    0,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   71,    2, 0x08 /* Private */,
      10,    0,   74,    2, 0x08 /* Private */,
      11,    0,   75,    2, 0x08 /* Private */,
      12,    1,   76,    2, 0x08 /* Private */,
      15,    0,   79,    2, 0x08 /* Private */,
      16,    1,   80,    2, 0x08 /* Private */,
      18,    4,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,   17,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,   19,   20,   21,   22,

       0        // eod
};

void TNGroupChatMembersWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TNGroupChatMembersWidget *_t = static_cast<TNGroupChatMembersWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->createGroupChatFinished((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1]))); break;
        case 1: _t->exitGroupChatFinished((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1]))); break;
        case 2: _t->widgetHided(); break;
        case 3: _t->slotSearch((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->slotSelectContactDialog(); break;
        case 5: _t->slotRemoveGroupChatMemberDialog(); break;
        case 6: _t->slotSelectFinished((*reinterpret_cast< QList<TNFriend>(*)>(_a[1]))); break;
        case 7: _t->slotExitGroupChat(); break;
        case 8: _t->slotMemberFrame((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 9: _t->on_notifyReMarkUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<TNFriend> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TNGroupChatMembersWidget::*_t)(TNMessageListAdapter );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNGroupChatMembersWidget::createGroupChatFinished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TNGroupChatMembersWidget::*_t)(TNMessageListAdapter );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNGroupChatMembersWidget::exitGroupChatFinished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TNGroupChatMembersWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TNGroupChatMembersWidget::widgetHided)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject TNGroupChatMembersWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TNGroupChatMembersWidget.data,
      qt_meta_data_TNGroupChatMembersWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TNGroupChatMembersWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TNGroupChatMembersWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TNGroupChatMembersWidget.stringdata0))
        return static_cast<void*>(const_cast< TNGroupChatMembersWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TNGroupChatMembersWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void TNGroupChatMembersWidget::createGroupChatFinished(TNMessageListAdapter _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TNGroupChatMembersWidget::exitGroupChatFinished(TNMessageListAdapter _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TNGroupChatMembersWidget::widgetHided()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
