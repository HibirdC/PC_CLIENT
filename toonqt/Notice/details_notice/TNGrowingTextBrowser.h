#ifndef TNGROWINGTEXTBROWSER
#define TNGROWINGTEXTBROWSER


#include <QTextBrowser>
#include <QMenu>
#include "NoticeEnum.h"

class TNModelUserMessage;
class TNGrowingTextBrowser : public QTextBrowser
{
	Q_OBJECT
public:
	TNGrowingTextBrowser(bool isShowRevoke, bool isShowSaveAs, QWidget *parent = Q_NULLPTR);
	~TNGrowingTextBrowser();
	void paintEvent(QPaintEvent *e);
	void contextMenuEvent(QContextMenuEvent *e);
	void setMessageType(MESSAGE_TYPE type);
	void InsertGifImage(const QUrl &Url,const QString fileName);
	void setData(TNModelUserMessage* data);
protected:
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
	void init();
	void clearResource();
    void customSelectAll();
    void focusOutEvent(QFocusEvent *ev);
private slots:
	void customCopy();
    void OnStartAnimate(int frame);
    void onAnchorClicked(QUrl url);
signals:
	void actionRevote();
	void actionSendForward();
	void actionSaveAs();
	void actionDeleteMsg();
private:
	bool			_resize_flag;
	QMenu			*_pop_menu;
	MESSAGE_TYPE	_type;
	bool            _isShowRevoke;
	bool			_isShowSaveAs;
	QAction*		_action[5];

	QList<QUrl> _lstUrl;
	QList<QMovie *> _lstMovie;
	QHash<QMovie*, QUrl> _urls;

	//数据
	TNModelUserMessage*		_data;
    bool					_isCreatedDrag;

    QPoint 					_startPos;
};

#endif
