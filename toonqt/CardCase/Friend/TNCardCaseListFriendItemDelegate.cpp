#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QTableView>
#include <QPainter>
#include <QHelpEvent>
#include <QToolTip>

#include "NetWorkAPI.h"
#include "TNNewFriendUtil.h"
#include "TNIMCoreClient.h"
#include "TNCardCaseListAdapter.h"
#include "TNCardCaseListFriendItemDelegate.h"
#include "tncommondealavator.h"
#include "TNSettingData.h"


#define AVATAR_MARGIN_LEFT 15
#define AVATAR_MARGIN_RIGHT 10
#define AVATAR_MARGIN_TOP 15
#define AVATAR_MARGIN_BUTTOM 15

#define TITLE_MARGIN_LEFT 65
#define TITLE_MARGIN_TOP 19

#define TAG_MARGIN_LEFT 15
#define TAG_MARGIN_TOP 19

#define NEW_MARGIN_LEFT 65
#define NEW_MARGIN_TOP 28

#define SUBTITLE_MARGIN_LEFT 65
#define SUBTITLE_MARGIN_TOP 39

#define AVATAR_WIDTH      40
#define AVATAR_HEIGHT      40

#define RED_UNREAD_LEFT   44
#define RED_UNREAD_TOP   15
#define RED_UNREAD_LENGTH 16

TNCardCaseListFriendItemDelegate::TNCardCaseListFriendItemDelegate()
{
	titleFont = QFont("Microsoft Yahei");
    titleFont.setPixelSize(13);
	subTitleFont = QFont("Microsoft Yahei");
	subTitleFont.setPixelSize(12);
	subTitleColor = QColor("#5D677D");
	tagFont = QFont("Microsoft Yahei");
    tagFont.setPixelSize(13);
	newFriendFont = QFont("Microsoft Yahei");
    newFriendFont.setPixelSize(13);
}

void TNCardCaseListFriendItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	TNCardCaseListAdapter *adapter = (TNCardCaseListAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return;

	if (index.column() == 0)
	{
		QRect rect = option.rect;
		QPen oldPen = painter->pen();
		QBrush oldBrush = painter->brush();
		QFont oldFont = painter->font();
		QString feedId = adapter->getDialogID();

		if (adapter->getType() == TNCardCaseListAdapter::FriendLetter)
		{
			int tagX = rect.x() + TAG_MARGIN_LEFT;
			int tagY = rect.y() + TAG_MARGIN_TOP;

			painter->setFont(tagFont);
			painter->drawText(tagX, tagY, adapter->getName());

			painter->setFont(oldFont);
		}
		else if (adapter->getType() == TNCardCaseListAdapter::FriendItem)
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
			QString avatarPath = adapter->getPhotoResID();
			Cust_Type _type;
			bool isMyInfo = adapter->getIsShowMyInfo();
			if (feedId.startsWith("c_"))
				_type = Cust_Type::cust_ellipse;
			else
				_type = Cust_Type::cust_radius;

			if (avatarPath.isEmpty() || !QFile::exists(avatarPath))
			{
				if (latestAvatarMap[feedId].isNull())
				{
					avatarPath = (":/Resources/toolWidget/defaultAvatar.png");
					(const_cast<TNCardCaseListFriendItemDelegate *>(this))->latestAvatarMap.insert(feedId
						, TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), _type));
					latestAvatarMap[feedId].scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
				}
				emit downLoadAvatar(feedId, adapter->getAvatarUrl(), 0);
			}
			else
			{
				QPixmap avatar = TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), _type);
				avatar.scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
				(const_cast<TNCardCaseListFriendItemDelegate *>(this))->latestAvatarMap.remove(feedId);
				(const_cast<TNCardCaseListFriendItemDelegate *>(this))->latestAvatarMap.insert(feedId, avatar); //更新新的
			}
			painter->drawPixmap(rect.x() + AVATAR_MARGIN_LEFT, rect.y() + AVATAR_MARGIN_TOP, AVATAR_WIDTH, AVATAR_HEIGHT, latestAvatarMap[feedId]);

			int titleX = rect.x() + TITLE_MARGIN_LEFT;
			int titleY = rect.y() + TITLE_MARGIN_TOP+10;
			painter->setFont(titleFont);

			int textLen = 0;
			QString title = adapter->getName();
			if (isMyInfo)
			{
				title = painter->fontMetrics().elidedText(title, Qt::ElideMiddle, 100, Qt::TextShowMnemonic);
				textLen = painter->fontMetrics().width(title);
			}
			else
				title = painter->fontMetrics().elidedText(title, Qt::ElideMiddle, 170, Qt::TextShowMnemonic);
			
			painter->drawText(titleX, titleY, title);

			if (isMyInfo)
			{
				//绘制多好友标识
				QString	flagPath = (":/Resources/toolWidget/exchange-icon.png");
				QPixmap img(flagPath);
				painter->drawPixmap(titleX + textLen+5, titleY-10, 10, 10, img);
				painter->setPen(subTitleColor);
				int myX = titleX + textLen+20;
				int myY = titleY;
				painter->setFont(subTitleFont);
				//预留25个像素的边
				QString myTitle = painter->fontMetrics().elidedText(adapter->getMyTitle(),
					Qt::ElideMiddle, 170 - textLen-25, Qt::TextShowMnemonic);
				painter->drawText(myX, myY, myTitle);
			}

			painter->setPen(subTitleColor);
			int subX = rect.x()+SUBTITLE_MARGIN_LEFT;
			int subY = rect.y()+SUBTITLE_MARGIN_TOP + 10;
			painter->setFont(subTitleFont);
			QString subTitle = painter->fontMetrics().elidedText(adapter->getSubTitle(), 
				Qt::ElideMiddle, 170, Qt::TextShowMnemonic);
			painter->drawText(subX, subY, subTitle);

			painter->setRenderHint(QPainter::SmoothPixmapTransform,false);
			painter->setFont(oldFont);
			painter->setPen(oldPen);
		}
		else
		{
			if (option.state & QStyle::State_Selected)
			{
				painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentSelectSkin()));
			}
			else if (option.state & QStyle::State_MouseOver)
			{
				painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentHoverSkin()));
			}

			QString avatarPath = adapter->getPhotoResID();
			if (avatarPath.isEmpty())
				avatarPath = (":/Resources/new_friend.png");
			QPixmap avatar = QPixmap(avatarPath);
			painter->drawPixmap(rect.x() + AVATAR_MARGIN_LEFT, rect.y() + AVATAR_MARGIN_TOP, AVATAR_WIDTH, AVATAR_HEIGHT, avatar);

			int X = rect.x() + NEW_MARGIN_LEFT;
			int Y = rect.y() + NEW_MARGIN_TOP+12;
			painter->setFont(newFriendFont);
			painter->drawText(X, Y, adapter->getName());

			//绘制红点
			int unCount = adapter->getNewFriendUnRead();
			if (unCount > 0)
			{
				QColor color(0xFF,0x74,0x45);
				QColor colorFont(0xFF, 0xFF, 0xFF);
				QString decorationText = QString("%1").arg(unCount);
				if (unCount > 99)
					decorationText = ("99+");
				int circleWidth = RED_UNREAD_LENGTH + (decorationText.length()-1)*5;

				QPen decorationPen(colorFont);
				QBrush decorationBrush(color);
				QFont decorationFont = subTitleFont;
				painter->setFont(decorationFont);

				QRect decoration(RED_UNREAD_LEFT, RED_UNREAD_TOP, circleWidth, RED_UNREAD_LENGTH);

				painter->setPen(decorationPen);
				QPainterPath path;
				path.addRoundedRect(decoration, 7, 10);
				painter->fillPath(path, decorationBrush);
				painter->drawText(decoration, Qt::AlignCenter | Qt::AlignVCenter, decorationText);
				
				painter->setPen(oldPen);
				painter->setBrush(oldBrush);//设置画刷形式
			}
			painter->setFont(oldFont);
		}
	}
}

QSize TNCardCaseListFriendItemDelegate::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QVariant value = index.data(Qt::SizeHintRole);
	if (value.isValid())
		return qvariant_cast<QSize>(value);

	TNCardCaseListAdapter *adapter = (TNCardCaseListAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return qvariant_cast<QSize>(value);

	if (adapter->getType() == TNCardCaseListAdapter::FriendLetter)
	{
		return QSize(LIST_AREA_WIDTH, LIST_TAG_HEIGHT);
	}
	else
	{
		return QSize(LIST_AREA_WIDTH, LIST_AREA_HEIGHT);
	}
}
bool TNCardCaseListFriendItemDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view,
	const QStyleOptionViewItem &option, const QModelIndex &index)
{
	if (!event || !view)
		return false;

	if (event->type() == QEvent::ToolTip) {
		QRect rect = view->visualRect(index);
		QSize size = sizeHint(option, index);
		QPoint pos = event->pos();
		if (rect.contains(pos)) {
			TNCardCaseListAdapter *adapter = (TNCardCaseListAdapter*)index.data().toLongLong();
			if (adapter != nullptr && adapter->getType() == TNCardCaseListAdapter::FriendItem)
			{
				int titleX = rect.x() + TITLE_MARGIN_LEFT;
				int titleY = rect.y() + TITLE_MARGIN_TOP;

				int textLen = 0;
				int textHei = 0;
				QFontMetrics fm(view->font());
				QString title = adapter->getName();
				bool isMyInfo = adapter->getIsShowMyInfo();
				if (isMyInfo)
				{
					title = fm.elidedText(title, Qt::ElideMiddle, 100, Qt::TextShowMnemonic);
				}
				else
				{
					title = fm.elidedText(title, Qt::ElideMiddle, 170, Qt::TextShowMnemonic);
				}
				textLen = fm.width(title);
				textHei = fm.height();

				QRect titleRect(titleX, titleY,textLen,textHei);
				QRect myTitleRect;

				if (isMyInfo)
				{
					int myX = titleX + textLen + 20;
					int myY = titleY;
					QString myTitle = fm.elidedText(adapter->getMyTitle(),
						Qt::ElideMiddle, 170 - textLen, Qt::TextShowMnemonic);

					textLen = fm.width(myTitle);
					textHei = fm.height();

					myTitleRect = QRect(myX, myY, textLen, textHei);
				}

				int subX = rect.x() + SUBTITLE_MARGIN_LEFT;
				int subY = rect.y() + SUBTITLE_MARGIN_TOP;
				QString subTitle = fm.elidedText(adapter->getSubTitle(),
					Qt::ElideMiddle, 170, Qt::TextShowMnemonic);

				textLen = fm.width(subTitle);
				textHei = fm.height();

				QRect subTitleRect(subX, subY, textLen, textHei);


				if (titleRect.contains(pos))
				{
					QToolTip::showText(event->globalPos(), adapter->getName(), view, rect);
				}
				else if (myTitleRect.contains(pos))
				{
					QToolTip::showText(event->globalPos(), adapter->getMyTitle(), view, rect);
				}
				else if (subTitleRect.contains(pos))
				{
					QToolTip::showText(event->globalPos(), adapter->getSubTitle(), view, rect);
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
