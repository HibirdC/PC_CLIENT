#ifndef TNMSGDETAILITEMWIDGET_H
#define TNMSGDETAILITEMWIDGET_H

#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QTextBrowser>

#include "TNDbUtil.h"
#include "TNGrowingTextBrowser.h"
#include "model_data/TNModelUserMessage.h"
#include "TNMsgDetailModel.h"
#include "tnstatuslabel.h"
#include "tnavatorbutton.h"
#include "TNPictureViewerDialog.h"

class TNFileBrowser;
class TNOtherMessageBrowser;
class TNAudioBrowser;
class image_progress_bar;

class TNMsgDetailItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TNMsgDetailItemWidget(TNModelUserMessage* data,
		const QModelIndex& index,
        const QSize& parentSize,
		QWidget *parent = 0,
		TNMsgDetailModel* detailModel = 0,
		bool first_message = false,
		bool time_visible = true);
	~TNMsgDetailItemWidget();
	/*
	设置头像
	*/
    void setHeadpic(QString);
	/*
	设置时间
	*/
	void setTime(QString time);
	//上传、下载完成后更新图片
	void updateImage(bool success, QString data);
	//结束进度条
    void endProgressBar(bool success);
    //更新进度条
    void updateProgressBar(MESSAGE_TYPE type,int progress);
	//文件下载完成
	void onFileDownloadFinish(bool success, QString file, QString msgId);
	//播放声音结束
	void stopPlay();
	//audio 下载完成
	void audioDownloadFinish(bool success,QString fileUrl);
	/*
	回执界面完成状态
	*/
	void setStatusLabel(bool success);
	/*
	重新设置大小
	*/
    void reSize(const QSize& size);
    /*
     *更新名称
    */
    void updateSendName();
Q_SIGNALS:
    void createSendFinish(TNModelUserMessage data,QModelIndex q_index);
    void createRecvFinish(TNModelUserMessage data,QModelIndex q_index);
	void downLoadAvatorIcon(TNModelUserMessage data);
	void autoHeight(int height, QModelIndex index);
	void sendRevokeSignal(int resultType, int msgType,qint64 msgTime, const QString&sessionId, const QString &msgId, const QString &pushInfo);
	void deleteMsgSignal(const QString & msgId);
    void jumpToMsg(const QString& msgId);
private slots:
	//上传、下载完成后更新文件状态
	void updateFile(bool success, QString file_path, QString msgId);
	//界面创建完成
    void onCreateSendFinished(TNModelUserMessage data,QModelIndex q_index);
    void onCreateRecvFinished(TNModelUserMessage data,QModelIndex q_index);
	void onLoadAvatorIcon(TNModelUserMessage data);
    //撤回
	void onActionMsgRevoke();
	void onActionSendFoward();
    void onSelectContactFinised(QList<TNMessageListAdapter> selectSessions, QList<TNFriend> selectFriends, QList<TNStructGroupChat> selectGroupChats);
	void onActionSaveAs();
	void onActionDeleteMsg();
    void slotFeedFrame();
    void onCancelFileDownOrUploading(bool upload);
protected:
    void paintEvent(QPaintEvent *e);
    bool eventFilter(QObject *watched, QEvent *event);
private:
	void init();
	void setTimeVisble(bool flag = true);
    void decodeContent(TNModelUserMessage* data);

	void createTextBrowser();
	void createLabelName();
    void createFileBrowser();
	void createOtherMessageBrowser(const QString& data, MESSAGE_TYPE type);
	void createAudioBrowser();
	void calculationTextBrowser();
	void calculationImageTextBrowser();
	void calculationImageBrowser();
	void paintEmojiAndText(QPaintEvent* e);
	void paintImage(QPaintEvent* e);
	void paintNotifyText(QPaintEvent* e);
	void adjustImage(int& width, int& height);
	void dealDownloadData();
	void dealUploadData();
    void dealConvertData();//转发的图片数据
	void setMovieSize(const QRect& rect);
    bool speedLoadImage(const QString& image_path,
                        const QString& image_type,
                        QImage& image, QSize& pic_size,
                        bool adjust = true);
	void createStatusLabel();
	void setAavtorCustType();
    int getPicList(QList<TNPictureViewerDialog::PictureItem> &picList);//取得当前图片列表，返回当前索引
    //取得和显示大图
    //QString getOrignalImage(const QString &strThumFileLocalPath, TNModelUserMessage *msgData);
    void showOrignalImage();
	//resize
    void setParentSize(const QSize& size);
	void getMaxTextWidth();
	void resizeTimeCtr();
	void resizeAvaCtr();
	void resizeLabelName();
	void resizeEmojiAndText();
	void resizeStatusLabel(const QRect& rect);
	void resizeImage();
	void resizeFileBrowser();
	void resizeAudioBrowser();
	void resizeOtherMsgBrowser();
	bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
    //insert image to rich text
    void insertImage(QString image_path,const QImage& source = QImage());
private:
	int		 _rectAngleSpaceWidth;//在label_text外层画矩形框到label_text的距离
	int		 _rectAngleSpaceHeight;
	int		 _labelTextSpaceToEnd;//label_text距离当前Label末尾right的距离
	int		 _labelTextTriangleWidth;//画聊天消息三角边长
	int      _messageSpaceToNext;//每条消息的间隔
	QRect	 _labelPeopleInitRect;//label_People初始位置(左边)
	QRect	 _rightPeopleInitRect;//(右边)
	QColor   _leftColor;
	QColor	 _rightColor;

    TNModelUserMessage		*_data;//数据
	TNGrowingTextBrowser	*_labelText;//表情和文字
	TNAvatorButton			*_labelPeople;//头像
	QLabel					*_labelTime;//时间

	int						_parentMaxwidth;//父窗口的最大宽度
	int						_parentMaxheight;
	int						_max_text_width;//文字和图片显示的最大宽度

	bool					_resizeFlag;//第一次绘制
	MESSAGE_TYPE			_messageType;//消息类型
	bool					_isFirstMessage;//第一条消息
	bool					_isTimeVisible;//是否隐藏时间显现
	//当文件、图片为接收或者为加载历史记录时,预先知道的参数
	//附件显示子控件
	TNFileBrowser*			_fileBrowser;
	//图片显示子控件
    image_progress_bar*	    _picProgress;//进度
	//model层变量
	TNMsgDetailModel*		_tnMsgDetailModel;
	//不能处理的消息或者群聊通知消息控件
	TNOtherMessageBrowser*  _tnOtherMsgBrowser;
	//音频控件
	TNAudioBrowser*			_tnAudioBrowser;
	//是否发送/接收成功状态
	TNStatusLabel*			_tnLabelStatus;
	int						_tnLabelStatusWidth;
	QModelIndex				_tnIndex;//在消息view界面中的index
	QLabel*					_labelName;//群聊别人发的数据显示昵称
	bool					_isCreateName;
	int						_nameSpaceText;//名字距离消息框的距离
    bool                    _isMouseButtonPress;
    bool                    _bIsDownPicSuccess;
};

#endif // TNMSGDETAILITEMWIDGET_H
