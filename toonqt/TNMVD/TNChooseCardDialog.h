#ifndef TNCHOOSECARDDIALOG_H
#define TNCHOOSECARDDIALOG_H

#include "TNMVD_global.h"
#include "TNDbUtil.h"
#include "DropShadowWidget.h"

#include <QDialog>
#include <QLabel>
#include <QToolButton>

namespace Ui {
class TNChooseCardDialog;
}

class CheckToolButton : public QToolButton
{
    Q_OBJECT

public:
    explicit CheckToolButton(QWidget *parent = 0)
    {
        numberLabel = new QLabel("", this);
        numberLabel->setObjectName("chooseCardCheckedLabel");
        numberLabel->setVisible(false);
        numberLabel->setAlignment(Qt::AlignCenter);
        numberLabel->raise();
        numberLabel->setFixedSize(22, 22);
        numberLabel->move(19, 22);
    }

    void setChooseFlag(bool flag)
    {
        numberLabel->setVisible(flag);
    }

private:
    QLabel *numberLabel;
};

class TNMVD_EXPORT TNChooseCardDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNChooseCardDialog(bool canCancel, QWidget *parent = 0);
    ~TNChooseCardDialog();

    void setTitleLabelText(const QString& text);
    void setCommentTextEditVisible(bool visible);
    void setChooseCardLabelText(const QString& text);

    QString getComment() const;
    st_FeedPtr getCard() const;
    QString getCardFeedId() const;

public Q_SLOTS:
    virtual void accept();

private slots:
    void slotMaxLength();
    void slotChooseCard();
    void slotClickedExpiredTipLabel();
    void OnTimerSlot();

private:
    Ui::TNChooseCardDialog *ui;

    QPushButton *m_expiredTipLabel; // 这里用QPushButton, 是利用QPushButton的点击信号，点击时将其隐藏
    QTimer *m_pTimer;

    QList<st_FeedPtr> m_myAllStuff;
    QMap<QString, CheckToolButton*> m_feedIdToButtonMap;
    QString m_currentCardFeedId;

    void initialTableWidget();

    // 异步更新下载头像
	void asynDownloadAvatar(const QString& url, const QString& sessionId, const QString& file_path);

private slots:
	void onAvatarDownLoadFinish(bool success, QString file_path, QString sessionId);
};

#endif // TNCHOOSECARDDIALOG_H
