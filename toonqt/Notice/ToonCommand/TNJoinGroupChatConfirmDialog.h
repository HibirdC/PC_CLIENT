#ifndef TNJOINGROUPCHATCONFIRMDIALOG_H
#define TNJOINGROUPCHATCONFIRMDIALOG_H

#include "TNDbUtil.h"
#include "DropShadowWidget.h"

#include <QDialog>
#include <QLabel>
#include <QToolButton>

namespace Ui {
class TNJoinGroupChatConfirmDialog;
}

class TNJoinGroupChatConfirmDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNJoinGroupChatConfirmDialog(const st_FeedPtr &card, st_GroupInfo groupChat, QWidget *parent = 0);
    ~TNJoinGroupChatConfirmDialog();

private:
    Ui::TNJoinGroupChatConfirmDialog *ui;

    // 异步更新下载头像
    void asynDownloadAvatar(const QString& url, const QString& sessionId, const QString& file_path);

private slots:
    void onAvatarDownLoadFinish(bool success, QString file_path, QString sessionId);
};

#endif // TNJOINGROUPCHATCONFIRMDIALOG_H
