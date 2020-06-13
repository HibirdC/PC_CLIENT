#include "TNMineDelegate.h"
#include <QDebug>
#include <QTableView>
#include <QPainter>
#include <QHelpEvent>
#include <QToolTip>

#include "NetWorkAPI.h"
#include "TNMineAdapter.h"
#include "tncommondealavator.h"
#include "TNSettingData.h"

#define AVATAR_MARGIN_LEFT     15
#define AVATAR_MARGIN_RIGHT    10
#define AVATAR_MARGIN_TOP      15
#define AVATAR_MARGIN_BUTTOM   15

#define TITLE_MARGIN_LEFT      65
#define TITLE_MARGIN_TOP       19

#define SUBTITLE_MARGIN_LEFT   65
#define SUBTITLE_MARGIN_TOP    39

#define AVATAR_WIDTH           40
#define AVATAR_HEIGHT          40

TNMineDelegate::TNMineDelegate()
{
	titleFont = QFont("Microsoft Yahei");
	titleFont.setPixelSize(14);
	subTitleFont = QFont("Microsoft Yahei");
	subTitleFont.setPixelSize(12);
	subTitleColor = QColor("#5D677D");
}

TNMineDelegate::~TNMineDelegate()
{

}
void TNMineDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	TNMineAdapter *adapter = (TNMineAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return;

	if (index.column() == 0)
	{
		QRect rect = option.rect;
		QPen oldPen = painter->pen();
		QBrush oldBrush = painter->brush();
		QFont oldFont = painter->font();
		QString feedId = adapter->getFeedId();

		if (option.state & QStyle::State_Selected)
		{
			painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentSelectSkin()));
		}
		else if (option.state & QStyle::State_MouseOver)
		{
			painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentHoverSkin()));
		}

		painter->setRenderHint(QPainter::SmoothPixmapTransform);
		QString avatarPath = adapter->getPhotoResourceID();
		Cust_Type _type;
		if (adapter->getFeedId().startsWith("c_"))
			_type = Cust_Type::cust_ellipse;
		else
			_type = Cust_Type::cust_radius;

		if (avatarPath.isEmpty() || !QFile::exists(avatarPath))
		{
			if (latestAvatarMap[feedId].isNull())
			{
				avatarPath = (":/Resources/toolWidget/defaultAvatar.png");
				(const_cast<TNMineDelegate *>(this))->latestAvatarMap.insert(feedId
					, TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), _type));
				latestAvatarMap[feedId].scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
			}
			emit downLoadAvatar(feedId, adapter->getAvatarURL(), 0);
		}
		else
		{
			QPixmap avatar = TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), _type);
			avatar.scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
			(const_cast<TNMineDelegate *>(this))->latestAvatarMap.remove(feedId);
			(const_cast<TNMineDelegate *>(this))->latestAvatarMap.insert(feedId, avatar); 
		}

		painter->drawPixmap(rect.x() + AVATAR_MARGIN_LEFT, rect.y() + AVATAR_MARGIN_TOP, AVATAR_WIDTH, AVATAR_HEIGHT, latestAvatarMap[feedId]);

		int titleX = rect.x() + TITLE_MARGIN_LEFT;
		int titleY = rect.y() + TITLE_MARGIN_TOP + 10;
		painter->setFont(titleFont);

		int textLen = 0;
		QString title = adapter->getTitle();
		
		title = painter->fontMetrics().elidedText(title, Qt::ElideMiddle, 170, Qt::TextShowMnemonic);

		painter->drawText(titleX, titleY, title);

		painter->setPen(subTitleColor);
		int subX = rect.x() + SUBTITLE_MARGIN_LEFT;
		int subY = rect.y() + SUBTITLE_MARGIN_TOP + 10;
		painter->setFont(subTitleFont);
		QString subTitle = painter->fontMetrics().elidedText(adapter->getSubTitle(),
			Qt::ElideMiddle, 170, Qt::TextShowMnemonic);
		painter->drawText(subX, subY, subTitle);

		painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
		painter->setFont(oldFont);
		painter->setPen(oldPen);
	}
}

QSize TNMineDelegate::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QVariant value = index.data(Qt::SizeHintRole);
	if (value.isValid())
		return qvariant_cast<QSize>(value);

	TNMineAdapter *adapter = (TNMineAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return qvariant_cast<QSize>(value);

	return QSize(LIST_AREA_WIDTH, LIST_AREA_HEIGHT);
}
bool TNMineDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view,
	const QStyleOptionViewItem &option, const QModelIndex &index)
{
	if (!event || !view)
		return false;

	if (event->type() == QEvent::ToolTip) {
		QRect rect = view->visualRect(index);
		QSize size = sizeHint(option, index);
		QPoint pos = event->pos();
		if (rect.contains(pos)) {
			TNMineAdapter *adapter = (TNMineAdapter*)index.data().toLongLong();

			int titleX = rect.x() + TITLE_MARGIN_LEFT;
			int titleY = rect.y() + TITLE_MARGIN_TOP;

			int textLen = 0, subTextLen = 0;
			int textHei = 0,subTextHei = 0;
			QString elideTitle;
			QString title = adapter->getTitle();
			QFontMetrics fm(view->font());

			elideTitle = fm.elidedText(title, Qt::ElideMiddle, 170, Qt::TextShowMnemonic);
			textLen = fm.width(elideTitle);
			textHei = fm.height();

			QRect titleRect(titleX, titleY, textLen, textHei);

			int subX = rect.x() + SUBTITLE_MARGIN_LEFT;
			int subY = rect.y() + SUBTITLE_MARGIN_TOP;


			QString subTitle = adapter->getSubTitle();
			QString elideSubtitle = fm.elidedText(subTitle,
				Qt::ElideMiddle, 170, Qt::TextShowMnemonic);
			subTextLen = fm.width(elideSubtitle);
			subTextHei = fm.height();

			QRect subRect(subX, subY, subTextLen, subTextHei);
			if (titleRect.contains(pos))
			{
				QToolTip::showText(event->globalPos(), title, view, rect);
			}
			else if (subRect.contains(pos))
			{
				QToolTip::showText(event->globalPos(), subTitle, view, rect);
			}
			else
				QToolTip::hideText();
		}
		else
			QToolTip::hideText();
		return true;
	}
	return QStyledItemDelegate::helpEvent(event, view, option, index);
}
