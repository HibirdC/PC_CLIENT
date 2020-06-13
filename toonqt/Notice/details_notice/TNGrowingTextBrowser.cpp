#include "TNGrowingTextBrowser.h"
#include <QScrollBar>
#include <QFocusEvent>
#include <QStyleOption>
#include <QPainter>
#include <qmovie.h>
#include <QApplication>
#include <QMimeData>
#include <QClipboard>
#include <QtMath>
#include <QTextDocumentFragment>
#include <QtMath>
#include <QDesktopServices>
#include <QDrag>
#include <QMimeData>
#include "model_data/TNModelUserMessage.h"
#include "tnimagectr.h"
#include "TNUserDataHelper.h"
#include "TNDataStatistics.h"

TNGrowingTextBrowser::TNGrowingTextBrowser(bool isShowRevoke, bool isShowSaveAs, QWidget *parent /* = Q_NULLPTR */) : QTextBrowser(parent)
, _resize_flag(false)
, _pop_menu(NULL)
, _type(em_text)
, _isShowRevoke(isShowRevoke)
, _isShowSaveAs(isShowSaveAs)
, _data(NULL)
, _isCreatedDrag(false)
{
    this->setOpenExternalLinks(false);
    this->setOpenLinks(false);
	init();
    connect(this,SIGNAL(anchorClicked(QUrl)),this,SLOT(onAnchorClicked(QUrl)));
}

TNGrowingTextBrowser::~TNGrowingTextBrowser()
{
	if (_pop_menu != NULL){
		delete _pop_menu;
		_pop_menu = NULL;
	}
	clearResource();
}

void TNGrowingTextBrowser::init()
{
    setFocusPolicy(Qt::StrongFocus);
	setReadOnly(true);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->verticalScrollBar()->setFixedWidth(0);
	this->horizontalScrollBar()->setFixedHeight(0);
	this->horizontalScrollBar()->setDisabled(true);
	this->verticalScrollBar()->setDisabled(true);
	setAlignment(Qt::AlignVCenter);

	_pop_menu = new QMenu();
	for (int i = 0; i < 5; i++)
	{
		_action[i] = new QAction(this);
	}
	_action[0]->setText(("复制"));
	_action[1]->setText(("转发"));
	_action[2]->setText(("另存为"));
	_action[3]->setText(("删除"));
	_action[4]->setText(("撤回"));
	_action[4]->setVisible(_isShowRevoke);
	_action[2]->setVisible(_isShowSaveAs);
	//清除原有菜单
	for (int i = 0; i < 5; i++)
	{
		_pop_menu->addAction(_action[i]);
	}

	connect(_action[0], SIGNAL(triggered()), this, SLOT(customCopy()));
	connect(_action[1], SIGNAL(triggered()), this, SIGNAL(actionSendForward()));
	connect(_action[4], SIGNAL(triggered()), this, SIGNAL(actionRevote()));
	connect(_action[2], SIGNAL(triggered()), this, SIGNAL(actionSaveAs()));
    connect(_action[3], SIGNAL(triggered()), this, SIGNAL(actionDeleteMsg()));
}

void TNGrowingTextBrowser::customCopy()
{
	QClipboard *board = QApplication::clipboard();
	switch (_type)
	{
	case em_text:
		this->copy();
		break;
	case em_image:
	{
        QMimeData* mimeData = new QMimeData();
        QList<QUrl> urls;
        QString local_path = _data->getFileLocalPath();
        Q_ASSERT(local_path.size() > 4);
        if(local_path.right(4) != "_org"){
            local_path += "_org";
        }
        QString new_path = local_path + _data->getFileSuffix();
        if(!QFile::exists(new_path)){
            if(!QFile::copy(local_path, new_path)){
                 return;
            }
        }
        urls.append(QUrl::fromLocalFile(new_path));
        mimeData->setUrls(urls);
        board->setMimeData(mimeData);
	}
		break;
	default:
		break;
	}
    //埋点
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_NoticeDetail_Copy,
        TNUserDataHelper::GetInstance()->_pluginParam);
}

void TNGrowingTextBrowser::customSelectAll()
{
    this->selectAll();
}

void TNGrowingTextBrowser::focusOutEvent(QFocusEvent *ev)
{
    Qt::FocusReason rsn = ev->reason();
    if (rsn != Qt::PopupFocusReason){
        QTextCursor cus = textCursor();
        cus.clearSelection();
        setTextCursor(cus);
        QTextBrowser::focusOutEvent(ev);
    }
}

void TNGrowingTextBrowser::paintEvent(QPaintEvent *e)
{
    QTextBrowser::paintEvent(e);
    if (!_resize_flag){
		QSizeF sizef = document()->size();
		_resize_flag = true;
        setFixedHeight(qCeil(sizef.height()));
        int idealWidth = qCeil(document()->idealWidth()) + 1;
		setFixedWidth(idealWidth + 
			contentsMargins().left() +
			contentsMargins().right());
    }
}

void TNGrowingTextBrowser::contextMenuEvent(QContextMenuEvent *e)
{
	//菜单出现的位置为当前鼠标的位置
    if (_type == em_image)
		customSelectAll();
    else if(_type == em_text){
        QTextCursor cursor = this->textCursor();
        if(cursor.selection().isEmpty()){
            customSelectAll();
        }
    }
    switch (_data->getMsgSendOrRecv()) {
    case MESSAGE_SEND:
    case MESSAGE_CONVERT:
        if(_data->getMsgStatus() != MSG_STATUS_SEND_SUC){
            _action[1]->setVisible(false);
            _action[4]->setVisible(false);
            if(_data->GetMessageType() == em_image)
                _action[2]->setVisible(false);
        }else{
            _action[1]->setVisible(true);
            _action[4]->setVisible(true);
            if(_data->GetMessageType() == em_image)
                _action[2]->setVisible(true);
        }
        break;
    case MESSAGE_RECV:
        switch (_data->GetMessageType()) {
        case em_image:
            if(_data->getMsgFileStatus() != MSG_STATUS_FILE_SUC){
                _action[0]->setVisible(false);
                _action[1]->setVisible(false);
                _action[2]->setVisible(false);
            }else{
                QString local_path = _data->getFileLocalPath();
                Q_ASSERT(local_path.size() > 4);
                if(local_path.right(4) != "_org"){
                    local_path += "_org";
                }
                bool visi = QFile::exists(local_path);
                _action[0]->setVisible(visi);
                _action[1]->setVisible(true);
                _action[2]->setVisible(visi);
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
	_pop_menu->exec(QCursor::pos());
}

void TNGrowingTextBrowser::setMessageType(MESSAGE_TYPE type)
{
	_type = type;
}
void TNGrowingTextBrowser::InsertGifImage(const QUrl &Url, const QString fileName)
{
	if (_lstUrl.contains(Url)){ //同一个gif 使用同一个movie
		return;
	}else{
		_lstUrl.append(Url);
	}

	QMovie* movie = new QMovie(this);
	movie->setFileName(fileName);
	movie->setCacheMode(QMovie::CacheNone);

	_lstMovie.append(movie);   //获取该movie,以便删除
	_urls.insert(movie, Url);

	//换帧时刷新  
	connect(movie, SIGNAL(frameChanged(int)), this, SLOT(OnStartAnimate(int)));
	movie->start();
}
void TNGrowingTextBrowser::OnStartAnimate(int frame)
{
	if (QMovie* movie = qobject_cast<QMovie*>(sender()))
	{
		document()->addResource(QTextDocument::ImageResource,   //替换图片为当前帧  
			_urls.value(movie), movie->currentPixmap());
		setLineWrapColumnOrWidth(lineWrapColumnOrWidth()); // 刷新显示  
	}
    Q_UNUSED(frame);
}
void TNGrowingTextBrowser::clearResource()
{
	_lstUrl.clear();
	_urls.clear();
	for (QMovie *temp : _lstMovie)
	{
		if (temp != nullptr)
			delete temp;
	}
	_lstMovie.clear();
}

void TNGrowingTextBrowser::setData(TNModelUserMessage* data)
{
	_data = data;
}

void TNGrowingTextBrowser::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        _startPos = event->pos();
    }
    return QTextBrowser::mousePressEvent(event);
}

void TNGrowingTextBrowser::mouseMoveEvent(QMouseEvent *event)
{
    if (_type == em_image){
        this->viewport()->setCursor(Qt::PointingHandCursor);
        if(event->buttons() & Qt::LeftButton && !_isCreatedDrag && !_data->getFileLocalPath().isEmpty()
                && QFile::exists(_data->getFileLocalPath() + "_org")){
            int distance = (event->pos() - _startPos).manhattanLength();
            if(distance >= QApplication::startDragDistance() && !this->rect().contains(event->pos())){
#ifndef __linux__
                QString new_path = _data->getFileLocalPath() + "_org" + _data->getFileSuffix();
                if(!QFile::exists(new_path)){
                    if(!QFile::copy(_data->getFileLocalPath() + "_org", new_path)){
                        return;
                    }
                }
                QUrl url = QUrl::fromLocalFile(new_path);
#endif
                _isCreatedDrag = true;
                QMimeData *mimeData = new QMimeData;
#ifdef __linux__
                QUrl url = QUrl::fromLocalFile(_data->getFileLocalPath() + "_org");
#endif
                QString sUrl = url.toString();
                mimeData->setData("text/uri-list",sUrl.toStdString().c_str());

                QDrag* drag = new QDrag(this);
                drag->setMimeData(mimeData);
                drag->setHotSpot(event->pos());
                drag->exec(Qt::CopyAction, Qt::CopyAction);
                _isCreatedDrag = false;
            }
        }
    }else{
        return QTextBrowser::mouseMoveEvent(event);
    }
}

void TNGrowingTextBrowser::onAnchorClicked(QUrl url)
{
    QString surl = QString::fromUtf8(url.toEncoded());
    if(surl.isEmpty()){
        surl = url.path();
    }
    if(!surl.startsWith("http") && !surl.startsWith("ftp")){
        surl.prepend("http://");
    }
    QDesktopServices::openUrl(surl);
}

void TNGrowingTextBrowser::dragEnterEvent(QDragEnterEvent *e)
{
    return QTextBrowser::dragEnterEvent(e);
}
