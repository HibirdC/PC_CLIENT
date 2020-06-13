#ifndef tnsearchbottom_H
#define tnsearchbottom_H

#include <QWidget>
namespace Ui {
	class tnsearchbottom;
}


class tnsearchbottom : public QWidget
{
	Q_OBJECT

public:
	tnsearchbottom(QWidget *parent = 0);
	~tnsearchbottom();
	void setButtomFixedHeight(int y);
	void setButtomFixedWidth(int x);
private:
	Ui::tnsearchbottom *ui;
};

#endif // tnsearchbottom_H
