#include "TNHomePageTreeItemDelegate.h"

#include <QPainter>
#include <QHelpEvent>
#include <QApplication>
#include <QToolTip>
#include <QDebug>

#include "TNSettingData.h"

TNHomePageTreeItemDelegate::TNHomePageTreeItemDelegate()
    : m_pButton(new QPushButton())
{
    tagFont = QFont("Microsoft Yahei");
    tagFont.setPixelSize(14);
    m_selectedItemIds = qMakePair(-1, -1);
}

TNHomePageTreeItemDelegate::~TNHomePageTreeItemDelegate()
{

}

void TNHomePageTreeItemDelegate::setSelectItemId(const QPair<int, int> &selectedItemIds)
{
    m_selectedItemIds = selectedItemIds;
}

void TNHomePageTreeItemDelegate::setButtonStatus(const QModelIndex &index, bool expanded)
{
    m_buttonStausMap[index] = expanded;
}

void TNHomePageTreeItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    TNHomePageTreeItem *item = static_cast<TNHomePageTreeItem*>(index.internalPointer());
    Q_ASSERT(item);
    if (item == NULL)
        return;

    QRect rect = option.rect;
    // 绘制选中或悬浮状态
    if ((option.state & QStyle::State_Selected) || isSelected(item))
    {
        painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentSelectSkin()));
    }
    else if (option.state & QStyle::State_MouseOver)
    {
        painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentHoverSkin()));
    }

    // 绘制图标
    painter->save();
    QString iconFile = item->getIconFile();
    QSize iconSize = item->getIconSize();
    QPoint iconPos = item->getIconPosition();
    QRect iconRect(rect.x()+iconPos.x(), rect.y()+iconPos.y(), iconSize.width(), iconSize.height());
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawPixmap(iconRect, QPixmap(iconFile));
    painter->restore();

    // 绘制文本
    painter->save();
    QString title = item->getTitle();
    QPoint titlePos = item->getTitlePosition();
    QRect textRect(iconRect.right()+titlePos.x(), rect.y()+titlePos.y(), 160, 20);
    painter->setPen(QPen(item->getFontColor()));
    painter->setFont(tagFont);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, title);
    painter->restore();

    // 绘制箭头按钮
    painter->save();
    if (item->childCount()>0)
    {
        QStyleOptionButton button;
        button.rect   = QRect(rect.right()-28, rect.y()+27, 16, 16);
        button.state |= QStyle::State_Enabled;
        button.iconSize = QSize(18, 18);
        if (m_buttonStausMap.contains(index))
        {
            if (m_buttonStausMap[index] == false)
                button.icon = QIcon(":/sysButton/Resources/img/sysButton/page-arrow-down.png");
            else
                button.icon = QIcon(":/sysButton/Resources/img/sysButton/page-arrow-up.png");
        }
        else
        {
            m_buttonStausMap[index] = false;
            button.icon = QIcon(":/sysButton/Resources/img/sysButton/page-arrow-down.png");
        }

        QWidget *pWidget = m_pButton.data();
        QApplication::style()->drawControl(QStyle::CE_PushButtonLabel, &button, painter, pWidget);
    }
    painter->restore();

    // 绘制分隔线
    bool isExpandHomePageItem = ((item->getItemGrade() == TNHomePageTreeItem::HomePageWeb) && (m_buttonStausMap[index] == true));
    bool isLastAppWebItem = ((item->getItemGrade() == TNHomePageTreeItem::AppWeb) && (item->isLastChildItemOfParent() == true));
    if (isExpandHomePageItem || isLastAppWebItem)
    {
        painter->save();
        QPen linePen(painter->pen());
        linePen.setColor(QColor("#D6E1EF"));
        painter->setPen(linePen);
        painter->drawLine(rect.left() + 1, rect.bottom(), rect.right() - 1, rect.bottom());
        painter->restore();
    }
}

QSize TNHomePageTreeItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QVariant value = index.data(Qt::SizeHintRole);
    TNHomePageTreeItem *item = static_cast<TNHomePageTreeItem*>(index.internalPointer());
    if (value.isValid() || item == nullptr)
        return qvariant_cast<QSize>(value);

    return item->getItemSizeHint();
}

bool TNHomePageTreeItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    bool bRepaint = false;
    QMouseEvent *pEvent = static_cast<QMouseEvent *>(event);

    QApplication::restoreOverrideCursor();

    QStyleOptionButton button;
    button.rect = QRect(option.rect.right()-28, option.rect.y()+26, 24, 24);

    switch (event->type())
    {
    case QEvent::MouseMove:  // 鼠标滑过
        // 鼠标位于按钮之上
        if (button.rect.contains(pEvent->pos()))
        {
            bRepaint = true;
            QApplication::setOverrideCursor(Qt::PointingHandCursor);
        }
        break;
    case QEvent::MouseButtonPress:
        break;
    case QEvent::MouseButtonRelease: // 鼠标释放
        // 鼠标位于按钮之上
        if (button.rect.contains(pEvent->pos()))
        {
            bRepaint = true;
            bool status = m_buttonStausMap[index];
            m_buttonStausMap[index] = !status;
            emit clickedArrowButton(index, m_buttonStausMap[index]);
        }
        else
        {
            emit clickedItemOtherArea(index);
        }
        break;
    default:
        break;
    }

    return bRepaint;
}

bool TNHomePageTreeItemDelegate::isSelected(TNHomePageTreeItem *item) const
{
    if (item->getItemGrade() == TNHomePageTreeItem::HomePageWeb)
        return (m_selectedItemIds.first == item->getId()) && (m_selectedItemIds.second == -1);

    if (item->getItemGrade() == TNHomePageTreeItem::AppWeb)
        return (m_selectedItemIds.first == item->parentItem()->getId()) && (m_selectedItemIds.second == item->getId());

    Q_ASSERT(!"never come to here");
    return false;
}
