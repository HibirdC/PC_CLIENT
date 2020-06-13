#ifndef TNSTATUSLABEL_H
#define TNSTATUSLABEL_H

#include <QLabel>
#include <QMovie>
#include "model_data/TNModelUserMessage.h"

class TNMsgDetailModel;
class TNSendIMsg;

class TNStatusLabel : public QLabel
{
	Q_OBJECT

public:
	enum MESSAGE_STATUS{
		em_readed = 1,	//已读
		em_unread,		//未读
		em_loading,
		em_loaded,
		em_failed,
		em_successed
	};
	TNStatusLabel(QWidget *parent = 0);
	~TNStatusLabel();
    void setData(TNModelUserMessage* data);
	void setModel(TNMsgDetailModel* detailModel);
	void setStatus(MESSAGE_STATUS status);
Q_SIGNALS:
    void reSend(TNModelUserMessage data);
protected:
	void mousePressEvent(QMouseEvent *ev);
private:
	void setUnRead();
	void setReaded();
	void setLoading();
	void setLoaded();
	void setFailed();
	void setSuccessed();
	//重新发送
	void reSend();
	//重新下载
	void reRecv();
private:
    MESSAGE_STATUS			_status = em_successed;
    TNModelUserMessage		*_data;
	QMovie*					_loadingMovie;
	TNMsgDetailModel*		_detailModel;
    TNSendIMsg*				_tnSendIMsg;
};

#endif // TNSTATUSLABEL_H
