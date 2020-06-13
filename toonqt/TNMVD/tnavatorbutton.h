#ifndef TNAVATORBUTTON_H
#define TNAVATORBUTTON_H

#include <QPushButton>
#include "tncommondealavator.h"

class TNMVD_EXPORT TNAvatorButton : public QPushButton
{
	Q_OBJECT

public:
	TNAvatorButton(QWidget *parent = 0, Cust_Type cust_type = cust_radius);
	~TNAvatorButton();

	void paintEvent(QPaintEvent * e);
	void setAvatorImagePath(const QString& file_path);
	void setCustType(Cust_Type cust_type);
	void setSmallMask(TN::AvatarType flag);
private:
	QString	  _avatorImagePath;
	Cust_Type _cust_type;
	TN::AvatarType	_sizeType;
};

#endif // TNAVATORBUTTON_H
