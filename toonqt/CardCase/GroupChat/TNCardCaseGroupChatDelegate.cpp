#include "TNCardCaseGroupChatDelegate.h"
#include <QPainter>
#include <QHelpEvent>
#include <QToolTip>
#include <QAbstractItemView>

#include "tncommondealavator.h"
#include "TNSettingData.h"
#include "GroupChat/TNCardCaseGroupChatAdapter.h"


#define AVATAR_MARGIN_LEFT 15
#define AVATAR_MARGIN_TOP 15
#define AVATAR_MARGIN_RIGHT 10

#define TITLE_MARGIN_LEFT 65
#define TITLE_MARGIN_TOP 18

#define AVATAR_WIDTH      40
#define AVATAR_HEIGHT      40

#define TAG_MARGIN_LEFT   65
#define TAG_MARGIN_TOP   38

#define ELIDLE_TEXT_TITLE 170

TNCardCaseGroupChatDelegate::TNCardCaseGroupChatDelegate()
{
	titleFont = QFont("Microsoft Yahei");
	titleFont.setPixelSize(14);
	memberFont = QFont("Microsoft Yahei");
	memberFont.setPixelSize(10);
	memberColor = QColor("#8E8E93");
}

TNCardCaseGroupChatDelegate::~TNCardCaseGroupChatDelegate()
{

}
void TNCardCaseGroupChatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	TNCardCaseGroupChatAdapter *item = (TNCardCaseGroupChatAdapter*)index.data().toLongLong();
	if (item == nullptr)
		return;

	if (index.column() == 0)
	{
		const int marginLR = 14;
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
		QString feedId = item->getGroupChatId();

		painter->setRenderHint(QPainter::SmoothPixmapTransform);
		QString avatarPath = item->getPhotoResourceID();
		if (avatarPath.isEmpty() || !QFile::exists(avatarPath))
		{
			if (latestAvatarMap[feedId].isNull())
			{
				avatarPath = (":/Resources/toolWidget/defaultAvatar.png");
				(const_cast<TNCardCaseGroupChatDelegate *>(this))->latestAvatarMap.insert(feedId
					, TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), Cust_Type::cust_radius));
				latestAvatarMap[feedId].scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
			}
			emit downLoadAvatar(feedId, item->getAvatarURL(), 3);
		}
		else
		{
			QPixmap avatar = TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), Cust_Type::cust_radius);
			avatar.scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
			(const_cast<TNCardCaseGroupChatDelegate *>(this))->latestAvatarMap.remove(feedId);
			(const_cast<TNCardCaseGroupChatDelegate *>(this))->latestAvatarMap.insert(feedId, avatar); //更新新的
		}
		painter->drawPixmap(rect.x() + AVATAR_MARGIN_LEFT, rect.y() + AVATAR_MARGIN_TOP, AVATAR_WIDTH, AVATAR_HEIGHT, latestAvatarMap[feedId]);
		painter->setRenderHint(QPainter::SmoothPixmapTransform,false);

		painter->setRenderHint(QPainter::Antialiasing);
		int titleX = rect.x() + TITLE_MARGIN_LEFT;
		int titleY = rect.y() + TITLE_MARGIN_TOP + 10;
		painter->setFont(titleFont);

		QString title = item->getTitle();
		title = painter->fontMetrics().elidedText(title, Qt::ElideMiddle, ELIDLE_TEXT_TITLE, Qt::TextShowMnemonic);

		painter->drawText(titleX, titleY, title);

		QString	memberText = QString("%1").arg(item->getMemberCount());
		memberText = memberText + QStringLiteral("人");
		QFontMetrics fm(memberFont);
        int textLen = fm.width(memberText);
        int textHeight = fm.height();
#ifdef Q_OS_WIN
        textHeight = fm.height()-2;
#endif


		int rectWidth = textLen + marginLR;

		QBrush memberBrush(QColor(0xFF,0xFF,0xFF));
		QColor bordColor(0xD3, 0xD3, 0xD2);
		QPen decorationPen(bordColor, 1);
		QRect decoration(rect.x() + TAG_MARGIN_LEFT, rect.y() + TAG_MARGIN_TOP, rectWidth, textHeight);
		painter->setPen(decorationPen);
		painter->setBrush(memberBrush);
		QPainterPath path;
		path.addRoundedRect(decoration, 6, 6);
		painter->drawPath(path);

		painter->setPen(memberColor);
		painter->setFont(memberFont);
		painter->drawText(decoration, Qt::AlignCenter | Qt::AlignVCenter, memberText);

		painter->setPen(oldPen);
		painter->setBrush(oldBrush);//设置画刷形式
		painter->setRenderHint(QPainter::Antialiasing, false);
	}
}
QSize TNCardCaseGroupChatDelegate::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QVariant value = index.data(Qt::SizeHintRole);
	if (value.isValid())
		return qvariant_cast<QSize>(value);
	return QSize(LIST_AREA_WIDTH, LIST_AREA_HEIGHT);
}
bool TNCardCaseGroupChatDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view,
	const QStyleOptionViewItem &option, const QModelIndex &index)
{
	if (!event || !view)
		return false;

	if (event->type() == QEvent::ToolTip) {
		QRect rect = view->visualRect(index);
		QSize size = sizeHint(option, index);
		QPoint pos = event->pos();
		if (rect.contains(pos)) {
			TNCardCaseGroupChatAdapter *item = (TNCardCaseGroupChatAdapter*)index.data().toLongLong();
			if (item != nullptr)
			{
				int titleX = rect.x() + TITLE_MARGIN_LEFT;
				int titleY = rect.y() + TITLE_MARGIN_TOP;

				int textLen = 0;
				int textHei = 0;
				QFontMetrics fm(view->font());
				QString title = item->getTitle();
				QString elidText = fm.elidedText(title, Qt::ElideMiddle, ELIDLE_TEXT_TITLE, Qt::TextShowMnemonic);
				textLen = fm.width(elidText);
				textHei = fm.height();

				QRect titleRect(titleX, titleY, textLen, textHei);
				if (titleRect.contains(pos))
				{
					QToolTip::showText(event->globalPos(), title, view, rect);
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
