#ifndef NOTICELISTDELEGATE_H
#define NOTICELISTDELEGATE_H
#include <QStyledItemDelegate>
#include <QFont>
#include <QMenu>
#include "TNMessageListAdapter.h"

class NoticeListDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    NoticeListDelegate(QObject* parent=NULL);
    ~NoticeListDelegate();
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option,
        const QModelIndex &index) const;
    virtual bool helpEvent(QHelpEvent *event, QAbstractItemView *view,
        const QStyleOptionViewItem &option, const QModelIndex &index);
    void setFocuseIn(bool flag);
public slots:
    void onDownLoadAvator(const TNMessageListAdapter& adapter) const;
Q_SIGNALS:
    void downLoadAvator(const TNMessageListAdapter& adapter) const;
private:
    void paint_avator_button(QPainter* painter,const QStyleOptionViewItem &option,
        const QModelIndex &index, const TNMessageListAdapter& adapter) const ;
    void paint_item_state(QPainter* painter,const QStyleOptionViewItem &option,
        const QModelIndex &index, const TNMessageListAdapter& adapter) const;
    void paint_item_title(QPainter* painter,const QStyleOptionViewItem &option,
        const QModelIndex &index, const TNMessageListAdapter& adapter) const;
    QPoint paint_item_time(QPainter* painter,const QStyleOptionViewItem &option,
        const QModelIndex &index, const TNMessageListAdapter& adapter) const;
    void paint_sub_title(QPainter* painter,const QStyleOptionViewItem &option,
        const QModelIndex &index, const TNMessageListAdapter& adapter) const;
    QPoint paint_sub_alarm(QPainter* painter,const QStyleOptionViewItem &option,
        const QModelIndex &index, const TNMessageListAdapter& adapter) const;
    void paint_unread_num(QPainter* painter,const QStyleOptionViewItem &option,
        const QModelIndex &index, const TNMessageListAdapter& adapter) const;
    void paint_on_top(QPainter* painter,const QStyleOptionViewItem &option,
        const QModelIndex &index,const TNMessageListAdapter& adapter) const;
private:
    int 	_avator_margn_left;
    int     _avator_margn_right;
    int 	_avator_margn_top;
    int     _avator_margn_bottom;
    int 	_avator_width;
    int 	_avator_height;
    int 	_title_margn_left;
    int 	_title_margn_top;
    int 	_time_margn_right;//时间显示控件距右边
    int     _time_margn_top;//时间控件距top
    int 	_time_title_margn;//title和时间的间距
    QFont   _big_title_font;
    QFont	_small_title_font;
    //title paint完后的rect
    mutable QRect	_title_auto_rect;
    //subtitle控件
    int 	_subctr_left;
    //alarm控件
    int 	_alarm_margn_right;
    int 	_alarm_width;
    int 	_alarm_height;
    //title and subtitle space_height
    int 	_title_subtitle_space;
    //头像的rect
    mutable QRect _avatar_rect;
    //未读条数
    QColor  _count_color;
    QColor  _count_brush_color;
    QFont   _count_font;
    int 	_count_height;
    int 	_count_round_width;
    //小字体的颜色
    QColor  _small_color;
    //置顶的图标
    QSize	_on_top_size;
    int 	_on_top_margn_left;
    int 	_on_top_margn_top;
    //草稿文字color
    QColor 	_draft_color;

    bool 	_focuseIn = true;
};

#endif // NOTICELISTDELEGATE_H
