#include "TNCardCaseGCDelegate.h"
#include "TNCardCaseTreeItem.h"
#include <QPainter>
#include <QHelpEvent>
#include <QToolTip>
#include <QAbstractItemView>

#include "tncommondealavator.h"
#include "TNSettingData.h"
#include "GroupChat/TNGroupChatItem.h"

#define EXPAND_MARGIN_LEFT 28
#define EXPAND_MARGIN_TOP 13

#define AVATAR_MARGIN_LEFT 15
#define AVATAR_MARGIN_TOP 15
#define AVATAR_MARGIN_RIGHT 10

#define TITLE_MARGIN_LEFT 65
#define TITLE_MARGIN_TOP 20

#define AVATAR_WIDTH      40
#define AVATAR_HEIGHT      40

#define TAG_MARGIN_LEFT   65
#define TAG_MARGIN_TOP   38
#define TAGRECT_WIDTH     30
#define TAGRECT_HEIGHT    16

#define ELIDLE_TEXT_TITLE 170

TNCardCaseGCDelegate::TNCardCaseGCDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
	titleFont = QFont("Microsoft Yahei");
    titleFont.setPixelSize(13);
	memberFont = QFont("Microsoft Yahei");
	memberFont.setPixelSize(12);
	memberColor = QColor("#858FA4");
}

TNCardCaseGCDelegate::~TNCardCaseGCDelegate()
{

}
void TNCardCaseGCDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QRect rect = option.rect;

	if (option.state & QStyle::State_Selected)
	{
		painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentSelectSkin()));
	}
	else if (option.state & QStyle::State_MouseOver)
	{
		painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentHoverSkin()));
	}
	QPen oldPen = painter->pen();
	QBrush oldBrush = painter->brush();
	QFont oldFont = painter->font();

	TNCardCaseTreeItem *item = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
	if (item == nullptr)
		return;
	if (item->getItemGrade() == TNCardCaseTreeItem::Expand)
	{
		QString text = item->data(0).toString();
		int num = item->childCount();
		bool status = num > 0 ? true : false;
		
		painter->setRenderHint(QPainter::SmoothPixmapTransform);
		if (item->getStatus())
		{
			//展开
			QString expandPath = tr(":/Resources/toolWidget/down_arrow.png");
			QPixmap ico(expandPath);
			if (!ico.isNull())
			{
				ico.scaled(7, 7, Qt::KeepAspectRatio);
				painter->drawPixmap(rect.x() + 17, rect.y() + 17, 7, 7, ico);
			}
		}
		else
		{
			//收回
			QString unexpandPath = tr(":/Resources/toolWidget/right_arrow.png");
			QPixmap unico(unexpandPath);
			if (!unico.isNull())
			{
				unico.scaled(7, 7, Qt::KeepAspectRatio);
				painter->drawPixmap(rect.x() + 17, rect.y() + 17, 7, 7, unico);
			}
		}
		painter->setRenderHint(QPainter::SmoothPixmapTransform,false);
		QRect expandRect = rect;
		expandRect.setLeft(EXPAND_MARGIN_LEFT);

		painter->setFont(titleFont);
		painter->drawText(expandRect, Qt::AlignLeft | Qt::AlignVCenter, text);

		painter->setFont(oldFont);

	}
	else if (item->getItemGrade() == TNCardCaseTreeItem::GroupChat)
	{
		painter->setRenderHint(QPainter::SmoothPixmapTransform);
		TNGroupChatItem *groupChatItem = static_cast<TNGroupChatItem*>(item);

		QString avatarPath = groupChatItem->getPhotoResourceID();
		if (avatarPath.isEmpty() || !QFile::exists(avatarPath))
		{
			avatarPath = tr(":/Resources/toolWidget/defaultAvatar.png");
			emit downLoadAvatar(groupChatItem->getDialogID(), groupChatItem->getAvatarURL(), 3);
		}
		QPixmap avatar = TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), Cust_Type::cust_radius);
		avatar.scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
		painter->drawPixmap(rect.x() + AVATAR_MARGIN_LEFT, rect.y() + AVATAR_MARGIN_TOP, AVATAR_WIDTH, AVATAR_HEIGHT, avatar);

		int titleX = rect.x() + TITLE_MARGIN_LEFT;
		int titleY = rect.y() + TITLE_MARGIN_TOP + 10;
		painter->setFont(titleFont);

		int textLen = 0;
		QString title = groupChatItem->getTitle();
		title = painter->fontMetrics().elidedText(title, Qt::ElideMiddle, ELIDLE_TEXT_TITLE, Qt::TextShowMnemonic);

		painter->drawText(titleX, titleY, title);

		QString	decorationText = QString("%1").arg(groupChatItem->getMemberNumber());
		decorationText = decorationText + QStringLiteral("人");
		int rectWidth = TAGRECT_WIDTH + (decorationText.length() - 2) * 6;

		QColor bordColor(0xDE,0xDE,0xDE);
		QPen decorationPen(bordColor, 1);
		QRect decoration(rect.x() + TAG_MARGIN_LEFT, rect.y()+TAG_MARGIN_TOP, rectWidth, TAGRECT_HEIGHT);
		painter->setPen(decorationPen);
		QPainterPath path;
		path.addRoundedRect(decoration, 2, 2);
		painter->drawPath(path);

		painter->setPen(memberColor);
		painter->setFont(memberFont);
		painter->drawText(decoration, Qt::AlignCenter | Qt::AlignVCenter, decorationText);

		painter->setPen(oldPen);
		painter->setBrush(oldBrush);//设置画刷形式
		painter->setRenderHint(QPainter::SmoothPixmapTransform,false);
	}
}
QSize TNCardCaseGCDelegate::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QVariant value = index.data(Qt::SizeHintRole);
	if (value.isValid())
		return qvariant_cast<QSize>(value);

	TNCardCaseTreeItem *item = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
	if (item == NULL)
		return qvariant_cast<QSize>(value);

	if (item->getItemGrade() == TNCardCaseTreeItem::Expand)
	{
		return QSize(TREE_ITEM_WIDTH, TREE_SECONDNODE_HEIGHT);
	}
	else
	{
		return QSize(TREE_ITEM_WIDTH, TREE_THIRDNODE_HEIGHT);
	}
}
bool TNCardCaseGCDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view,
	const QStyleOptionViewItem &option, const QModelIndex &index)
{
	if (!event || !view)
		return false;

	if (event->type() == QEvent::ToolTip) {
		QRect rect = view->visualRect(index);
		QSize size = sizeHint(option, index);
		QPoint pos = event->pos();
		if (rect.contains(pos)) {
			TNCardCaseTreeItem *item = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
			if (item != nullptr && item->getItemGrade() == TNCardCaseTreeItem::GroupChat)
			{
				TNGroupChatItem *groupChatItem = static_cast<TNGroupChatItem*>(item);

				int titleX = rect.x() + TITLE_MARGIN_LEFT;
				int titleY = rect.y() + TITLE_MARGIN_TOP;

				int textLen = 0;
				int textHei = 0;
				QFontMetrics fm(view->font());
				QString title = groupChatItem->getTitle();
				title = fm.elidedText(title, Qt::ElideMiddle, ELIDLE_TEXT_TITLE, Qt::TextShowMnemonic);
				textLen = fm.width(title);
				textHei = fm.height();

				QRect titleRect(titleX, titleY, textLen, textHei);
				if (titleRect.contains(pos))
				{
					QToolTip::showText(event->globalPos(), groupChatItem->getTitle(), view, rect);
				}
				else
					QToolTip::hideText();
			}
		}
		else
			QToolTip::hideText();
		return true;
	}

	return QStyledItemDelegate::helpEvent(event, view, option, index);
}
