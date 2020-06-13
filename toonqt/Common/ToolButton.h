////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	ToolButton.h
//
// summary:	Declares the tool button class
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef TOOlBUTTON_H
#define TOOlBUTTON_H


#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>

#include "common_global.h"

class QLabel;
class COMMON_EXPORT ToolButton : public QToolButton
{
	Q_OBJECT

public:
	explicit ToolButton(const QString &pic_name,int type, QWidget *parent = 0);
	~ToolButton();

    void showRedPoint(bool show ,int callType);
	void setMousePress(bool mouse_press);
	virtual void setFeedType(const QString &feed);
	virtual void setAvatarPath(const QString &path);

public slots:
	void setMessageNumber(int count);
    int getMessageNumber() const;

protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void painterInfo(int top_color, int middle_color, int bottom_color);
	void mouseDoubleClickEvent(QMouseEvent *event);

public:
	bool mouse_over; //鼠标是否移过
	bool mouse_press; //鼠标是否按下

private:
    QLabel *numberLabel;
    int m_number;

Q_SIGNALS:
	void doubleClicked();
};

#endif //TOOlBUTTON_H
