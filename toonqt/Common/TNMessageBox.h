#ifndef TNMESSAGEBOX_H
#define TNMESSAGEBOX_H

#include "common_global.h"

#include <QMessageBox>

namespace Ui { class TNMessageBox; };

class COMMON_EXPORT TNMessageBox : public QDialog
{
	Q_OBJECT

public:
    explicit TNMessageBox(QWidget *parent, int expireTime_ms = 1500);
	~TNMessageBox();

public:
    void setIconVisible(bool visible);

	void setMsg(const QString &msg);

    // 设置相对于父窗体的位置
    void setPositionToParent(int dx, int dy);

private Q_SLOTS :
	void OnTimerSlot();
	
protected:
	virtual void paintEvent(QPaintEvent *event);

	virtual bool eventFilter(QObject *target, QEvent *event);

private:
	Ui::TNMessageBox *ui;
	QPoint m_parentPoint;
	QTimer *m_pTimer;
};

#endif // TNMESSAGEBOX_H
