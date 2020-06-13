/****************************************************************************
** Meta object code from reading C++ file 'NoticeListArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../list_notice/NoticeListArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NoticeListArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NoticeListArea_t {
    QByteArrayData data[85];
    char stringdata0[1315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NoticeListArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NoticeListArea_t qt_meta_stringdata_NoticeListArea = {
    {
QT_MOC_LITERAL(0, 0, 14), // "NoticeListArea"
QT_MOC_LITERAL(1, 15, 15), // "ListAreaClicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "index"
QT_MOC_LITERAL(4, 38, 21), // "ListAreaDoubleClicked"
QT_MOC_LITERAL(5, 60, 20), // "messageNumberChanged"
QT_MOC_LITERAL(6, 81, 5), // "count"
QT_MOC_LITERAL(7, 87, 21), // "manualModifyGroupName"
QT_MOC_LITERAL(8, 109, 9), // "sessionId"
QT_MOC_LITERAL(9, 119, 4), // "name"
QT_MOC_LITERAL(10, 124, 26), // "manualRemoveCurrentSession"
QT_MOC_LITERAL(11, 151, 10), // "isSelected"
QT_MOC_LITERAL(12, 162, 13), // "messageNotify"
QT_MOC_LITERAL(13, 176, 20), // "TNMessageListAdapter"
QT_MOC_LITERAL(14, 197, 6), // "adpter"
QT_MOC_LITERAL(15, 204, 8), // "isNotice"
QT_MOC_LITERAL(16, 213, 17), // "reLoadDetailsData"
QT_MOC_LITERAL(17, 231, 21), // "TNMessageListAdapter*"
QT_MOC_LITERAL(18, 253, 7), // "adapter"
QT_MOC_LITERAL(19, 261, 10), // "activeMenu"
QT_MOC_LITERAL(20, 272, 2), // "id"
QT_MOC_LITERAL(21, 275, 19), // "outlineUpdateUnread"
QT_MOC_LITERAL(22, 295, 6), // "feedId"
QT_MOC_LITERAL(23, 302, 8), // "unreaded"
QT_MOC_LITERAL(24, 311, 4), // "type"
QT_MOC_LITERAL(25, 316, 16), // "updateTrayUnRead"
QT_MOC_LITERAL(26, 333, 23), // "outlineUpdateUnreadTray"
QT_MOC_LITERAL(27, 357, 23), // "manualNoAlarmNotifyTray"
QT_MOC_LITERAL(28, 381, 19), // "manualDeleteSession"
QT_MOC_LITERAL(29, 401, 16), // "reduceUnReadTray"
QT_MOC_LITERAL(30, 418, 29), // "manualModifySessionNameToTray"
QT_MOC_LITERAL(31, 448, 13), // "OnMessageSlot"
QT_MOC_LITERAL(32, 462, 18), // "messageListAdapter"
QT_MOC_LITERAL(33, 481, 14), // "showDetailArea"
QT_MOC_LITERAL(34, 496, 21), // "slotInitiateGroupChat"
QT_MOC_LITERAL(35, 518, 12), // "belongFeedId"
QT_MOC_LITERAL(36, 531, 11), // "groupChatId"
QT_MOC_LITERAL(37, 543, 31), // "slotCreateGroupChatFromMenuArea"
QT_MOC_LITERAL(38, 575, 20), // "on_NotifySendForward"
QT_MOC_LITERAL(39, 596, 27), // "QList<TNMessageListAdapter>"
QT_MOC_LITERAL(40, 624, 14), // "msgListAdapter"
QT_MOC_LITERAL(41, 639, 20), // "slotAppendSessionTop"
QT_MOC_LITERAL(42, 660, 14), // "messageAdapter"
QT_MOC_LITERAL(43, 675, 6), // "isSend"
QT_MOC_LITERAL(44, 682, 8), // "isActive"
QT_MOC_LITERAL(45, 691, 8), // "isOnLine"
QT_MOC_LITERAL(46, 700, 8), // "isBubble"
QT_MOC_LITERAL(47, 709, 20), // "slotRemoveSessionTop"
QT_MOC_LITERAL(48, 730, 19), // "slotReduceUnreadNum"
QT_MOC_LITERAL(49, 750, 6), // "number"
QT_MOC_LITERAL(50, 757, 17), // "onListAreaClicked"
QT_MOC_LITERAL(51, 775, 16), // "OnUnreadedUpdate"
QT_MOC_LITERAL(52, 792, 16), // "on_notifyRefresh"
QT_MOC_LITERAL(53, 809, 19), // "onUpdateSessionName"
QT_MOC_LITERAL(54, 829, 13), // "onManualOnTop"
QT_MOC_LITERAL(55, 843, 7), // "q_index"
QT_MOC_LITERAL(56, 851, 13), // "onManualNoTop"
QT_MOC_LITERAL(57, 865, 17), // "onModifyGroupName"
QT_MOC_LITERAL(58, 883, 18), // "onManualDelSession"
QT_MOC_LITERAL(59, 902, 15), // "onManualOnAlarm"
QT_MOC_LITERAL(60, 918, 15), // "onManualNoAlarm"
QT_MOC_LITERAL(61, 934, 10), // "slotSearch"
QT_MOC_LITERAL(62, 945, 7), // "content"
QT_MOC_LITERAL(63, 953, 17), // "searchClickedSlot"
QT_MOC_LITERAL(64, 971, 19), // "updateSessionActive"
QT_MOC_LITERAL(65, 991, 26), // "slotUpdateSessionUnreadNum"
QT_MOC_LITERAL(66, 1018, 3), // "num"
QT_MOC_LITERAL(67, 1022, 14), // "hideSearchArea"
QT_MOC_LITERAL(68, 1037, 17), // "slotRemoveSession"
QT_MOC_LITERAL(69, 1055, 19), // "slotUpOrDownSession"
QT_MOC_LITERAL(70, 1075, 8), // "upOrDown"
QT_MOC_LITERAL(71, 1084, 10), // "updateTime"
QT_MOC_LITERAL(72, 1095, 17), // "slotUpdateSession"
QT_MOC_LITERAL(73, 1113, 5), // "isAll"
QT_MOC_LITERAL(74, 1119, 16), // "initLocalSession"
QT_MOC_LITERAL(75, 1136, 23), // "onShowDefaultBackGround"
QT_MOC_LITERAL(76, 1160, 18), // "trayDoubleClickMsg"
QT_MOC_LITERAL(77, 1179, 19), // "slotCreateGroupChat"
QT_MOC_LITERAL(78, 1199, 20), // "on_notifyKeyEventDis"
QT_MOC_LITERAL(79, 1220, 8), // "keyEvent"
QT_MOC_LITERAL(80, 1229, 22), // "onUpdateSessionLastMsg"
QT_MOC_LITERAL(81, 1252, 25), // "onUpdateSessionListAvatar"
QT_MOC_LITERAL(82, 1278, 19), // "QList<UINotifyData>"
QT_MOC_LITERAL(83, 1298, 8), // "dataList"
QT_MOC_LITERAL(84, 1307, 7) // "isReady"

    },
    "NoticeListArea\0ListAreaClicked\0\0index\0"
    "ListAreaDoubleClicked\0messageNumberChanged\0"
    "count\0manualModifyGroupName\0sessionId\0"
    "name\0manualRemoveCurrentSession\0"
    "isSelected\0messageNotify\0TNMessageListAdapter\0"
    "adpter\0isNotice\0reLoadDetailsData\0"
    "TNMessageListAdapter*\0adapter\0activeMenu\0"
    "id\0outlineUpdateUnread\0feedId\0unreaded\0"
    "type\0updateTrayUnRead\0outlineUpdateUnreadTray\0"
    "manualNoAlarmNotifyTray\0manualDeleteSession\0"
    "reduceUnReadTray\0manualModifySessionNameToTray\0"
    "OnMessageSlot\0messageListAdapter\0"
    "showDetailArea\0slotInitiateGroupChat\0"
    "belongFeedId\0groupChatId\0"
    "slotCreateGroupChatFromMenuArea\0"
    "on_NotifySendForward\0QList<TNMessageListAdapter>\0"
    "msgListAdapter\0slotAppendSessionTop\0"
    "messageAdapter\0isSend\0isActive\0isOnLine\0"
    "isBubble\0slotRemoveSessionTop\0"
    "slotReduceUnreadNum\0number\0onListAreaClicked\0"
    "OnUnreadedUpdate\0on_notifyRefresh\0"
    "onUpdateSessionName\0onManualOnTop\0"
    "q_index\0onManualNoTop\0onModifyGroupName\0"
    "onManualDelSession\0onManualOnAlarm\0"
    "onManualNoAlarm\0slotSearch\0content\0"
    "searchClickedSlot\0updateSessionActive\0"
    "slotUpdateSessionUnreadNum\0num\0"
    "hideSearchArea\0slotRemoveSession\0"
    "slotUpOrDownSession\0upOrDown\0updateTime\0"
    "slotUpdateSession\0isAll\0initLocalSession\0"
    "onShowDefaultBackGround\0trayDoubleClickMsg\0"
    "slotCreateGroupChat\0on_notifyKeyEventDis\0"
    "keyEvent\0onUpdateSessionLastMsg\0"
    "onUpdateSessionListAvatar\0QList<UINotifyData>\0"
    "dataList\0isReady"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NoticeListArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      54,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  284,    2, 0x06 /* Public */,
       4,    1,  287,    2, 0x06 /* Public */,
       5,    1,  290,    2, 0x06 /* Public */,
       7,    2,  293,    2, 0x06 /* Public */,
      10,    2,  298,    2, 0x06 /* Public */,
      12,    2,  303,    2, 0x06 /* Public */,
      16,    1,  308,    2, 0x06 /* Public */,
      19,    1,  311,    2, 0x06 /* Public */,
      21,    3,  314,    2, 0x06 /* Public */,
      25,    1,  321,    2, 0x06 /* Public */,
      26,    2,  324,    2, 0x06 /* Public */,
      27,    3,  329,    2, 0x06 /* Public */,
      28,    1,  336,    2, 0x06 /* Public */,
      29,    2,  339,    2, 0x06 /* Public */,
      30,    2,  344,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      31,    2,  349,    2, 0x08 /* Private */,
      34,    2,  354,    2, 0x08 /* Private */,
      37,    1,  359,    2, 0x08 /* Private */,
      38,    1,  362,    2, 0x08 /* Private */,
      41,    6,  365,    2, 0x08 /* Private */,
      41,    5,  378,    2, 0x28 /* Private | MethodCloned */,
      41,    4,  389,    2, 0x28 /* Private | MethodCloned */,
      41,    3,  398,    2, 0x28 /* Private | MethodCloned */,
      41,    2,  405,    2, 0x28 /* Private | MethodCloned */,
      41,    1,  410,    2, 0x28 /* Private | MethodCloned */,
      47,    2,  413,    2, 0x08 /* Private */,
      48,    2,  418,    2, 0x08 /* Private */,
      50,    1,  423,    2, 0x08 /* Private */,
      51,    1,  426,    2, 0x08 /* Private */,
      52,    1,  429,    2, 0x08 /* Private */,
      53,    1,  432,    2, 0x08 /* Private */,
      54,    1,  435,    2, 0x08 /* Private */,
      56,    1,  438,    2, 0x08 /* Private */,
      57,    1,  441,    2, 0x08 /* Private */,
      58,    1,  444,    2, 0x08 /* Private */,
      59,    1,  447,    2, 0x08 /* Private */,
      60,    1,  450,    2, 0x08 /* Private */,
      61,    1,  453,    2, 0x08 /* Private */,
      63,    3,  456,    2, 0x08 /* Private */,
      64,    2,  463,    2, 0x08 /* Private */,
      65,    2,  468,    2, 0x08 /* Private */,
      67,    0,  473,    2, 0x08 /* Private */,
      68,    1,  474,    2, 0x08 /* Private */,
      68,    2,  477,    2, 0x08 /* Private */,
      69,    1,  482,    2, 0x08 /* Private */,
      71,    0,  485,    2, 0x08 /* Private */,
      72,    2,  486,    2, 0x08 /* Private */,
      74,    0,  491,    2, 0x08 /* Private */,
      75,    0,  492,    2, 0x08 /* Private */,
      76,    0,  493,    2, 0x08 /* Private */,
      77,    0,  494,    2, 0x08 /* Private */,
      78,    1,  495,    2, 0x08 /* Private */,
      80,    1,  498,    2, 0x08 /* Private */,
      81,    2,  501,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    8,   11,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Bool,   14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,   22,   23,   24,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 13, QMetaType::Bool,   32,   33,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   35,   36,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 39,   40,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   42,   11,   43,   44,   45,   46,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   42,   11,   43,   44,   45,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   42,   11,   43,   44,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Bool, QMetaType::Bool,   42,   11,   43,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Bool,   42,   11,
    QMetaType::Void, 0x80000000 | 13,   42,
    QMetaType::Void, 0x80000000 | 13, QMetaType::Bool,   42,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    8,   49,
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QModelIndex,   55,
    QMetaType::Void, QMetaType::QModelIndex,   55,
    QMetaType::Void, QMetaType::QModelIndex,   55,
    QMetaType::Void, QMetaType::QModelIndex,   55,
    QMetaType::Void, QMetaType::QModelIndex,   55,
    QMetaType::Void, QMetaType::QModelIndex,   55,
    QMetaType::Void, QMetaType::QString,   62,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Bool, QMetaType::QString, QMetaType::Bool,    8,   44,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,    8,   66,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    8,   11,
    QMetaType::Void, QMetaType::Bool,   70,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    8,   73,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   79,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, 0x80000000 | 82, QMetaType::Bool,   83,   84,

       0        // eod
};

void NoticeListArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NoticeListArea *_t = static_cast<NoticeListArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ListAreaClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->ListAreaDoubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->messageNumberChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->manualModifyGroupName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->manualRemoveCurrentSession((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->messageNotify((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->reLoadDetailsData((*reinterpret_cast< TNMessageListAdapter*(*)>(_a[1]))); break;
        case 7: _t->activeMenu((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->outlineUpdateUnread((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->updateTrayUnRead((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->outlineUpdateUnreadTray((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->manualNoAlarmNotifyTray((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: _t->manualDeleteSession((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->reduceUnReadTray((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->manualModifySessionNameToTray((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 15: _t->OnMessageSlot((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 16: _t->slotInitiateGroupChat((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 17: _t->slotCreateGroupChatFromMenuArea((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1]))); break;
        case 18: _t->on_NotifySendForward((*reinterpret_cast< QList<TNMessageListAdapter>(*)>(_a[1]))); break;
        case 19: _t->slotAppendSessionTop((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 20: _t->slotAppendSessionTop((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 21: _t->slotAppendSessionTop((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 22: _t->slotAppendSessionTop((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 23: _t->slotAppendSessionTop((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 24: _t->slotAppendSessionTop((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1]))); break;
        case 25: _t->slotRemoveSessionTop((*reinterpret_cast< TNMessageListAdapter(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 26: _t->slotReduceUnreadNum((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 27: _t->onListAreaClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 28: _t->OnUnreadedUpdate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 29: _t->on_notifyRefresh((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 30: _t->onUpdateSessionName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 31: _t->onManualOnTop((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 32: _t->onManualNoTop((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 33: _t->onModifyGroupName((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 34: _t->onManualDelSession((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 35: _t->onManualOnAlarm((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 36: _t->onManualNoAlarm((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 37: _t->slotSearch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 38: _t->searchClickedSlot((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 39: { bool _r = _t->updateSessionActive((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 40: { bool _r = _t->slotUpdateSessionUnreadNum((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 41: _t->hideSearchArea(); break;
        case 42: { bool _r = _t->slotRemoveSession((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 43: _t->slotRemoveSession((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 44: _t->slotUpOrDownSession((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 45: _t->updateTime(); break;
        case 46: _t->slotUpdateSession((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 47: _t->initLocalSession(); break;
        case 48: _t->onShowDefaultBackGround(); break;
        case 49: _t->trayDoubleClickMsg(); break;
        case 50: _t->slotCreateGroupChat(); break;
        case 51: _t->on_notifyKeyEventDis((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->onUpdateSessionLastMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 53: _t->onUpdateSessionListAvatar((*reinterpret_cast< QList<UINotifyData>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NoticeListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::ListAreaClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::ListAreaDoubleClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::messageNumberChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::manualModifyGroupName)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(const QString & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::manualRemoveCurrentSession)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(TNMessageListAdapter , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::messageNotify)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(TNMessageListAdapter * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::reLoadDetailsData)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::activeMenu)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(const QString & , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::outlineUpdateUnread)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::updateTrayUnRead)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(TNMessageListAdapter , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::outlineUpdateUnreadTray)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(const QString & , bool , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::manualNoAlarmNotifyTray)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::manualDeleteSession)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::reduceUnReadTray)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (NoticeListArea::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NoticeListArea::manualModifySessionNameToTray)) {
                *result = 14;
                return;
            }
        }
    }
}

const QMetaObject NoticeListArea::staticMetaObject = {
    { &ListAreaBase::staticMetaObject, qt_meta_stringdata_NoticeListArea.data,
      qt_meta_data_NoticeListArea,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NoticeListArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NoticeListArea::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NoticeListArea.stringdata0))
        return static_cast<void*>(const_cast< NoticeListArea*>(this));
    return ListAreaBase::qt_metacast(_clname);
}

int NoticeListArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ListAreaBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 54)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 54;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 54)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 54;
    }
    return _id;
}

// SIGNAL 0
void NoticeListArea::ListAreaClicked(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NoticeListArea::ListAreaDoubleClicked(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NoticeListArea::messageNumberChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NoticeListArea::manualModifyGroupName(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void NoticeListArea::manualRemoveCurrentSession(const QString & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void NoticeListArea::messageNotify(TNMessageListAdapter _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void NoticeListArea::reLoadDetailsData(TNMessageListAdapter * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void NoticeListArea::activeMenu(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void NoticeListArea::outlineUpdateUnread(const QString & _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void NoticeListArea::updateTrayUnRead(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void NoticeListArea::outlineUpdateUnreadTray(TNMessageListAdapter _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void NoticeListArea::manualNoAlarmNotifyTray(const QString & _t1, bool _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void NoticeListArea::manualDeleteSession(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void NoticeListArea::reduceUnReadTray(const QString & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void NoticeListArea::manualModifySessionNameToTray(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_END_MOC_NAMESPACE
