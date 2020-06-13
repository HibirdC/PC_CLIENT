#include "TNSearchListItemDelegateV2.h"
#include "tncommondealavator.h"
#include "TNSettingData.h"

#include <QPainter>
#include <QHelpEvent>
#include <QToolTip>
#include <QAbstractItemView>
#include <QApplication>
#include <QDebug>

#define SEARCH_ITEM_WIDTH                          250
#define SEARCH_ITEM_HEIGHT                         50
#define SEARCH_TYPE_WIDTH                          250
#define SEARCH_TYPE_HEIGHT                         24

#define SEARCH_SHOW_COUNT                          3

#define SEARCHTYPELINE_MARGIN_LEFT                 15
#define SEARCHTYPELINE_MARGIN_TOP                  6
#define SEARCHTYPELINE_WIDTH                       2
#define SEARCHTYPELINE_HEIGHT                      14

#define SHOWALL_MARGIN_LEFT                        187
#define SHOWALL_MARGIN_TOP                         2
#define SHOWALL_BUTTON_W                           48
#define SHOWALL_BUTTON_H                           20

#define Friend                                     1
#define Colleague                                  2
#define Group                                      3
#define GroupChat                                  4
#define NotityMsg                                  5

#define AVATAR_WIDTH                               30
#define AVATAR_HEIGHT                              30

#define MY_AVATAR_WIDTH                            20
#define MY_AVATAR_HEIGHT                           20

#define AVATAR_MARGIN_LEFT                         15
#define AVATAR_MARGIN_TOP                          10

#define MYAVATAR_MARGIN_LEFT                       210
#define MYAVATAR_MARGIN_TOP                        15

#define TITLE_MARGIN_LEFT                          55
#define TITLE_MARGIN_TOP                           12

#define NICK_MARGIN_LEFT                           55
#define NICK_MARGIN_TOP                            30

#define ELIDEFLAG                                  QStringLiteral("…")

#define ELIDE_LENGTH                               150
#define ELIDE_LENGTH_NOAVATAR                      160

TNSearchListItemDelegateV2::TNSearchListItemDelegateV2()
	: m_pButton(new QPushButton())
	, m_currentType(0)
{
	nameFont = QFont("Microsoft Yahei");
	nameFont.setPixelSize(12);
	nickFont = QFont("Microsoft Yahei");
	nickFont.setPixelSize(12);
	nickColor = QColor("#5D677D");
	nameColor = QColor("#000000");

	tagFont = QFont("Microsoft Yahei");
	tagFont.setPixelSize(14);
	tagColor = QColor("#858FA4");

	m_pButton->setObjectName("searchShowAllButton");
}

TNSearchListItemDelegateV2::~TNSearchListItemDelegateV2()
{

}
void TNSearchListItemDelegateV2::paintTag(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index, TNSearchTreeItemV2 *item) const
{
	Q_ASSERT(item != nullptr);

	QRect rect = option.rect;
	QPen oldPen = painter->pen();
	QBrush oldBrush = painter->brush();
	QFont oldFont = painter->font();

	bool showAll = item->getItemCount() > SEARCH_SHOW_COUNT ? true : false;
	QString data = item->data(0).toString();
	QString name;
	if (data == "AFriend")
	{
		(const_cast<TNSearchListItemDelegateV2 *>(this))->m_currentType = Friend;
		if (!m_ButtonStaus.contains(Friend))
			(const_cast<TNSearchListItemDelegateV2 *>(this))->m_ButtonStaus.insert(Friend, false);
		name = tr(QStringLiteral("好友").toUtf8().data());
	}
	else if (data == "BColleague")
	{
		(const_cast<TNSearchListItemDelegateV2 *>(this))->m_currentType = Colleague;
		if (!m_ButtonStaus.contains(Colleague))
			(const_cast<TNSearchListItemDelegateV2 *>(this))->m_ButtonStaus.insert(Colleague, false);
		name = tr(QStringLiteral("同事").toUtf8().data());
	}
	else if (data == "CGroup")
	{
		(const_cast<TNSearchListItemDelegateV2 *>(this))->m_currentType = Group;
		if (!m_ButtonStaus.contains(Group))
			(const_cast<TNSearchListItemDelegateV2 *>(this))->m_ButtonStaus.insert(Group, false);
		name = tr(QStringLiteral("社区").toUtf8().data());
	}
	else if (data == "DGroupChat")
	{
		(const_cast<TNSearchListItemDelegateV2 *>(this))->m_currentType = GroupChat;
		if (!m_ButtonStaus.contains(GroupChat))
			(const_cast<TNSearchListItemDelegateV2 *>(this))->m_ButtonStaus.insert(GroupChat, false);
		name = tr(QStringLiteral("群聊").toUtf8().data());
	}
	else if (data == "ENotifyMsg")
	{
		(const_cast<TNSearchListItemDelegateV2 *>(this))->m_currentType = NotityMsg;
		if (!m_ButtonStaus.contains(NotityMsg))
			(const_cast<TNSearchListItemDelegateV2 *>(this))->m_ButtonStaus.insert(NotityMsg, false);
		name = tr(QStringLiteral("消息通知").toUtf8().data());
	}
	painter->setRenderHint(QPainter::Antialiasing);
	QPen linePen(QColor(TNSettingData::instance()->GetCurrentThemeSkin()), SEARCHTYPELINE_WIDTH);
	QString text = item->data(0).toString();
	painter->setPen(linePen);
	painter->drawLine(rect.x() + SEARCHTYPELINE_MARGIN_LEFT, rect.y() + SEARCHTYPELINE_MARGIN_TOP, rect.x() + SEARCHTYPELINE_MARGIN_LEFT, rect.y() + SEARCHTYPELINE_MARGIN_TOP + SEARCHTYPELINE_HEIGHT);
	painter->setRenderHint(QPainter::Antialiasing, false);

	painter->setPen(tagColor);
	painter->setFont(tagFont);
	QRect Rect = rect;
	Rect.setLeft(SEARCHTYPELINE_MARGIN_LEFT + 7);
	painter->drawText(Rect, Qt::AlignLeft | Qt::AlignVCenter, name);
	painter->setPen(oldPen);
	painter->setFont(oldFont);

	int btnX = rect.x() + SHOWALL_MARGIN_LEFT;
	int btnY = rect.y() + SHOWALL_MARGIN_TOP;

	if (showAll)
	{
		QStyleOptionButton button;
		button.rect = QRect(btnX,
			btnY, SHOWALL_BUTTON_W, SHOWALL_BUTTON_H);
		button.state |= QStyle::State_Enabled;
		if (m_ButtonStaus[m_currentType] == false)
			button.text = tr(QStringLiteral("显示所有").toUtf8().data());
		else
			button.text = tr(QStringLiteral("收起").toUtf8().data());

		if (!m_ButtonMap.contains(index))
		{
			(const_cast<TNSearchListItemDelegateV2 *>(this))->m_ButtonMap.insert(index, m_currentType);
		}
		QWidget *pWidget = m_pButton.data();
		QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter, pWidget);
	}
	painter->setFont(oldFont);
	painter->setPen(oldPen);
	painter->setBrush(oldBrush);
}
void TNSearchListItemDelegateV2::paintFriendItem(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index, TNSearchNameItem *item) const
{
	Q_ASSERT(item != nullptr);

	QRect rect = option.rect;
	QPen oldPen = painter->pen();
	QBrush oldBrush = painter->brush();
	QFont oldFont = painter->font();

	QString nick = item->getNickName();
	int nickX = rect.x() + NICK_MARGIN_LEFT;
	int nickY = rect.y() + NICK_MARGIN_TOP + 10;
	int titleX = rect.x() + TITLE_MARGIN_LEFT;
	int titleY = rect.y() + TITLE_MARGIN_TOP + 10;
	painter->setFont(nameFont);
	painter->setPen(nameColor);

	if (nick.isEmpty())
	{
		titleY += 8;

		QString right,left,hit;
		QString title = item->getTitle();
		int keyIndex = -1;
		QString elidTitle = painter->fontMetrics().elidedText(title, Qt::ElideRight, ELIDE_LENGTH, Qt::TextShowMnemonic);
		keyIndex = elidTitle.indexOf(item->getSearchHitKey());
		if (keyIndex == -1)
		{
			hit = ELIDEFLAG;
			left = elidTitle.left(elidTitle.indexOf(hit));
		}
		else
		{
			left = elidTitle.left(keyIndex);
			hit = item->getSearchHitKey();
			right = elidTitle.right(elidTitle.length() -
				keyIndex - hit.length());
		}
		int leftLen = painter->fontMetrics().width(left);
		int hitLen = painter->fontMetrics().width(hit);

		painter->drawText(titleX, titleY, left);
		painter->setPen(keyColor);
		painter->drawText(titleX + leftLen, titleY,hit);
		painter->setPen(nameColor);
		if (!right.isEmpty())
		{
			painter->drawText(titleX + leftLen + hitLen, titleY, right);
		}
	}
	else
	{
		QString title = item->getTitle();
		title = painter->fontMetrics().elidedText(title, Qt::ElideRight, ELIDE_LENGTH, Qt::TextShowMnemonic);
		painter->drawText(titleX, titleY, title);
		//在昵称当中hit
		nick = tr(QStringLiteral("昵称：").toUtf8().data()) + nick;
		int keyIndex = -1;
		QString left, hit, right;
		QString	elideNick = painter->fontMetrics().elidedText(nick, Qt::ElideRight, ELIDE_LENGTH, Qt::TextShowMnemonic);
		painter->setFont(nickFont);
		painter->setPen(nickColor);

		keyIndex = elideNick.indexOf(item->getSearchHitKey());
		if (keyIndex == -1)
		{
			hit = ELIDEFLAG;
			left = elideNick.left(elideNick.indexOf(hit));
		}
		else
		{
			left = elideNick.left(keyIndex);
			hit = item->getSearchHitKey();
			right = elideNick.right(elideNick.length() - keyIndex - hit.length());
		}

		int leftLen = painter->fontMetrics().width(left);
		int hitLen  = painter->fontMetrics().width(hit);

		painter->drawText(nickX, nickY, left);
		painter->setPen(keyColor);
		painter->drawText(nickX + leftLen, nickY, hit);
		painter->setPen(nickColor);
		if (!right.isEmpty())
		{
			painter->drawText(nickX + leftLen + hitLen, nickY, right);
		}
	}
	if (item->getShowBelongStatus())
		paintMyAvator(painter, option, index, item);
	painter->setFont(oldFont);
	painter->setPen(oldPen);
	painter->setBrush(oldBrush);
}
void TNSearchListItemDelegateV2::paintTargetAvator(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index, TNSearchNameItem *item) const
{
	Q_ASSERT(item != nullptr);
	QRect rect = option.rect;

	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	QString avatarPath = item->getPhotoResourceID();
	Cust_Type _type;
	if (item->getFeedID().startsWith("c_"))
		_type = Cust_Type::cust_ellipse;
	else if (item->getFeedID().startsWith("g_"))
		_type = Cust_Type::cust_hexagon;
	else if (item->getFeedID().startsWith("gc_"))
		_type = Cust_Type::cust_radius;
	else
		_type = Cust_Type::cust_radius;

	if (avatarPath.isEmpty() || !QFile::exists(avatarPath))
	{
		avatarPath = (":/Resources/toolWidget/defaultAvatar.png");
		emit downLoadAvatar(item->getFeedID(), item->getAvatarURL(), 0);
	}
	QPixmap avatar = TNCommonDealAvator::getTypeQPixmap(avatarPath, QSize(80, 80), _type);
	avatar.scaled(AVATAR_WIDTH, AVATAR_HEIGHT, Qt::KeepAspectRatio);
	painter->drawPixmap(rect.x() + AVATAR_MARGIN_LEFT, rect.y() + AVATAR_MARGIN_TOP, AVATAR_WIDTH, AVATAR_HEIGHT, avatar);
	painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
}
void TNSearchListItemDelegateV2::paintMyAvator(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index, TNSearchNameItem *item) const
{
	Q_ASSERT(item != nullptr);
	QRect rect = option.rect;

	painter->setRenderHint(QPainter::SmoothPixmapTransform);
	QString myAvatarPath = item->getBelongPhotoResID();
	Cust_Type _type;
	if (item->getBelongFeedId().startsWith("c_"))
		_type = Cust_Type::cust_ellipse;
	else
		_type = Cust_Type::cust_radius;

	if (myAvatarPath.isEmpty() || !QFile::exists(myAvatarPath))
	{
		myAvatarPath = (":/Resources/toolWidget/defaultAvatar.png");
	}
	QPixmap myAvatar = TNCommonDealAvator::getTypeQPixmap(myAvatarPath, QSize(80, 80), _type);
	myAvatar.scaled(MY_AVATAR_WIDTH, MY_AVATAR_HEIGHT, Qt::KeepAspectRatio);
	painter->drawPixmap(rect.x() + MYAVATAR_MARGIN_LEFT, rect.y() + MYAVATAR_MARGIN_TOP, MY_AVATAR_WIDTH, MY_AVATAR_HEIGHT, myAvatar);
	painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
}
void TNSearchListItemDelegateV2::paintColleagueItem(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index, TNSearchNameItem *item) const
{
	Q_ASSERT(item != nullptr);

	QRect rect = option.rect;
	QPen oldPen = painter->pen();
	QBrush oldBrush = painter->brush();
	QFont oldFont = painter->font();

	int titleX = rect.x() + TITLE_MARGIN_LEFT;
	int titleY = rect.y() + TITLE_MARGIN_TOP + 18;
	painter->setFont(nameFont);
	painter->setPen(nameColor);

	QString left, hit, right;
	QString title = item->getTitle();
	int keyIndex = -1;
	QString elidTitle = painter->fontMetrics().elidedText(title, Qt::ElideRight, ELIDE_LENGTH, Qt::TextShowMnemonic);

	keyIndex = elidTitle.indexOf(item->getSearchHitKey());
	if (keyIndex == -1)
	{
		hit = ELIDEFLAG;
		left = elidTitle.left(elidTitle.indexOf(hit));
	}
	else
	{
		hit = item->getSearchHitKey();
		right = elidTitle.right(elidTitle.length() -
			keyIndex - hit.length());
		left = elidTitle.left(keyIndex);
	}
	int leftLen = painter->fontMetrics().width(left);
	int hitLen = painter->fontMetrics().width(hit);

	painter->drawText(titleX, titleY, left);
	painter->setPen(keyColor);
	painter->drawText(titleX + leftLen, titleY, hit);
	painter->setPen(nameColor);
	if (!right.isEmpty())
	{
		painter->drawText(titleX + leftLen + hitLen, titleY, right);
	}
	if (item->getShowBelongStatus())
		paintMyAvator(painter, option, index, item);
	painter->setFont(oldFont);
	painter->setPen(oldPen);
	painter->setBrush(oldBrush);
}
void TNSearchListItemDelegateV2::paintGroupItem(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index, TNSearchNameItem *item) const
{
	Q_ASSERT(item != nullptr);

	QRect rect = option.rect;
	QPen oldPen = painter->pen();
	QBrush oldBrush = painter->brush();
	QFont oldFont = painter->font();

	int titleX = rect.x() + TITLE_MARGIN_LEFT;
	int titleY = rect.y() + TITLE_MARGIN_TOP + 18;
	painter->setFont(nameFont);
	painter->setPen(nameColor);

	QString left, hit, right;
	QString title = item->getTitle();
	int keyIndex = -1;
	QString elidTitle = painter->fontMetrics().elidedText(title, Qt::ElideRight, ELIDE_LENGTH_NOAVATAR, Qt::TextShowMnemonic);
	keyIndex = elidTitle.indexOf(item->getSearchHitKey());
	if (keyIndex == -1)
	{
		hit = ELIDEFLAG;
		left = elidTitle.left(elidTitle.indexOf(hit));
	}
	else
	{
		hit = item->getSearchHitKey();
		right = elidTitle.right(elidTitle.length() -
			keyIndex - hit.length());
		left = elidTitle.left(keyIndex);
	}

	int leftLen = painter->fontMetrics().width(left);
	int hitLen = painter->fontMetrics().width(hit);

	painter->drawText(titleX, titleY, left);
	painter->setPen(keyColor);
	painter->drawText(titleX + leftLen, titleY, hit);
	painter->setPen(nameColor);
	if (!right.isEmpty())
	{
		painter->drawText(titleX + leftLen + hitLen, titleY, right);
	}
	painter->setFont(oldFont);
	painter->setPen(oldPen);
	painter->setBrush(oldBrush);
}
void TNSearchListItemDelegateV2::paintGroupChatItem(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index, TNSearchNameItem *item) const
{
	Q_ASSERT(item != nullptr);

	QRect rect = option.rect;
	QPen oldPen = painter->pen();
	QBrush oldBrush = painter->brush();
	QFont oldFont = painter->font();

	QString nick = item->getNickName();
	int nickX = rect.x() + NICK_MARGIN_LEFT;
	int nickY = rect.y() + NICK_MARGIN_TOP + 10;

	int titleX = rect.x() + TITLE_MARGIN_LEFT;
	int titleY = rect.y() + TITLE_MARGIN_TOP + 10;
	painter->setFont(nameFont);
	painter->setPen(nameColor);

	if (nick.isEmpty())
	{
		titleY += 8;
		QString left,hit,right;
		QString title = item->getTitle();
		int keyIndex = -1;
		QString elidTitle = painter->fontMetrics().elidedText(title, Qt::ElideRight, ELIDE_LENGTH_NOAVATAR, Qt::TextShowMnemonic);
		keyIndex = elidTitle.indexOf(item->getSearchHitKey());
		if (keyIndex == -1)
		{
			hit = ELIDEFLAG;
			left = elidTitle.left(elidTitle.indexOf(hit));
		}
		else
		{
			hit = item->getSearchHitKey();
			left = elidTitle.left(keyIndex);
			right = elidTitle.right(elidTitle.length() -
				keyIndex - hit.length());
		}
		int leftLen = painter->fontMetrics().width(left);
		int hitLen = painter->fontMetrics().width(hit);

		painter->drawText(titleX, titleY, left);
		painter->setPen(keyColor);
		painter->drawText(titleX + leftLen, titleY, hit);
		painter->setPen(nameColor);
		if (!right.isEmpty())
		{
			painter->drawText(titleX + leftLen + hitLen, titleY, right);
		}
	}
	else
	{
		QString left, hit, right;
		QString title = item->getTitle();
		title = painter->fontMetrics().elidedText(title, Qt::ElideRight, ELIDE_LENGTH_NOAVATAR, Qt::TextShowMnemonic);
		painter->drawText(titleX, titleY, title);
		//在昵称当中hit
		nick = tr(QStringLiteral("包含：").toUtf8().data()) + nick;
		int keyIndex = -1;
		QString elideNick = painter->fontMetrics().elidedText(nick, Qt::ElideRight, ELIDE_LENGTH_NOAVATAR, Qt::TextShowMnemonic);
		painter->setFont(nickFont);
		painter->setPen(nickColor);

		keyIndex = elideNick.indexOf(item->getSearchHitKey());
		if (keyIndex == -1)
		{
			hit = ELIDEFLAG;
			left = elideNick.left(elideNick.indexOf(hit));
		}
		else
		{
			hit = item->getSearchHitKey();
			left = elideNick.left(keyIndex);
			right = elideNick.right(elideNick.length() - keyIndex - hit.length());
		}

		int leftLen = painter->fontMetrics().width(left);
		int hitLen = painter->fontMetrics().width(hit);

		painter->drawText(nickX, nickY, left);
		painter->setPen(keyColor);
		painter->drawText(nickX + leftLen, nickY, hit);
		painter->setPen(nickColor);
		if (!right.isEmpty())
		{
			painter->drawText(nickX + leftLen + hitLen, nickY, right);
		}
	}
}
void TNSearchListItemDelegateV2::paintNotifyItem(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index, TNSearchNameItem *item) const
{
	Q_ASSERT(item != nullptr);

	QRect rect = option.rect;
	QPen oldPen = painter->pen();
	QBrush oldBrush = painter->brush();
	QFont oldFont = painter->font();

	QString left, hit, right;
	int titleX = rect.x() + TITLE_MARGIN_LEFT;
	int titleY = rect.y() + TITLE_MARGIN_TOP + 18;
	painter->setFont(nameFont);
	painter->setPen(nameColor);

	QString title = item->getTitle();
	int keyIndex = -1;
	QString	elidTitle = painter->fontMetrics().elidedText(title, Qt::ElideRight, ELIDE_LENGTH_NOAVATAR, Qt::TextShowMnemonic);

	keyIndex = elidTitle.indexOf(item->getSearchHitKey());
	if (keyIndex == -1)
	{
		hit = ELIDEFLAG;
		left = elidTitle.left(elidTitle.indexOf(hit));
	}
	else
	{
		hit = item->getSearchHitKey();
		left = elidTitle.left(keyIndex);
		right = elidTitle.right(elidTitle.length() -
			keyIndex - hit.length());
	}
	int leftLen = painter->fontMetrics().width(left);
	int hitLen = painter->fontMetrics().width(hit);

	painter->drawText(titleX, titleY, left);
	painter->setPen(keyColor);
	painter->drawText(titleX + leftLen, titleY, hit);
	painter->setPen(nameColor);
	if (!right.isEmpty())
	{
		painter->drawText(titleX + leftLen + hitLen, titleY, right);
	}
	painter->setFont(oldFont);
	painter->setPen(oldPen);
	painter->setBrush(oldBrush);
}
void TNSearchListItemDelegateV2::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	TNSearchTreeItemV2 *item = static_cast<TNSearchTreeItemV2*>(index.internalPointer());
	if (item != nullptr){
		if (item->getItemGrade() == TNSearchTreeItemV2::Type){
			paintTag(painter, option, index, item);
		}
		else if (item->getItemGrade() == TNSearchTreeItemV2::Name){
			if (option.state & QStyle::State_Selected){
				painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentSelectSkin()));
			}
			else if (option.state & QStyle::State_MouseOver){
				painter->fillRect(option.rect, QColor(TNSettingData::instance()->GetCurrentHoverSkin()));
			}
			TNSearchNameItem *nameItem = static_cast<TNSearchNameItem*>(item);
			if (nameItem != nullptr){
				(const_cast<TNSearchListItemDelegateV2 *>(this))->keyColor
					= QColor(TNSettingData::instance()->GetCurrentThemeSkin());

				paintTargetAvator(painter, option, index, nameItem);
				if (nameItem->getType() == TNSearchNameItem::FriendItem){
					paintFriendItem(painter, option, index, nameItem);
				}
				else if (nameItem->getType() == TNSearchNameItem::ColleagueItem){
					paintColleagueItem(painter, option, index, nameItem);
				}
				else if (nameItem->getType() == TNSearchNameItem::GroupItem){
					paintGroupItem(painter, option, index, nameItem);
				}
				else if (nameItem->getType() == TNSearchNameItem::GroupChatItem){
					paintGroupChatItem(painter, option, index, nameItem);
				}
				else if (nameItem->getType() == TNSearchNameItem::NotifyItem){
					paintNotifyItem(painter, option, index, nameItem);
				}
			}
		}
	}
}
QSize TNSearchListItemDelegateV2::sizeHint(const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	QVariant value = index.data(Qt::SizeHintRole);
	TNSearchTreeItemV2 *item = static_cast<TNSearchTreeItemV2*>(index.internalPointer());
	if (value.isValid() || item == nullptr)
		return qvariant_cast<QSize>(value);
	if (item->getItemGrade() == TNSearchTreeItemV2::Type)
	{
		return QSize(SEARCH_TYPE_WIDTH, SEARCH_TYPE_HEIGHT);
	}
	else if (item->getItemGrade() == TNSearchTreeItemV2::Name)
	{
		return QSize(SEARCH_ITEM_WIDTH, SEARCH_ITEM_HEIGHT);
	}
	return QSize(0,0);
}
//void TNSearchListItemDelegateV2::paintFriendToolTip(QHelpEvent *event, QAbstractItemView *view,
//	const QStyleOptionViewItem &option, const QModelIndex &index, TNSearchNameItem *item)
//{
//	Q_ASSERT(item != nullptr);
//	if (item->getType() == TNSearchNameItem::FriendItem ||
//		item->getType() == TNSearchNameItem::GroupChatItem)
//	{
//		QRect rect = view->visualRect(index);
//		QSize size = sizeHint(option, index);
//		QPoint pos = event->pos();
//
//		int textLen = 0, textHei = 0;
//		int nickTextLen = 0, nickTextHei = 0;
//		QRect titleRect, nickRect;
//		QString title,nick;
//
//		QFontMetrics fm(view->font());
//		nick = item->getNickName();
//		int nickX = rect.x() + NICK_MARGIN_LEFT;
//		int nickY = rect.y() + NICK_MARGIN_TOP;
//		int titleX = rect.x() + TITLE_MARGIN_LEFT;
//		int titleY = rect.y() + TITLE_MARGIN_TOP;
//
//		if (nick.isEmpty())
//		{
//			titleY += 8;
//			QString right, left, hit;
//			title = item->getTitle();
//			QString elidTitle = fm.elidedText(title, Qt::ElideRight, ELIDE_LENGTH, Qt::TextShowMnemonic);
//			textLen = fm.width(elidTitle);
//			textHei = fm.height();
//			titleRect = QRect(titleX, titleY, textLen, textHei);
//		}
//		else
//		{
//			QString elidTitle;
//			title = item->getTitle();
//			elidTitle = fm.elidedText(title, Qt::ElideRight, ELIDE_LENGTH, Qt::TextShowMnemonic);
//			textLen = fm.width(elidTitle);
//			textHei = fm.height();
//			titleRect = QRect(titleX, titleY, textLen, textHei);
//			//在昵称当中hit
//			nick = tr(QStringLiteral("昵称：").toUtf8().data()) + nick;
//			QString	elideNick = fm.elidedText(nick, Qt::ElideRight, ELIDE_LENGTH, Qt::TextShowMnemonic);
//			nickTextLen = fm.width(elideNick);
//			nickTextHei = fm.height();
//			nickRect = QRect(nickX, nickY, nickTextLen, nickTextHei);
//		}
//		if (titleRect.contains(pos))
//		{
//			QToolTip::showText(event->globalPos(), title, view, rect);
//		}
//		else if (nickRect.contains(pos))
//		{
//			nick = nick.right(nick.length()-3);
//			QToolTip::showText(event->globalPos(), nick, view, rect);
//		}
//		else
//			QToolTip::hideText();
//	}
//}
//void TNSearchListItemDelegateV2::paintColleagueToolTip(QHelpEvent *event, QAbstractItemView *view,
//	const QStyleOptionViewItem &option, const QModelIndex &index, TNSearchNameItem *item)
//{
//	Q_ASSERT(item != nullptr);
//
//	if (item->getType() == TNSearchNameItem::ColleagueItem ||
//		item->getType() == TNSearchNameItem::GroupItem ||
//		item->getType() == TNSearchNameItem::NotifyItem)
//	{
//		QRect rect = view->visualRect(index);
//		QSize size = sizeHint(option, index);
//		QPoint pos = event->pos();
//
//		int textLen = 0, textHei = 0;
//		QRect titleRect;
//		QString title;
//
//		QFontMetrics fm(view->font());
//		int titleX = rect.x() + TITLE_MARGIN_LEFT;
//		int titleY = rect.y() + TITLE_MARGIN_TOP;
//
//		title = item->getTitle();
//		QString elidTitle = fm.elidedText(title, Qt::ElideRight, ELIDE_LENGTH, Qt::TextShowMnemonic);
//		textLen = fm.width(elidTitle);
//		textHei = fm.height();
//
//		titleRect = QRect(titleX, titleY, textLen, textHei);
//		if (titleRect.contains(pos))
//		{
//			QToolTip::showText(event->globalPos(), title, view, rect);
//		}
//		else
//			QToolTip::hideText();
//	}
//}
//bool TNSearchListItemDelegateV2::helpEvent(QHelpEvent *event, QAbstractItemView *view,
//	const QStyleOptionViewItem &option, const QModelIndex &index)
//{
//	if (!event || !view)
//		return false;
//
//	if (event->type() == QEvent::ToolTip) {
//		QRect rect = view->visualRect(index);
//		QSize size = sizeHint(option, index);
//		QPoint pos = event->pos();
//		if (rect.contains(pos)) {
//			//TNSearchTreeItemV2 *typeItem = static_cast<TNSearchTreeItemV2*>(index.internalPointer());
//			//if (typeItem != nullptr)
//			//{
//			//	TNSearchNameItem *item = static_cast<TNSearchNameItem*>(typeItem);
//			//	if (item == nullptr)
//			//		return false;
//			//	if (item->getType() == TNSearchNameItem::FriendItem ||
//			//		item->getType() == TNSearchNameItem::GroupChatItem)
//			//	{
//			//		paintFriendToolTip(event, view, option,index,item);
//			//	}
//			//	else if (item->getType() == TNSearchNameItem::ColleagueItem ||
//			//		item->getType() == TNSearchNameItem::GroupItem ||
//			//		item->getType() == TNSearchNameItem::NotifyItem)
//			//	{
//			//		paintColleagueToolTip(event, view, option, index, item);
//			//	}
//			//}
//		}
//		else
//			QToolTip::hideText();
//		return true;
//	}
//	return QStyledItemDelegate::helpEvent(event, view, option, index);
//}

bool TNSearchListItemDelegateV2::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
	bool bRepaint = false;
	QMouseEvent *pEvent = static_cast<QMouseEvent *> (event);

	int titleX = option.rect.x() + SHOWALL_MARGIN_LEFT;
	int titleY = option.rect.y() + SHOWALL_MARGIN_TOP;
	
	QApplication::restoreOverrideCursor();

	QStyleOptionButton button;
	button.rect = QRect(titleX,
		titleY, SHOWALL_BUTTON_W, SHOWALL_BUTTON_H);
	
	// 鼠标位于按钮之上
	if (button.rect.contains(pEvent->pos()))
	{
		bRepaint = true;
		switch (event->type())
		{
			// 鼠标滑过
			case QEvent::MouseMove:
				QApplication::setOverrideCursor(Qt::PointingHandCursor);
				break;
			case QEvent::MouseButtonPress:
				break;
			case QEvent::MouseButtonRelease:
				if (m_ButtonMap[index] > 0)
				{
					QString tagName;
					int status = m_ButtonStaus[m_ButtonMap[index]];
					(const_cast<TNSearchListItemDelegateV2 *>(this))->m_ButtonStaus[m_ButtonMap[index]] = !status;
					emit showButtonClickedIntag(index, m_ButtonMap[index], !status);
				}
				break;
			default:
				break;
		}
	}
	return bRepaint;
}
void TNSearchListItemDelegateV2::resetShowAllStatus()
{
	m_ButtonStaus.clear();
}