#ifndef TNOFFLINENOTICEDIALOG_H
#define TNOFFLINENOTICEDIALOG_H

#include "DropShadowWidget.h"
#include <QDialog>

namespace Ui {
class TNOfflineNoticeDialog;
}

class TNOfflineNoticeDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:

	enum {
		warning,
		errorAndFixed
	};
	explicit TNOfflineNoticeDialog(int mode,QWidget *parent);
    ~TNOfflineNoticeDialog();
	void setText(const QString title, const QString contect);
private:
    Ui::TNOfflineNoticeDialog *ui;
};

#endif // TNOFFLINENOTICEDIALOG_H
