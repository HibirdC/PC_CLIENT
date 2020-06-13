#include "TNCardCaseGroupDelegate.h"
#include <QPainter>
#include <QHelpEvent>
#include <QToolTip>
#include <QAbstractItemView>
#include <QDebug>

#include "tncommondealavator.h"
#include "TNSettingData.h"
#include "TNCardCaseGroupAdapter.h"

#define AVATAR_MARGIN_LEFT 15
#define AVATAR_MARGIN_RIGHT 10
#define AVATAR_MARGIN_TOP 15
#define AVATAR_MARGIN_BUTTOM 15

#define TITLE_MARGIN_LEFT 65
#define TITLE_MARGIN_TOP 18

#define TAG_MARGIN_LEFT 65
#define TAG_MARGIN_TOP 38

#define AVATAR_WIDTH 40
#define AVATAR_HEIGHT 40

TNCardCaseGroupDelegate::TNCardCaseGroupDelegate()
{
	titleFont = QFont("Microsoft Yahei");
	titleFont.setPixelSize(14);
	tagFont = QFont("Microsoft Yahei");
	tagFont.setPixelSize(10);
}

TNCardCaseGroupDelegate::~TNCardCaseGroupDelegate()
{

}
void TNCardCaseGroupDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	TNCardCaseGroupAdapter *item = (TNCardCaseGroupAdapter*)index.data().toLongLong();
	if (item == nullptr)
		return;

	if (index.column() == 0)
	{
		const int marginLR = 14;
		const int marginTag = 10;
		QColor fillColor;
		QColor bordColor;
		QColor tagFontColor;

		QRect rect = option.rect;
		QPen oldPen = painter->pen();
		QBrush oldBrush = painter->brush();
		QFont oldFont = painter->font();
		QString feedId = item->getGroupId();

		if (option.state & QStyle::State_Selected)
		{
			painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentSelectSkin()));
		}
		else if (option.state & QStyle::State_MouseOver)
		{
			painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentHoverSkin()));
		}

		painter->setRenderHint(QPainter::SmoothPixmapTransform);
		QString avatarPath = item->getPhotoResourceID();
		if (avatarPath.isEmpty() || !QFile::exists(avatarPath))
		{
			if (latestAvatarMap[feedId].isNull())
			{
				avatarPath = (":/Resources/toolWidget/defaultAvatar.png");
				(const_cast<TNCardCaseGroupDelegate *>(this))->latestAvatarMap.insert(feedId
					, TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), Cust_Type::cust_hexagon));
				latestAvatarMap[feedId].scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
			}
			emit downLoadAvatar(feedId, item->getAvatarURL(), 2);
		}
		else
		{
			QPixmap avatar = TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), Cust_Type::cust_hexagon);
			avatar.scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
			(const_cast<TNCardCaseGroupDelegate *>(this))->latestAvatarMap.remove(feedId);
			(const_cast<TNCardCaseGroupDelegate *>(this))->latestAvatarMap.insert(feedId, avatar); //更新新的
		}

		painter->drawPixmap(rect.x() + AVATAR_MARGIN_LEFT, rect.y() + AVATAR_MARGIN_TOP, AVATAR_WIDTH, AVATAR_HEIGHT, latestAvatarMap[feedId]);
		painter->setRenderHint(QPainter::SmoothPixmapTransform,false);

		int titleX = rect.x() + TITLE_MARGIN_LEFT;
		int titleY = rect.y() + TITLE_MARGIN_TOP + 10;
		painter->setFont(titleFont);

		QString title = item->getTitle();
		title = painter->fontMetrics().elidedText(title, Qt::ElideMiddle, 170, Qt::TextShowMnemonic);

		painter->drawText(titleX, titleY, title);

		int preTagLen = 0;
		bool isCreator = item->getIsCreator();
		bool isAdmin = item->getIsAdmin();
		if (isCreator || isAdmin)
		{
			painter->setRenderHint(QPainter::Antialiasing);
			QString	decorationText = isCreator ? QStringLiteral("版主") : QStringLiteral("管理员");
			bordColor = isCreator ? QColor(0xF6, 0x7C, 0x5E) : QColor(0x32, 0xC4, 0xF0);
			fillColor = isCreator ? QColor(0xF6, 0x7C, 0x5E) : QColor(0x32, 0xC4, 0xF0);
			tagFontColor = QColor("#FFFFFF");

			QFontMetrics fm(tagFont);
			int textLen = fm.width(decorationText);
			int rectWidth = textLen + marginLR;
            int rectHeight = 0;
#ifdef Q_OS_WIN
            rectHeight = fm.height()-2;
#else
            rectHeight = fm.height();
#endif

			QBrush decorationBrush(fillColor);
			QPen decorationPen(bordColor, 1);
			QRect decoration(rect.x() + TAG_MARGIN_LEFT, rect.y() + TAG_MARGIN_TOP, rectWidth, rectHeight);
			painter->setPen(decorationPen);
			painter->setBrush(decorationBrush);
			QPainterPath path;
			path.addRoundedRect(decoration, 6, 6);
			painter->drawPath(path);

			painter->setPen(tagFontColor);
			painter->setFont(tagFont);
			painter->drawText(decoration, Qt::AlignCenter | Qt::AlignVCenter, decorationText);

			preTagLen = rectWidth + marginTag;
			painter->setFont(oldFont);
			painter->setPen(oldPen);
			painter->setBrush(oldBrush);
			painter->setRenderHint(QPainter::Antialiasing, false);
		}

		painter->setRenderHint(QPainter::Antialiasing);
		QString	memberText = QString("%1").arg(item->getMemberCount());
		memberText = memberText + QStringLiteral("人");

		QFontMetrics fm(tagFont);
		int textLen = fm.width(memberText);
        int textHeight = 0;
#ifdef Q_OS_WIN
        textHeight = fm.height()-2;
#else
        textHeight = fm.height();
#endif

		int memberRectWidth = textLen + marginLR;

		fillColor = QColor(0xFF, 0xFF, 0xFF);
		bordColor = QColor(0xDE, 0xD2, 0xD2);
		tagFontColor = QColor(0x8E,0x8E,0x93);

		QBrush decorationBrush(fillColor);
		QPen decorationPen(bordColor, 1);
		QRect decoration(rect.x() + TAG_MARGIN_LEFT + preTagLen, rect.y() + TAG_MARGIN_TOP, memberRectWidth, textHeight);
		painter->setPen(decorationPen);
		painter->setBrush(decorationBrush);
		QPainterPath path;
		path.addRoundedRect(decoration, 6, 6);
		painter->drawPath(path);

		painter->setPen(tagFontColor);
		painter->setFont(tagFont);
		painter->drawText(decoration, Qt::AlignCenter | Qt::AlignVCenter, memberText);
		preTagLen = preTagLen + memberRectWidth + marginTag;

		QString object = item->getGroupSubject();
		if (!object.isEmpty())
		{
			QFontMetrics fm(tagFont);
			int textLen = fm.width(object);
            int textHeight = 0;
#ifdef Q_OS_WIN
            textHeight = fm.height()-2;
#else
            textHeight = fm.height();
#endif

			int objectRectWidth = textLen + marginLR;

			QPen decorationPen(bordColor, 1);
			QRect decoration(rect.x() + TAG_MARGIN_LEFT + preTagLen, rect.y() + TAG_MARGIN_TOP, objectRectWidth, textHeight);
			painter->setPen(decorationPen);
			painter->setBrush(decorationBrush);
			QPainterPath path;
			path.addRoundedRect(decoration, 6, 6);
			painter->drawPath(path);

			painter->setPen(tagFontColor);
			painter->setFont(tagFont);
			painter->drawText(decoration, Qt::AlignCenter | Qt::AlignVCenter, object);
		}
		painter->setFont(oldFont);
		painter->setPen(oldPen);
		painter->setBrush(oldBrush);
		painter->setRenderHint(QPainter::Antialiasing, false);
	}
}
QSize TNCardCaseGroupDelegate::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QVariant value = index.data(Qt::SizeHintRole);
	if (value.isValid())
		return qvariant_cast<QSize>(value);
	return QSize(LIST_AREA_WIDTH, LIST_AREA_HEIGHT);
}
bool TNCardCaseGroupDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view,
	const QStyleOptionViewItem &option, const QModelIndex &index)
{
	if (!event || !view)
		return false;

	if (event->type() == QEvent::ToolTip) {
		QRect rect = view->visualRect(index);
		QSize size = sizeHint(option, index);
		QPoint pos = event->pos();
		if (rect.contains(pos)) {
			TNCardCaseGroupAdapter *item = (TNCardCaseGroupAdapter*)index.data().toLongLong();
			if (item == nullptr)
				return false;
			int titleX = rect.x() + TITLE_MARGIN_LEFT;
			int titleY = rect.y() + TITLE_MARGIN_TOP;

			QFontMetrics fm(view->font());
			QString title = item->getTitle();
			QString elideTitle = fm.elidedText(title, Qt::ElideMiddle, 170, Qt::TextShowMnemonic);
			int textLen = fm.width(elideTitle);
			int textHei = fm.height();

			QRect titleRect(titleX, titleY, textLen, textHei);

			if (titleRect.contains(pos))
			{
				QToolTip::showText(event->globalPos(), title, view, rect);
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
