/****************************************************************************
** Meta object code from reading C++ file 'CardCaseListArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CardCaseListArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CardCaseListArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CardCaseListArea_t {
    QByteArrayData data[64];
    char stringdata0[1078];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CardCaseListArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CardCaseListArea_t qt_meta_stringdata_CardCaseListArea = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CardCaseListArea"
QT_MOC_LITERAL(1, 17, 20), // "clickedNewFriendItem"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 19), // "updateNewFriendPage"
QT_MOC_LITERAL(4, 59, 20), // "messageNumberChanged"
QT_MOC_LITERAL(5, 80, 5), // "count"
QT_MOC_LITERAL(6, 86, 15), // "ListAreaClicked"
QT_MOC_LITERAL(7, 102, 5), // "index"
QT_MOC_LITERAL(8, 108, 24), // "ColleagueListAreaClicked"
QT_MOC_LITERAL(9, 133, 20), // "GroupListAreaClicked"
QT_MOC_LITERAL(10, 154, 24), // "GroupChatListAreaClicked"
QT_MOC_LITERAL(11, 179, 21), // "ListAreaDoubleClicked"
QT_MOC_LITERAL(12, 201, 23), // "ListFriendToDetailEvent"
QT_MOC_LITERAL(13, 225, 26), // "ListColleagueToDetailEvent"
QT_MOC_LITERAL(14, 252, 22), // "ListGroupToDetailEvent"
QT_MOC_LITERAL(15, 275, 26), // "ListGroupChatToDetailEvent"
QT_MOC_LITERAL(16, 302, 24), // "ListGroupChatModifyEvent"
QT_MOC_LITERAL(17, 327, 20), // "CloseDetailPageEvent"
QT_MOC_LITERAL(18, 348, 6), // "feedId"
QT_MOC_LITERAL(19, 355, 8), // "belongId"
QT_MOC_LITERAL(20, 364, 19), // "SearchClickedSignal"
QT_MOC_LITERAL(21, 384, 4), // "type"
QT_MOC_LITERAL(22, 389, 26), // "UpdateColleagueCacheSignal"
QT_MOC_LITERAL(23, 416, 31), // "UpdateOrgGroupAndRelationSignal"
QT_MOC_LITERAL(24, 448, 26), // "RemoveSessionInSessionList"
QT_MOC_LITERAL(25, 475, 18), // "UpdateFriendReMark"
QT_MOC_LITERAL(26, 494, 17), // "notifySessionList"
QT_MOC_LITERAL(27, 512, 19), // "QList<UINotifyData>"
QT_MOC_LITERAL(28, 532, 8), // "dataList"
QT_MOC_LITERAL(29, 541, 7), // "isReady"
QT_MOC_LITERAL(30, 549, 18), // "OnButtonFriendSlot"
QT_MOC_LITERAL(31, 568, 16), // "on_notifyRefresh"
QT_MOC_LITERAL(32, 585, 20), // "refreshNewFriendPage"
QT_MOC_LITERAL(33, 606, 21), // "OnListAreaClickedSlot"
QT_MOC_LITERAL(34, 628, 23), // "OnColleagueListAreaSlot"
QT_MOC_LITERAL(35, 652, 19), // "OnGroupListAreaSlot"
QT_MOC_LITERAL(36, 672, 23), // "OnGroupChatListAreaSlot"
QT_MOC_LITERAL(37, 696, 27), // "on_notifyCurrentFeedChanged"
QT_MOC_LITERAL(38, 724, 6), // "feedID"
QT_MOC_LITERAL(39, 731, 20), // "needToDownLoadAvatar"
QT_MOC_LITERAL(40, 752, 3), // "url"
QT_MOC_LITERAL(41, 756, 21), // "on_notifyReMarkUpdate"
QT_MOC_LITERAL(42, 778, 20), // "on_notifyKeyEventDis"
QT_MOC_LITERAL(43, 799, 8), // "keyEvent"
QT_MOC_LITERAL(44, 808, 24), // "feedCardUpdateFromCatche"
QT_MOC_LITERAL(45, 833, 8), // "avatarId"
QT_MOC_LITERAL(46, 842, 4), // "name"
QT_MOC_LITERAL(47, 847, 7), // "subName"
QT_MOC_LITERAL(48, 855, 6), // "userId"
QT_MOC_LITERAL(49, 862, 6), // "namePy"
QT_MOC_LITERAL(50, 869, 10), // "sourceType"
QT_MOC_LITERAL(51, 880, 21), // "OnButtonColleagueSlot"
QT_MOC_LITERAL(52, 902, 21), // "OnButtonGroupChatSlot"
QT_MOC_LITERAL(53, 924, 17), // "OnButtonGroupSlot"
QT_MOC_LITERAL(54, 942, 10), // "slotSearch"
QT_MOC_LITERAL(55, 953, 4), // "text"
QT_MOC_LITERAL(56, 958, 22), // "onAvatarDownLoadFinish"
QT_MOC_LITERAL(57, 981, 7), // "success"
QT_MOC_LITERAL(58, 989, 17), // "SearchClickedSlot"
QT_MOC_LITERAL(59, 1007, 23), // "setCODepartItemExpanded"
QT_MOC_LITERAL(60, 1031, 14), // "hideSearchArea"
QT_MOC_LITERAL(61, 1046, 6), // "status"
QT_MOC_LITERAL(62, 1053, 19), // "currentSelectedPage"
QT_MOC_LITERAL(63, 1073, 4) // "page"

    },
    "CardCaseListArea\0clickedNewFriendItem\0"
    "\0updateNewFriendPage\0messageNumberChanged\0"
    "count\0ListAreaClicked\0index\0"
    "ColleagueListAreaClicked\0GroupListAreaClicked\0"
    "GroupChatListAreaClicked\0ListAreaDoubleClicked\0"
    "ListFriendToDetailEvent\0"
    "ListColleagueToDetailEvent\0"
    "ListGroupToDetailEvent\0"
    "ListGroupChatToDetailEvent\0"
    "ListGroupChatModifyEvent\0CloseDetailPageEvent\0"
    "feedId\0belongId\0SearchClickedSignal\0"
    "type\0UpdateColleagueCacheSignal\0"
    "UpdateOrgGroupAndRelationSignal\0"
    "RemoveSessionInSessionList\0"
    "UpdateFriendReMark\0notifySessionList\0"
    "QList<UINotifyData>\0dataList\0isReady\0"
    "OnButtonFriendSlot\0on_notifyRefresh\0"
    "refreshNewFriendPage\0OnListAreaClickedSlot\0"
    "OnColleagueListAreaSlot\0OnGroupListAreaSlot\0"
    "OnGroupChatListAreaSlot\0"
    "on_notifyCurrentFeedChanged\0feedID\0"
    "needToDownLoadAvatar\0url\0on_notifyReMarkUpdate\0"
    "on_notifyKeyEventDis\0keyEvent\0"
    "feedCardUpdateFromCatche\0avatarId\0"
    "name\0subName\0userId\0namePy\0sourceType\0"
    "OnButtonColleagueSlot\0OnButtonGroupChatSlot\0"
    "OnButtonGroupSlot\0slotSearch\0text\0"
    "onAvatarDownLoadFinish\0success\0"
    "SearchClickedSlot\0setCODepartItemExpanded\0"
    "hideSearchArea\0status\0currentSelectedPage\0"
    "page"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CardCaseListArea[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      20,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  219,    2, 0x06 /* Public */,
       3,    0,  220,    2, 0x06 /* Public */,
       4,    1,  221,    2, 0x06 /* Public */,
       6,    1,  224,    2, 0x06 /* Public */,
       8,    1,  227,    2, 0x06 /* Public */,
       9,    1,  230,    2, 0x06 /* Public */,
      10,    1,  233,    2, 0x06 /* Public */,
      11,    1,  236,    2, 0x06 /* Public */,
      12,    1,  239,    2, 0x06 /* Public */,
      13,    1,  242,    2, 0x06 /* Public */,
      14,    1,  245,    2, 0x06 /* Public */,
      15,    1,  248,    2, 0x06 /* Public */,
      16,    1,  251,    2, 0x06 /* Public */,
      17,    2,  254,    2, 0x06 /* Public */,
      20,    2,  259,    2, 0x06 /* Public */,
      22,    0,  264,    2, 0x06 /* Public */,
      23,    0,  265,    2, 0x06 /* Public */,
      24,    1,  266,    2, 0x06 /* Public */,
      25,    2,  269,    2, 0x06 /* Public */,
      26,    2,  274,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      30,    0,  279,    2, 0x0a /* Public */,
      31,    2,  280,    2, 0x0a /* Public */,
      32,    0,  285,    2, 0x0a /* Public */,
      33,    1,  286,    2, 0x0a /* Public */,
      34,    1,  289,    2, 0x0a /* Public */,
      35,    1,  292,    2, 0x0a /* Public */,
      36,    1,  295,    2, 0x0a /* Public */,
      37,    1,  298,    2, 0x0a /* Public */,
      39,    3,  301,    2, 0x0a /* Public */,
      41,    4,  308,    2, 0x0a /* Public */,
      42,    1,  317,    2, 0x0a /* Public */,
      44,    7,  320,    2, 0x0a /* Public */,
      51,    0,  335,    2, 0x08 /* Private */,
      52,    0,  336,    2, 0x08 /* Private */,
      53,    0,  337,    2, 0x08 /* Private */,
      54,    1,  338,    2, 0x08 /* Private */,
      56,    3,  341,    2, 0x08 /* Private */,
      58,    3,  348,    2, 0x08 /* Private */,
      59,    1,  355,    2, 0x08 /* Private */,
      60,    1,  358,    2, 0x0a /* Public */,
      62,    1,  361,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   18,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::QModelIndex,   21,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 27, QMetaType::Bool,   28,   29,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 27,   21,   28,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QString,   38,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,   18,   40,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,   43,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,   18,   45,   46,   47,   48,   49,   50,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   55,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,   57,   40,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Int,   63,

       0        // eod
};

void CardCaseListArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CardCaseListArea *_t = static_cast<CardCaseListArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clickedNewFriendItem(); break;
        case 1: _t->updateNewFriendPage(); break;
        case 2: _t->messageNumberChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->ListAreaClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->ColleagueListAreaClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->GroupListAreaClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->GroupChatListAreaClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 7: _t->ListAreaDoubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 8: _t->ListFriendToDetailEvent((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 9: _t->ListColleagueToDetailEvent((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 10: _t->ListGroupToDetailEvent((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 11: _t->ListGroupChatToDetailEvent((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 12: _t->ListGroupChatModifyEvent((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 13: _t->CloseDetailPageEvent((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 14: _t->SearchClickedSignal((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 15: _t->UpdateColleagueCacheSignal(); break;
        case 16: _t->UpdateOrgGroupAndRelationSignal(); break;
        case 17: _t->RemoveSessionInSessionList((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->UpdateFriendReMark((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 19: _t->notifySessionList((*reinterpret_cast< QList<UINotifyData>(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 20: _t->OnButtonFriendSlot(); break;
        case 21: _t->on_notifyRefresh((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QList<UINotifyData>(*)>(_a[2]))); break;
        case 22: _t->refreshNewFriendPage(); break;
        case 23: _t->OnListAreaClickedSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 24: _t->OnColleagueListAreaSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 25: _t->OnGroupListAreaSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 26: _t->OnGroupChatListAreaSlot((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 27: _t->on_notifyCurrentFeedChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 28: _t->needToDownLoadAvatar((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 29: _t->on_notifyReMarkUpdate((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 30: _t->on_notifyKeyEventDis((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->feedCardUpdateFromCatche((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7]))); break;
        case 32: _t->OnButtonColleagueSlot(); break;
        case 33: _t->OnButtonGroupChatSlot(); break;
        case 34: _t->OnButtonGroupSlot(); break;
        case 35: _t->slotSearch((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 36: _t->onAvatarDownLoadFinish((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 37: _t->SearchClickedSlot((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 38: _t->setCODepartItemExpanded((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 39: _t->hideSearchArea((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: _t->currentSelectedPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CardCaseListArea::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::clickedNewFriendItem)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::updateNewFriendPage)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::messageNumberChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::ListAreaClicked)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::ColleagueListAreaClicked)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::GroupListAreaClicked)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::GroupChatListAreaClicked)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::ListAreaDoubleClicked)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::ListFriendToDetailEvent)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::ListColleagueToDetailEvent)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::ListGroupToDetailEvent)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::ListGroupChatToDetailEvent)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::ListGroupChatModifyEvent)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::CloseDetailPageEvent)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QString & , const QModelIndex & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::SearchClickedSignal)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::UpdateColleagueCacheSignal)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::UpdateOrgGroupAndRelationSignal)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::RemoveSessionInSessionList)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::UpdateFriendReMark)) {
                *result = 18;
                return;
            }
        }
        {
            typedef void (CardCaseListArea::*_t)(QList<UINotifyData> , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CardCaseListArea::notifySessionList)) {
                *result = 19;
                return;
            }
        }
    }
}

const QMetaObject CardCaseListArea::staticMetaObject = {
    { &ListAreaBase::staticMetaObject, qt_meta_stringdata_CardCaseListArea.data,
      qt_meta_data_CardCaseListArea,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CardCaseListArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CardCaseListArea::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CardCaseListArea.stringdata0))
        return static_cast<void*>(const_cast< CardCaseListArea*>(this));
    return ListAreaBase::qt_metacast(_clname);
}

int CardCaseListArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ListAreaBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 41)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 41;
    }
    return _id;
}

// SIGNAL 0
void CardCaseListArea::clickedNewFriendItem()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void CardCaseListArea::updateNewFriendPage()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void CardCaseListArea::messageNumberChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CardCaseListArea::ListAreaClicked(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CardCaseListArea::ColleagueListAreaClicked(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CardCaseListArea::GroupListAreaClicked(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CardCaseListArea::GroupChatListAreaClicked(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CardCaseListArea::ListAreaDoubleClicked(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CardCaseListArea::ListFriendToDetailEvent(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CardCaseListArea::ListColleagueToDetailEvent(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void CardCaseListArea::ListGroupToDetailEvent(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void CardCaseListArea::ListGroupChatToDetailEvent(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void CardCaseListArea::ListGroupChatModifyEvent(const QModelIndex & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void CardCaseListArea::CloseDetailPageEvent(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void CardCaseListArea::SearchClickedSignal(const QString & _t1, const QModelIndex & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void CardCaseListArea::UpdateColleagueCacheSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 15, Q_NULLPTR);
}

// SIGNAL 16
void CardCaseListArea::UpdateOrgGroupAndRelationSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 16, Q_NULLPTR);
}

// SIGNAL 17
void CardCaseListArea::RemoveSessionInSessionList(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void CardCaseListArea::UpdateFriendReMark(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void CardCaseListArea::notifySessionList(QList<UINotifyData> _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}
QT_END_MOC_NAMESPACE
