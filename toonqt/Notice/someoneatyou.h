#ifndef SOMEONEATYOU_H
#define SOMEONEATYOU_H

#include <QDialog>
#include "ui_someoneatyou.h"
#include <QMessageBox>
namespace Ui { class someoneatyou; };

#include "common_global.h"

class someoneatyou : public QWidget
{
	Q_OBJECT

public:
	someoneatyou(QWidget *parent = 0);
	~someoneatyou();

    void setText(const QString &text);
    void setMsgId(const QString& msgId){_msgId = msgId;}
	void SetIndex(int index){ _index = index; }
    QString getText();
signals:
    void ClickedMsgBox(QString msgId, int index, bool isScorll = true);

private slots:
	void OnCloseBox();
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual bool eventFilter(QObject *target, QEvent *event);
private:
	Ui::someoneatyou *ui;
	int    _index;
    QString _msgId;
};

#endif // SOMEONEATYOU_H
