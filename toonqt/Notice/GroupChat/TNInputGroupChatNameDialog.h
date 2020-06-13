#ifndef TNINPUTGROUPCHATNAMEDIALOG_H
#define TNINPUTGROUPCHATNAMEDIALOG_H

#include "DropShadowWidget.h"
#include <QDialog>

namespace Ui {
class TNInputGroupChatNameDialog;
}

class TNInputGroupChatNameDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNInputGroupChatNameDialog(const QString &groupChatName = QString::null, QWidget *parent = 0);
    ~TNInputGroupChatNameDialog();

    QString getGroupChatName() const;

public Q_SLOTS:
    virtual void accept();
	
	void slotCheckNameLength(const QString &text);

private:
    Ui::TNInputGroupChatNameDialog *ui;

    bool validateParameters();
    bool existInDB(const QString &groupChatName);
};

#endif // TNINPUTGROUPCHATNAMEDIALOG_H
