#include "AvatarMenuBase.h"
#include "tncommondealavator.h"

#define AVATAR_WIDTH 40
#define AVATAR_HEIGHT 40

AvatarMenuBase::AvatarMenuBase(int id, const QString &pic_name, QWidget *parent)
: MenuAreaBase(id, pic_name, MENU_SHOW_TYPE_AVATAR, parent)
, _cust_type(cust_ellipse)
, _sizeType(TN::Middle)

{
	setAvatarPath(pic_name);
}

AvatarMenuBase::~AvatarMenuBase()
{

}
void AvatarMenuBase::paintEvent(QPaintEvent *event)
{
	MenuAreaBase::paintEvent(event);
}
void AvatarMenuBase::setFeedType(const QString &feed)
{ 
	if (feed.startsWith("g_"))
	{
		_cust_type = cust_hexagon;
	}
	else if (feed.startsWith("c_"))
	{
		_cust_type = cust_ellipse;
	}
	else
	{
		_cust_type = cust_radius;
	}
}
void AvatarMenuBase::setAvatarPath(const QString &path)
{ 
	QPixmap avatarImage = TNCommonDealAvator::getTypeQPixmap(path, QSize(AVATAR_WIDTH, AVATAR_HEIGHT), _cust_type, _sizeType);
	setIcon(avatarImage);
	setIconSize(QSize(AVATAR_WIDTH, AVATAR_HEIGHT));
	update();
}
