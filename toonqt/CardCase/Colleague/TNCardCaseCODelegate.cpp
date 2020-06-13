#include "TNCardCaseCODelegate.h"
#include <QPainter>
#include <QHelpEvent>
#include <QToolTip>
#include <QAbstractItemView>
#include <QDebug>

#include "tncommondealavator.h"
#include "TNSettingData.h"
#include "Colleague/TNCompanyItem.h"
#include "Colleague/TNDepartmentItem.h"
#include "Colleague/TNStaffItem.h"

#define COMPANYITEMLINE_MARGIN_LEFT 15
#define COMPANYITEMLINE_MARGIN_TOP  9
#define COMPANYITEMLINE_WIDTH       2
#define COMPANYITEMLINE_HEIGHT      12

#define COMPANYITEMTEXT_MARGIN_LEFT 23
#define COMPANYITEMTEXT_MARGIN_TOP  20

#define DEPART_MARGIN_LEFT          28
#define DEPART_NUMBER_MARGIN_RIGHT  15

#define AVATAR_WIDTH      40
#define AVATAR_HEIGHT      40

#define AVATAR_MARGIN_LEFT 15
#define AVATAR_MARGIN_TOP 15

#define TITLE_MARGIN_LEFT 65
#define TITLE_MARGIN_TOP  21

#define SUBTITLE_MARGIN_LEFT 65
#define SUBTITLE_MARGIN_TOP 39

#define ELIDL_COMPANY_NAME  200
#define ELIDL_DEPART_NAME   180
#define ELIDL_STAFF_TITLE   170
#define ELIDL_STAFF_SUBTITLE  170

TNCardCaseCODelegate::TNCardCaseCODelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
	companyFont = QFont("Microsoft Yahei");
	companyFont.setPixelSize(14);
	departFont = QFont("Microsoft Yahei");
	departFont.setPixelSize(14);
	staffFont = QFont("Microsoft Yahei");
	staffFont.setPixelSize(13);

	subTitleFont = QFont("Microsoft Yahei");
	subTitleFont.setPixelSize(12);

	companyColor = QColor("#858FA4");
	departNumberColor = QColor("#858FA4");
	subTitleColor = QColor("#5D677D");
}

TNCardCaseCODelegate::~TNCardCaseCODelegate()
{

}
void TNCardCaseCODelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QRect rect = option.rect;

	QPen oldPen = painter->pen();
	QBrush oldBrush = painter->brush();
	QFont oldFont = painter->font();

	TNCardCaseTreeItem *item = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
	if (item == nullptr)
		return;

	if (item->getItemGrade() == TNCardCaseTreeItem::Company)
	{
		painter->setRenderHint(QPainter::Antialiasing);
		QPen linePen(QColor(TNSettingData::instance()->GetCurrentThemeSkin()), COMPANYITEMLINE_WIDTH);
		QString text = item->data(0).toString();
		painter->setPen(linePen);
		painter->drawLine(rect.x() + COMPANYITEMLINE_MARGIN_LEFT, rect.y() + COMPANYITEMLINE_MARGIN_TOP, rect.x() + COMPANYITEMLINE_MARGIN_LEFT, rect.y() + COMPANYITEMLINE_MARGIN_TOP + COMPANYITEMLINE_HEIGHT);
		painter->setRenderHint(QPainter::Antialiasing,false);

		painter->setPen(companyColor);
		painter->setFont(companyFont);
		QRect Rect = rect;
		Rect.setLeft(COMPANYITEMTEXT_MARGIN_LEFT);
		QString elideText = painter->fontMetrics().elidedText(text, Qt::ElideMiddle, ELIDL_COMPANY_NAME, Qt::TextShowMnemonic);

		painter->drawText(Rect, Qt::AlignLeft | Qt::AlignVCenter, elideText);

		painter->setPen(oldPen);
	}
	else if (item->getItemGrade() == TNCardCaseTreeItem::Department)
	{
		QString text = item->data(0).toString();
		int num = item->childCount();

		painter->setRenderHint(QPainter::SmoothPixmapTransform);
		if (item->getStatus())
		{
			//展开
			QString expandPath = (":/Resources/toolWidget/down_arrow.png");
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
			QString unexpandPath = (":/Resources/toolWidget/right_arrow.png");
			QPixmap unico(unexpandPath);
			if (!unico.isNull())
			{
				unico.scaled(7, 7, Qt::KeepAspectRatio);
				painter->drawPixmap(rect.x() + 17, rect.y() + 17, 7, 7, unico);
			}
		}
		painter->setRenderHint(QPainter::SmoothPixmapTransform, false);

		painter->setFont(departFont);
		QString elideText = painter->fontMetrics().elidedText(text, Qt::ElideMiddle, ELIDL_DEPART_NAME, Qt::TextShowMnemonic);

		QRect txtRect = rect;
		txtRect.setLeft(DEPART_MARGIN_LEFT);
		painter->drawText(txtRect, Qt::AlignLeft | Qt::AlignVCenter, elideText);

		//绘制数字
		painter->setFont(subTitleFont);
		painter->setPen(departNumberColor);
		QRect numberRect = rect;
		numberRect.setRight(TREE_ITEM_WIDTH-DEPART_NUMBER_MARGIN_RIGHT);
		painter->drawText(numberRect, Qt::AlignRight | Qt::AlignVCenter, QString::number(num, 10));

		painter->setFont(oldFont);
		painter->setPen(oldPen);
	}
	else if (item->getItemGrade() == TNCardCaseTreeItem::Staff)
	{
		if (option.state & QStyle::State_Selected)
		{
			painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentSelectSkin()));
		}
		else if (option.state & QStyle::State_MouseOver)
		{
			painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentHoverSkin()));
		}
		painter->setRenderHint(QPainter::SmoothPixmapTransform);
		TNStaffItem *staffItem = static_cast<TNStaffItem*>(item);

		QString feedId = staffItem->getDialogID();
		QString avatarPath = staffItem->getPhotoResourceID();
		if (avatarPath.isEmpty() || !QFile::exists(avatarPath))
		{
			if (latestAvatarMap[feedId].isNull())
			{
				avatarPath = (":/Resources/toolWidget/defaultAvatar.png");
				(const_cast<TNCardCaseCODelegate *>(this))->latestAvatarMap.insert(feedId
					, TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), Cust_Type::cust_radius));
				latestAvatarMap[feedId].scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
			}
			emit downLoadAvatar(feedId, staffItem->getAvatarURL(), 1);
		}
		else
		{
			QPixmap avatar = TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), Cust_Type::cust_radius);
			avatar.scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
			(const_cast<TNCardCaseCODelegate *>(this))->latestAvatarMap.remove(feedId);
			(const_cast<TNCardCaseCODelegate *>(this))->latestAvatarMap.insert(feedId, avatar); //更新新的
		}
		painter->drawPixmap(rect.x() + AVATAR_MARGIN_LEFT, rect.y() + AVATAR_MARGIN_TOP, AVATAR_WIDTH, AVATAR_HEIGHT, latestAvatarMap[feedId]);
		painter->setRenderHint(QPainter::SmoothPixmapTransform,false);

		int titleX = rect.x() + TITLE_MARGIN_LEFT;
		int titleY = rect.y() + TITLE_MARGIN_TOP + 10;
		painter->setFont(staffFont);

		int textLen = 0;
		QString title = staffItem->getTitle();
		title = painter->fontMetrics().elidedText(title, Qt::ElideMiddle, ELIDL_STAFF_TITLE, Qt::TextShowMnemonic);

		painter->drawText(titleX, titleY, title);

		painter->setPen(subTitleColor);
		int subX = rect.x() + SUBTITLE_MARGIN_LEFT;
		int subY = rect.y() + SUBTITLE_MARGIN_TOP + 10;
		painter->setFont(subTitleFont);
		QString subTitle = painter->fontMetrics().elidedText(staffItem->getSubTitle(),
			Qt::ElideMiddle, ELIDL_STAFF_SUBTITLE, Qt::TextShowMnemonic);
		painter->drawText(subX, subY, subTitle);

		painter->setPen(oldPen);
		painter->setBrush(oldBrush);//设置画刷形式
	}
}
QSize TNCardCaseCODelegate::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QVariant value = index.data(Qt::SizeHintRole);
	if (value.isValid())
		return qvariant_cast<QSize>(value);

	TNCardCaseTreeItem *item = static_cast<TNCardCaseTreeItem*>(index.internalPointer());
	if (item == NULL)
		return qvariant_cast<QSize>(value);

	if (item->getItemGrade() == TNCardCaseTreeItem::Company)
	{
		return QSize(TREE_ITEM_WIDTH, TREE_FIRSTNODE_HEIGHT);
	}
	else if (item->getItemGrade() == TNCardCaseTreeItem::Department)
	{
		return QSize(TREE_ITEM_WIDTH, TREE_SECONDNODE_HEIGHT);
	}
	else
	{
		return QSize(TREE_ITEM_WIDTH, TREE_THIRDNODE_HEIGHT);
	}
}
bool TNCardCaseCODelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view,
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
			if (item == nullptr)
				return false;
			if (item->getItemGrade() == TNCardCaseTreeItem::Company)
			{
				int textLen = 0;
				int textHei = 0;
				QFontMetrics fm(view->font());
				QString name = item->data(0).toString();
				QString elidename = fm.elidedText(name, Qt::ElideMiddle, ELIDL_COMPANY_NAME, Qt::TextShowMnemonic);
				textLen = fm.width(elidename);
				textHei = fm.height();

				int titleX = rect.x() + COMPANYITEMTEXT_MARGIN_LEFT;
				int titleY = rect.y() + (rect.height() - textHei)/2;

				QRect titleRect(titleX, titleY, textLen, textHei);
				if (titleRect.contains(pos))
				{
					QToolTip::showText(event->globalPos(), name, view, rect);
				}
				else
					QToolTip::hideText();
			}
			else if (item->getItemGrade() == TNCardCaseTreeItem::Department)
			{
				int textLen = 0;
				int textHei = 0;
				QFontMetrics fm(view->font());
				QString departName = item->data(0).toString();
				QString elideDepartname = fm.elidedText(departName, Qt::ElideMiddle, ELIDL_DEPART_NAME, Qt::TextShowMnemonic);
				textLen = fm.width(elideDepartname);
				textHei = fm.height();

				int titleX = rect.x() + DEPART_MARGIN_LEFT;
				int titleY = rect.y() + (rect.height() - textHei) / 2;

				QRect titleRect(titleX, titleY, textLen, textHei);
				if (titleRect.contains(pos))
				{
					QToolTip::showText(event->globalPos(), departName, view, rect);
				}
				else
					QToolTip::hideText();
			}
			else if (item->getItemGrade() == TNCardCaseTreeItem::Staff)
			{
				int textLen = 0;
				int textHei = 0;

				TNStaffItem *staffItem = static_cast<TNStaffItem*>(item);
				QFontMetrics fm(view->font());
				QString title = staffItem->getTitle();
				QString elideTitle = fm.elidedText(title, Qt::ElideMiddle, ELIDL_STAFF_TITLE, Qt::TextShowMnemonic);
				textLen = fm.width(elideTitle);
				textHei = fm.height();

				int titleX = rect.x() + TITLE_MARGIN_LEFT;
				int titleY = rect.y() + TITLE_MARGIN_TOP;
				QRect titleRect(titleX, titleY, textLen, textHei);

				int subTextLen = 0;
				int subTextHei = 0;
				QFontMetrics subFm(view->font());
				QString subTitle = staffItem->getSubTitle();
				QString elideSubTitle = subFm.elidedText(subTitle, Qt::ElideMiddle, ELIDL_STAFF_SUBTITLE, Qt::TextShowMnemonic);
				subTextLen = subFm.width(elideSubTitle);
				subTextHei = subFm.height();

				int subX = rect.x() + SUBTITLE_MARGIN_LEFT;
				int subY = rect.y() + SUBTITLE_MARGIN_TOP;

				QRect subTitleRect(subX, subY, subTextLen, subTextHei);
				if (titleRect.contains(pos))
				{
					QToolTip::showText(event->globalPos(), title, view, rect);
				}
				else if (subTitleRect.contains(pos))
				{
					QToolTip::showText(event->globalPos(), subTitle, view, rect);
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
