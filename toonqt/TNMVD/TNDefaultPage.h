#ifndef TNDEFAULTPAGE_H
#define TNDEFAULTPAGE_H

#include <QWidget>
#include "TNMVD_global.h"

namespace Ui {
	class TNDefaultPage;
}


class TNMVD_EXPORT TNDefaultPage : public QWidget
{
	Q_OBJECT

public:
	TNDefaultPage(QWidget *parent = 0);
	~TNDefaultPage();

	void setTextTitle(const QString &text);
	void setBackPic(const QString & path,QSize size);
    void setBorderImage(const QString &path);
private:
	Ui::TNDefaultPage *ui;
};

#endif // TNDEFAULTPAGE_H
