#ifndef AvatarMENUBASE_H
#define AvatarMENUBASE_H

#include "MenuAreaBase.h"
#include "TNMVD_global.h"
#include "TNNameSpace.h"

class AvatarMenuBase : public MenuAreaBase
{
	Q_OBJECT
public:
	AvatarMenuBase(int id, const QString &pic_name, QWidget *parent = 0);
	~AvatarMenuBase();
	void setFeedType(const QString &feed);
	void setAvatarPath(const QString &path);

protected:
	void paintEvent(QPaintEvent *event);

private:
	Cust_Type _cust_type;
	TN::AvatarType _sizeType;
	
};

#endif // AvatarMENUBASE_H
