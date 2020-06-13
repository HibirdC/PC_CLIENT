#ifndef TNFEEDBACKPROPOSALDIALOG_H
#define TNFEEDBACKPROPOSALDIALOG_H

#include "DropShadowWidget.h"
#include "TNHttpFeedBack.h"
#include "TNHttpGetListCard.h"

#include <QDialog>

namespace Ui {
class TNFeedBackProposalDialog;
}

class TNFeedBackProposalDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNFeedBackProposalDialog(QWidget *parent = 0);
    ~TNFeedBackProposalDialog();

public slots:
    virtual void accept();

private slots:
    void onMaxLength();

private:
    Ui::TNFeedBackProposalDialog *ui;

    QString getProposalContent() const;
    TNHttpFeedBackPtr m_httpFeedBack;
    TNHttpGetListCardPtr  m_httpGetListCard;
};

#endif // TNFEEDBACKPROPOSALDIALOG_H
