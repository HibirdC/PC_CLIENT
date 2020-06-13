#ifndef TNDETAILSUNREADWDIGET_H
#define TNDETAILSUNREADWDIGET_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class TNDetailsUnreadWdiget;
}

class TNDetailsUnreadWdiget : public QWidget
{
    Q_OBJECT

public:
    explicit TNDetailsUnreadWdiget(QWidget *parent = 0);
    ~TNDetailsUnreadWdiget();
    /*
     * ture up
     * false down
    */
    void setUpAndDown(bool up);
    void setUpUnReadNum(int number);
    void setDownUnReadNum(int number);
    void addUpUnreadNum();
    void addDownUnreadNum();
    int  getDownUnreadNum(){return _downUnreadNum;}
    int  getUpUnreadNum(){return _upUnreadNum;}
    bool getUpOrDown(){return _upOrDown;}
    void setFirstUnreadMsgId(const QString& msgId){_firstUnreadMsgId = msgId;}
    QString getFirstUnreadMsgId(){return _firstUnreadMsgId;}
Q_SIGNALS:
    void downClicked();
    void upClicked();
protected:
    virtual void paintEvent(QPaintEvent *event);
private slots:
    void on_details_unread_button_close_clicked();
private:
    Ui::TNDetailsUnreadWdiget 	*ui;
    int 						_upUnreadNum;
    int     					_downUnreadNum;
    bool 						_upOrDown;
    //第一条未读消息的id,方便跳转
    QString 					_firstUnreadMsgId;
};

#endif // TNDETAILSUNREADWDIGET_H
