#ifndef TNUNREADVIEW_H
#define TNUNREADVIEW_H

#include <QListView>
#include <QEvent>

class TNUnReadView : public QListView
{
	Q_OBJECT

public:
	TNUnReadView();
	~TNUnReadView();

private:
protected:
	bool event(QEvent *event);
	void mousePressEvent(QMouseEvent *event);
};

#endif // TNUNREADVIEW_H
