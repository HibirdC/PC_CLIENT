#include <QDebug>
#include <QPainter>
#include <QHelpEvent>
#include <QToolTip>
#include <QApplication>

#include "TNUnReadListDelegate.h"
#include "TNUnReadMsgAdapter.h"
#include "NetWorkAPI.h"
#include "TNIMCoreClient.h"
#include "tncommondealavator.h"
#include "TNSettingData.h"


#define AVATAR_MARGIN_LEFT 15
#define AVATAR_MARGIN_TOP 5
#define AVATAR_MARGIN_BUTTOM 5

#define TITLE_MARGIN_LEFT 15
#define TITLE_MARGIN_TOP 5

#define NORMAL_MARGIN_LEFT 55
#define NORMAL_MARGIN_TOP 12

#define AVATAR_WIDTH      30
#define AVATAR_HEIGHT      30

#define RED_UNREAD_LEFT   224
#define RED_UNREAD_TOP   12
#define RED_UNREAD_LENGTH 16

#define IGNORE_MARGIN_LEFT 174
#define IGNORE_MARGIN_TOP 10
#define IGNORE_BUTTON_W  60
#define IGNORE_BUTTON_H  20

TNUnReadListDelegate::TNUnReadListDelegate()
	: QStyledItemDelegate()
{
	normalFont = QFont("Microsoft Yahei");
    normalFont.setPixelSize(12);

	countFont = QFont("Microsoft Yahei");
	countFont.setPixelSize(12);

    normalColor = QColor(0x00,0x00,0x00);
	countColor = QColor(0xff,0xff,0xff);
	countBrushC = QColor(0xff, 0x74, 0x46);
}

void TNUnReadListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	TNUnReadMsgAdapter *adapter = (TNUnReadMsgAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return;

	if (index.column() == 0)
	{
		QRect rect = option.rect;

		QPen oldPen = painter->pen();
		QBrush oldBrush = painter->brush();
		QFont oldFont = painter->font();
		QString feedId = adapter->getFromFeedID();

		if (adapter->getType() == TNUnReadMsgAdapter::normal)
		{
			if (option.state & QStyle::State_Selected)
			{
				painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentSelectSkin()));
			}
			else if (option.state & QStyle::State_MouseOver)
			{
				painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentHoverSkin()));
			}

//			painter->setRenderHint(QPainter::Antialiasing, false);
//          painter->setPen(QPen(QColor("#ebedf0")));//画下边框
//			painter->drawLine(rect.x(), rect.y() + LIST_UNREAD_HEIGHT - 1, LIST_UNREAD_WIDTH, rect.y() + LIST_UNREAD_HEIGHT - 1);
            painter->setRenderHint(QPainter::Antialiasing, true);

			painter->setRenderHint(QPainter::SmoothPixmapTransform);
			QString avatarPath = adapter->getFromAvator();
			Cust_Type _type;
			if (feedId.startsWith("c_"))
				_type = Cust_Type::cust_ellipse;
			else if (feedId.startsWith("gc_"))
				_type = Cust_Type::cust_radius;
			else
				_type = Cust_Type::cust_radius;

			if (avatarPath.isEmpty() || !QFile::exists(avatarPath))
			{
				if (latestAvatarMap[feedId].isNull())
				{
					avatarPath = (":/Resources/toolWidget/defaultAvatar.png");
					(const_cast<TNUnReadListDelegate *>(this))->latestAvatarMap.insert(feedId
						, TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), _type));
					latestAvatarMap[feedId].scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
				}
			}
			else
			{
				QPixmap avatar = TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), _type);
				avatar.scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
				(const_cast<TNUnReadListDelegate *>(this))->latestAvatarMap.remove(feedId);
				(const_cast<TNUnReadListDelegate *>(this))->latestAvatarMap.insert(feedId, avatar); //更新新的
			}
			painter->drawPixmap(rect.x() + AVATAR_MARGIN_LEFT, rect.y() + AVATAR_MARGIN_TOP, AVATAR_WIDTH, AVATAR_HEIGHT, latestAvatarMap[feedId]);

			int X = rect.x() + NORMAL_MARGIN_LEFT;
			int Y = rect.y() + NORMAL_MARGIN_TOP + 12;
			painter->setFont(normalFont);
			painter->setPen(QPen(normalColor));

			int textLen = 0;
			QString title = adapter->getFromName();
            title = painter->fontMetrics().elidedText(title, Qt::ElideRight, 130, Qt::TextShowMnemonic);

			painter->drawText(X, Y, title);

			if (!adapter->getNoShowCount())
			{
				int unCount = adapter->getUnReadCount();
				QString decorationText = QString("%1").arg(unCount);
				if (unCount > 99)
					decorationText = ("99+");

				QPen decorationPen(countColor);
				QBrush decorationBrush(countBrushC);
				QFont decorationFont = countFont;
				painter->setFont(decorationFont);

				QRect decoration = option.rect;
				decoration.setHeight(16);
                decoration.moveCenter(option.rect.center());
				if (unCount > 99)
				{
                    decoration.setLeft(option.rect.right() - 38);
                    decoration.setRight(option.rect.right() - 12);
				}
				else
				{
                    decoration.setLeft(option.rect.right() - 30);
                    decoration.setRight(option.rect.right() - 14);
				}

                painter->setPen(decorationPen);
				QPainterPath path;
				path.addRoundedRect(decoration, 7, 10);
				painter->fillPath(path, decorationBrush);
				painter->drawText(decoration, Qt::AlignCenter | Qt::AlignVCenter, decorationText);
			}
			painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
			painter->setFont(oldFont);
			painter->setPen(oldPen);
		}
		/*else
		{
			int titleX = rect.x() + IGNORE_MARGIN_LEFT;
			int titleY = rect.y() + IGNORE_MARGIN_TOP;

			QStyleOptionButton button;
			button.rect = QRect(titleX,
				titleY, IGNORE_BUTTON_W, IGNORE_BUTTON_H);
			button.state |= QStyle::State_Enabled;
			button.text = ("忽略所有");
			if (button.rect.contains(m_mousePoint))
			{
				if (m_nType == 0)
				{
					button.state |= QStyle::State_MouseOver;
				}
				else if (m_nType == 1)
				{
					button.state |= QStyle::State_Sunken;
				}
			}

			QWidget *pWidget = m_pButton.data();
			QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter, pWidget);
		}*/
	}
}

QSize TNUnReadListDelegate::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QVariant value = index.data(Qt::SizeHintRole);
	if (value.isValid())
		return qvariant_cast<QSize>(value);

	TNUnReadMsgAdapter *adapter = (TNUnReadMsgAdapter*)index.data().toLongLong();
	if (adapter == NULL)
		return qvariant_cast<QSize>(value);

	if (adapter->getType() == TNUnReadMsgAdapter::Title)
	{
		return QSize(LIST_UNREAD_WIDTH, LIST_UNREAD_TITLE_HEIGHT);
	}
	else if(adapter->getType() == TNUnReadMsgAdapter::buttom)
	{
		return QSize(LIST_UNREAD_WIDTH, LIST_UNREAD_BUTTOM_HEIGHT);
	}
	else
	{
		return QSize(LIST_UNREAD_WIDTH, LIST_UNREAD_HEIGHT);
	}
}
bool TNUnReadListDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view,
	const QStyleOptionViewItem &option, const QModelIndex &index)
{
	if (!event || !view)
		return false;
	if (event->type() == QEvent::ToolTip) {
		QRect rect = view->visualRect(index);
		QSize size = sizeHint(option, index);
		QPoint pos = event->pos();
		if (rect.contains(pos)) {
			TNUnReadMsgAdapter *adapter = (TNUnReadMsgAdapter*)index.data().toLongLong();
			if (adapter != nullptr && adapter->getType() == TNUnReadMsgAdapter::normal)
			{
				int X = rect.x() + NORMAL_MARGIN_LEFT;
				int Y = rect.y() + NORMAL_MARGIN_TOP;

				int textLen = 0;
				int textHei = 0;
				QFontMetrics fm(view->font());
				QString title = adapter->getFromName();
                title = fm.elidedText(title, Qt::ElideMiddle, 140, Qt::TextShowMnemonic);
				textLen = fm.width(title);
				textHei = fm.height();

				QRect titleRect(X, Y, textLen, textHei);
				QRect myTitleRect;

				
				if (titleRect.contains(pos))
				{
					QToolTip::showText(event->globalPos(), adapter->getFromName(), view, rect);
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
//bool TNUnReadListDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
//{
//	m_nType = -1;
//	bool bRepaint = false;
//	QMouseEvent *pEvent = static_cast<QMouseEvent *> (event);
//	m_mousePoint = pEvent->pos();
//
//	// 还原鼠标样式
//	QApplication::restoreOverrideCursor();
//
//	int titleX = option.rect.x() + IGNORE_MARGIN_LEFT;
//	int titleY = option.rect.y() + IGNORE_MARGIN_TOP;
//
//	QStyleOptionButton button;
//	button.rect = QRect(titleX,
//		titleY, IGNORE_BUTTON_W, IGNORE_BUTTON_H);
//
//	// 鼠标位于按钮之上
//	if (button.rect.contains(m_mousePoint))
//	{
//		bRepaint = true;
//		switch (event->type())
//		{
//			// 鼠标滑过
//			case QEvent::MouseMove:
//			{
//				// 设置鼠标样式为手型
//				QApplication::setOverrideCursor(Qt::PointingHandCursor);
//				m_nType = 0;
//				break;
//			}
//			case QEvent::MouseButtonPress:
//				m_nType = 1;
//				break;
//			case QEvent::MouseButtonRelease:
//				//发送信号
//				emit ignoreAll(index);
//				break;
//			default:
//				break;
//		}
//	}
//	return bRepaint;
//}
