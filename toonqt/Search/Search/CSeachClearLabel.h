#ifndef CSEACHCLEARLABEL_H
#define CSEACHCLEARLABEL_H

#include <QLabel>

class CSeachClearLabel : public QLabel
{
	Q_OBJECT

public:
	explicit CSeachClearLabel(QWidget *parent);
	~CSeachClearLabel();

	bool eventFilter(QObject *target, QEvent *event);
protected:
	void mousePressEvent(QMouseEvent *ev);
signals:
	void sigClicked();
	
};

#endif // CSEACHCLEARLABEL_H
