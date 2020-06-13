#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QHelpEvent>
#include <QCursor>
#include <QPoint>
#include "noticelistdelegate.h"
#include "TNMessageListAdapter.h"
#include "TNSettingData.h"
#include "tncommondealavator.h"
#include "TNConfig.h"
#include "NoticeEnum.h"
#include "draft/deal_draft_data.h"
#include "tnsendimsg.h"

NoticeListDelegate::NoticeListDelegate(QObject* parent) : QStyledItemDelegate(parent)
  ,_avator_margn_left(15)
  ,_avator_margn_right(0)
  ,_avator_margn_top(15)
  ,_avator_margn_bottom(15)
  ,_avator_width(40)
  ,_avator_height(40)
  ,_title_margn_left(_avator_margn_left + _avator_margn_right + _avator_width + 10)
  ,_title_margn_top(26)
  ,_time_margn_right(15)
  ,_time_margn_top(26)
  ,_time_title_margn(10)
  ,_subctr_left(_avator_margn_left + _avator_margn_right + _avator_width + 10)
  ,_alarm_margn_right(15)
  ,_alarm_width(14)
  ,_alarm_height(14)
  ,_title_subtitle_space(6)
  ,_count_color(QColor(0xff,0xff,0xff))
  ,_count_brush_color(QColor(0xff,0x74,0x46))
  ,_count_height(16)
  ,_count_round_width(26)
  ,_small_color(QColor(0x858fa4))
  ,_on_top_size(QSize(6,6))
  ,_on_top_margn_left(8)
  ,_on_top_margn_top(8)
  ,_draft_color(qRgb(255,0,0))
{
    _big_title_font = QFont("Microsoft Yahei");
    _big_title_font.setPixelSize(14);

    _small_title_font = QFont("Microsoft Yahei");
    _small_title_font.setPixelSize(12);

    _count_font = QFont("Microsoft Yahei");
    _count_font.setPixelSize(10);

    qRegisterMetaType<TNMessageListAdapter>("TNMessageListAdapter");
    connect(this,SIGNAL(downLoadAvator(const TNMessageListAdapter&)),
            this,SLOT(onDownLoadAvator(const TNMessageListAdapter&)),Qt::QueuedConnection);
}

NoticeListDelegate::~NoticeListDelegate()
{
}

void NoticeListDelegate::paint(QPainter *painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
    if(!index.isValid()) return;
    TNMessageListAdapter* adapter = (TNMessageListAdapter*)index.data().toLongLong();
    if(adapter == NULL){
        return;
    }
    if(index.column() != 0){
        return;
    }
    Q_ASSERT(adapter);
    TNMessageListAdapter session = *adapter;
    paint_item_state(painter,option,index,session);
    paint_avator_button(painter,option,index,session);
    paint_item_title(painter,option,index,session);
    paint_sub_title(painter,option,index,session);
    paint_unread_num(painter,option,index,session);
    paint_on_top(painter,option,index,session);
}

QSize NoticeListDelegate::sizeHint(const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    return QSize(LIST_AREA_WIDTH,LIST_AREA_WIDTH);
}


bool NoticeListDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index)
{
    return QStyledItemDelegate::helpEvent(event,view,option,index);
}

void NoticeListDelegate::paint_item_state(QPainter *painter,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index,
                                          const TNMessageListAdapter& adapter) const
{
    if(!index.isValid()) return;
    if(adapter.getBackStatus() == TNMessageListAdapter::em_notice_list_select){
        painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentSelectSkin()));
    }else if(adapter.getBackStatus() == TNMessageListAdapter::em_notice_list_hover){
        painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentHoverSkin()));
    }else if(option.state & QStyle::State_MouseOver && _focuseIn){
        painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentHoverSkin()));
    }
}

void NoticeListDelegate::paint_avator_button(QPainter *painter,
                                             const QStyleOptionViewItem &option,
                                             const QModelIndex &index,
                                             const TNMessageListAdapter& adapter)const
{
    if(!index.isValid()) return;
    QString avatarPath = adapter.getPhotoResID();
    if(avatarPath.isEmpty() || !QFile::exists(avatarPath)){
        avatarPath = (":/Resources/toolWidget/defaultAvatar.png");
        //下载头像
        TNMessageListAdapter session = adapter;
        emit downLoadAvator(session);
    }
    painter->save();
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    Cust_Type cust_type;
    if (adapter.getToFeed().startsWith("c_")){
        cust_type = Cust_Type::cust_ellipse;
    }else if(adapter.getSessionId().startsWith("gc_")){
        cust_type = Cust_Type::cust_radius;
    }else{
		cust_type = Cust_Type::cust_radius;
    }
    QPixmap pix_avatar = TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), cust_type);
    pix_avatar.scaled(_avator_width,_avator_height,Qt::KeepAspectRatio);
    QRect op_rect = option.rect;
    _avatar_rect = QRect(
        op_rect.left() + _avator_margn_left,
        op_rect.top() + _avator_margn_top,
        _avator_width,
        _avator_height);
    painter->drawPixmap(_avatar_rect,pix_avatar);
    painter->restore();
    Q_UNUSED(option);
}

void NoticeListDelegate::paint_item_title(QPainter *painter,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index,
                                         const TNMessageListAdapter& adapter) const
{
    if(!index.isValid()) return;
    QString title = adapter.getName();
    if(!adapter.getRemark().isEmpty()){
        title = adapter.getRemark();
    }
    QFont old_font = painter->font();
    //计算title可显示的宽度
    QPoint time_star_point = paint_item_time(painter,option,index,adapter);
    int title_width = time_star_point.x() - _title_margn_left - _time_title_margn;
    painter->setFont(_big_title_font);
    title = DealDraftData::delAllSpecialChar(title);
    title = painter->fontMetrics().elidedText(title, Qt::ElideRight,
                                              title_width, Qt::TextShowMnemonic);
    QRect auto_rect = painter->fontMetrics().boundingRect(title);
    QRect op_rect = option.rect;
    _title_auto_rect = QRect(
                op_rect.left() + _title_margn_left,
                op_rect.top() + _title_margn_top,
                auto_rect.width(),
                auto_rect.height());
    painter->drawText(op_rect.left() + _title_margn_left,
                      op_rect.top() + _title_margn_top,title);
    painter->setFont(old_font);
}

QPoint NoticeListDelegate::paint_item_time(QPainter *painter,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index,
                                         const TNMessageListAdapter& adapter) const
{
    if(!index.isValid()) return QPoint();
    QFont old_font = painter->font();
    QRect view_rect = option.rect;
    int time_end_right = view_rect.right() - _time_margn_right;
    //计算字符串的物理长度
    painter->setFont(_small_title_font);
    QPen old_pen = painter->pen();
    QPen pen;
    pen.setColor(_small_color);
    painter->setPen(pen);

    QFontMetrics font_met(_small_title_font);
    qint64 time = adapter.getTime();
    QDateTime dtTime = QDateTime::fromMSecsSinceEpoch(time * 1000);
    QDate currDate = QDateTime::currentDateTime().date();
    QString s_time;
    if (dtTime.date() == currDate){
        s_time = dtTime.toString("hh:mm");
    }
    else if (currDate.year() - dtTime.date().year() > 1){
        s_time = dtTime.toString("yyyy-MM-dd");
    }
    else if (currDate.daysTo(dtTime.date()) == -1){//昨天
        s_time = ("昨天");
    }
    else if (currDate.daysTo(dtTime.date()) <= -2){
        s_time = dtTime.toString("MM-dd");
    }

    int time_start_left = time_end_right - font_met.boundingRect(s_time).width();
    int time_start_top = view_rect.top() + _time_margn_top;
    painter->drawText(time_start_left,time_start_top,s_time);
    painter->setFont(old_font);
    painter->setPen(old_pen);

    return QPoint(time_start_left,time_start_top);
}

void NoticeListDelegate::paint_sub_title(QPainter *painter,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index,
                                         const TNMessageListAdapter& adapter) const
{
    if(!index.isValid()) return;
    //得到no_alarm控件的开始位置
    QPoint sub_title_end = paint_sub_alarm(painter,option,index,adapter);

    QString sub_title = adapter.getLastMessage();
    QRect op_rect = option.rect;
    QFont old_font = painter->font();
    QPen old_pen = painter->pen();
    QPen pen;
    int pre_content_width = 0;
    //有人@我,优先绘制@
    if(adapter.getIsAtMe()){
        QString pre_at = tr(AT_YOU_SUCCESS);
        pen.setColor(QColor(TNSettingData::instance()->GetCurrentThemeSkin()));
        painter->setPen(pen);
        painter->setFont(_small_title_font);
        QRect pre_at_rect = painter->fontMetrics().boundingRect(pre_at);
        pre_content_width = pre_at_rect.width() + 2;
        painter->drawText(op_rect.left() + _subctr_left,sub_title_end.y(),pre_at);
        sub_title = adapter.getLastMessage();
        goto custom_paint;
    }
    //////////////////////////////
    if(!adapter.getDraft().isEmpty() && adapter.getBackStatus() != TNMessageListAdapter::em_notice_list_select){
        QString pre_draft = ("[草稿]:");
        //画前缀草稿
        pen.setColor(_draft_color);
        painter->setPen(pen);
        painter->setFont(_small_title_font);
        QRect pre_draft_rect = painter->fontMetrics().boundingRect(pre_draft);
        pre_content_width = pre_draft_rect.width() + 2;
        painter->drawText(op_rect.left() + _subctr_left,sub_title_end.y(),pre_draft);
        sub_title = adapter.getDraft();
        sub_title = DealDraftData::convertAtToPlainText(sub_title);
        if(sub_title.size() > 100)
            sub_title = sub_title.left(100);
    }
custom_paint:
    painter->setFont(_small_title_font);
    pen.setColor(_small_color);
    painter->setPen(pen);
    int sub_title_width = sub_title_end.x() - _subctr_left - pre_content_width;
    sub_title = DealDraftData::delAllSpecialChar(sub_title);
    sub_title = painter->fontMetrics().elidedText(sub_title, Qt::ElideRight,
                                              sub_title_width, Qt::TextShowMnemonic);
    painter->drawText(op_rect.left() + _subctr_left + pre_content_width,sub_title_end.y(),sub_title);
    painter->setFont(old_font);
    painter->setPen(old_pen);
}

QPoint NoticeListDelegate::paint_sub_alarm(QPainter *painter,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index,
                                           const TNMessageListAdapter& adapter) const
{
    if(!index.isValid()) return QPoint();
    QRect view_rect = option.rect;
    int alarm_end_right = view_rect.right() - _alarm_margn_right;
    int alarm_start_top = _title_auto_rect.bottom() + _title_subtitle_space;
    if(adapter.getNoAlarm()){
        int alarm_start_left = alarm_end_right - _alarm_width;
        QPixmap im;
        if (im.load(":/Resources/toolWidget/no_alarm.png")){
            QRect rect = QRect(alarm_start_left,alarm_start_top - _alarm_height,_alarm_width,_alarm_height);
            painter->drawPixmap(rect,im);
        }
        return QPoint(alarm_start_left,alarm_start_top);
    }
    return QPoint(alarm_end_right,alarm_start_top);
}

void NoticeListDelegate::paint_unread_num(QPainter *painter,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index,
                                          const TNMessageListAdapter& adapter) const
{
    Q_UNUSED(option);
    if(!index.isValid()) return;
    int count = adapter.getUnreadCount();
    if(count <= 0){
        return;
    }
    QString s_count;
    if(count > 99){
        s_count = ("99+");
    }else{
        s_count = QString("%1").arg(count);
    }
    QPen pen(_count_color);
    QBrush brush(_count_brush_color);
    QFont old_font = painter->font();
    QPen old_pen = painter->pen();
    painter->setFont(_count_font);

    QRect decoration = QRect(_avatar_rect.right() - _count_height / 2,
                 _avatar_rect.top() - _count_height / 2,
                 _count_height,
                 _count_height);

    painter->setRenderHint(QPainter::Antialiasing,true);
    if(!adapter.getNoAlarm()){
        painter->setPen(pen);
        QPainterPath path;
        if(count > 99){
            decoration.setLeft(decoration.left() - 5);
            decoration.setWidth(_count_round_width);
            path.addRoundedRect(decoration, _count_height / 2, _count_height / 2);
        }else{
            path.addRoundedRect(decoration,_count_height / 2,_count_height / 2);
        }
        painter->fillPath(path, brush);
        painter->drawText(decoration, Qt::AlignCenter | Qt::AlignVCenter, s_count);
    }else{
        decoration = QRect(_avatar_rect.right() - 10 / 2,
                           _avatar_rect.top() - 10 / 2,
                           10,
                           10);
        painter->setPen(pen);
        QPainterPath path;
        path.addRoundedRect(decoration, 10 / 2, 10 / 2);
        painter->fillPath(path,brush);
    }
    painter->setFont(old_font);
    painter->setPen(old_pen);
    painter->setRenderHint(QPainter::Antialiasing,false);
}

void NoticeListDelegate::paint_on_top(QPainter *painter,
    const QStyleOptionViewItem &option,
    const QModelIndex &index,
    const TNMessageListAdapter& adapter) const
{
    if(!index.isValid()) return;
    QRect item_rect = option.rect;
    if(adapter.getTopStatus() > 0){//置顶
        QPixmap im;
        if (im.load(":/Resources/toolWidget/on_top.png")){
            QRect rect(item_rect.left() + _on_top_margn_left,
                       item_rect.top() + _on_top_margn_top,
                       _on_top_size.width(),
                       _on_top_size.height());
            painter->drawPixmap(rect,im);
        }
    }
    Q_UNUSED(index);
}

void NoticeListDelegate::setFocuseIn(bool flag)
{
    _focuseIn = flag;
}

void NoticeListDelegate::onDownLoadAvator(const TNMessageListAdapter& adapter) const
{
    TNSendIMsg::getInstance()->downLoadAvator(adapter);
}
