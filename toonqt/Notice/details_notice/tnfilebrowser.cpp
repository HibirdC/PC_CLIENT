#include "tnfilebrowser.h"
#include "notice_global.h"
#include <QImage>
#include <QFileIconProvider>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QFileDialog>
#include <QMenu>
#include <QTextCodec>
#include <QContextMenuEvent>
#include <QMimeData>
#include <QDrag>
#include <map>
#include "TNIMCoreClient.h"
#include "model_data/TNModelUserMessage.h"
#include "TNMsgDetailModel.h"
#include "network/tnsendimsg.h"
#include "TNPathUtil.h"
#include "TNMessageBox.h"
#include "tnnotifycenter.h"
#include "recoredfilebrowser.h"
#include "tnwinconvert.h"
#ifdef WIN32
#include <Windows.h>
#include <shlobj.h>
#endif


#define OPEN_FILE		QString("打开")
#define OPEN_DIR		QString("打开文件夹")
#define DOWNLOAD_FILE	QString("下载")
#define SAVE_OTHER_FILE QString("另存为")
#define FILE_DOWNLOAD_FIAL QString("失败")
#define FILE_SENDFORWARD QString("转发")
#define NOT_EXISTS		QString("此文件不存在,可能被删除或被移动到其它位置")

QString TNFileBrowser::_oldSelectPath = "";
std::map<QString,TNFileBrowser*> g_map_fileBrowser;


void add_map_fileBrowser(QString msgId,TNFileBrowser* fileBrowser){
    Q_ASSERT(!msgId.isEmpty());
    g_map_fileBrowser[msgId] = fileBrowser;
}

void delete_map_fileBrowser(QString msgId){
    Q_ASSERT(!msgId.isEmpty());
    std::map<QString,TNFileBrowser*>::const_iterator itera = g_map_fileBrowser.find(msgId);
    if(itera != g_map_fileBrowser.end())
        g_map_fileBrowser.erase(itera);
}

bool find_fileBrowser(){
    std::list<QString>& recorde = RecoredFileBrowser::getInstance()->_recored_file_browser;
    for(std::list<QString>::const_iterator itera = recorde.begin();
        itera != recorde.end();++itera){
        QString msgId = *itera;
        if(g_map_fileBrowser.find(msgId) == g_map_fileBrowser.end()){
            recorde.erase(itera);
            return false;
        }
    }
    return true;
}

TNFileBrowser::TNFileBrowser(bool isShowRevoke, TNModelUserMessage* data,
	TNMsgDetailModel* msgModel,
	QWidget *parent /* = 0 */)
	: QWidget(parent)
	, _data(data)
	, _msgModel(msgModel)
	, _isShowRevoke(isShowRevoke)
    , _isCreatedDrag(false)
{
	ui.setupUi(this);
	ui.progressBar_file->setTextVisible(false);
	ui.label_file_name->setElideMode(Qt::ElideMiddle);
	ui.button_file_open->setCursor(Qt::PointingHandCursor);
	ui.button_file_opendir->setCursor(Qt::PointingHandCursor);
	ui.button_file_open->setFlat(true);
	ui.button_file_opendir->setFlat(true);
    ui.button_file_sendForward->setFlat(true);
    ui.button_file_sendForward->setCursor(Qt::PointingHandCursor);
    ui.button_cancel_upload->setCursor(Qt::PointingHandCursor);
    ui.widget_file_content->setCursor(Qt::PointingHandCursor);
	ui.button_file_sendForward->setText(FILE_SENDFORWARD);

    //初始化上传下载库
    _imClient = TNSendIMsg::getInstance();
    //初始化文件状态
    initStatus();

    connect(ui.button_file_open, SIGNAL(clicked()),this,SLOT(onClickedOpenfile()));
	connect(ui.button_file_opendir, SIGNAL(clicked()), this, SLOT(onClickedOpendir()));
    connect(ui.button_file_sendForward, SIGNAL(clicked()), this, SIGNAL(actionSendForward()));
    connect(ui.button_cancel_upload, SIGNAL(clicked()),this, SLOT(onCancelUploading()));
    //设置文件的简介
	setFileData();
	InitMenu();
    setAcceptDrops(true);
    //全局记录fileBrowser
    add_map_fileBrowser(_data->GetMsgID(),this);
    RecoredFileBrowser::getInstance()->add_recored_fielbrowser(_data->GetMsgID());
    _currentMsgId = _data->GetMsgID();
}

TNFileBrowser::~TNFileBrowser()
{
    delete_map_fileBrowser(_currentMsgId);
}

void TNFileBrowser::initStatus()
{
    switch (_data->getMsgSendOrRecv()){
    case MESSAGE_SEND://发送的数据
        ui.label_file_isdownload->hide();
        switch(_data->getMsgStatus()){
        case MSG_STATUS_SEND_SUC:
            ui.progressBar_file->hide();
            ui.button_cancel_upload->setVisible(false);//hide();
            break;
        case MSG_STATUS_SENDING:{
            int progress = 100;
            if(!_imClient->getProgress(down_mark(_data->GetMsgID()),&progress)){
                ui.progressBar_file->hide();
            }else{
                startProgressBar(progress);
            }
            ui.button_file_sendForward->hide();
            ui.button_cancel_upload->setVisible(true);//show();
            break;
            }
        case MSG_STATUS_UNSEND:
            startProgressBar(0);
            ui.button_file_sendForward->hide();
            break;
        case MSG_STATUS_SEND_FAIL:
            ui.progressBar_file->hide();
            ui.button_file_sendForward->hide();
            ui.button_cancel_upload->setVisible(false);//hide();
            break;
        case MSG_STATUS_RESEND:{
            int progress = 0;
            startProgressBar(progress);
            ui.button_file_sendForward->hide();
            ui.button_cancel_upload->setVisible(true);//show();
            break;
            }
        default:
            break;
        }
        break;
    case MESSAGE_RECV://接收的数据
    case MESSAGE_CONVERT:
        ui.progressBar_file->hide();
        ui.button_cancel_upload->setVisible(false);//hide();
        switch (_data->getMsgStatus()) {
        case MSG_STATUS_SEND_SUC:{
            QString localPath = _data->getFileLocalPath();
            QFile file(localPath);
            switch (_data->getMsgFileStatus()) {
            case MSG_STATUS_FILE_DOWNLOADING:{
                int progress = 0;
                _imClient->getProgress(down_mark(_data->GetMsgID()),&progress);
                startProgressBar(progress);
                ui.button_file_open->setText("");
                ui.button_file_opendir->setText("");
                ui.button_file_open->setCursor(Qt::ArrowCursor);
                ui.button_file_opendir->setCursor(Qt::ArrowCursor);
                ui.label_file_isdownload->hide();
                ui.button_cancel_upload->setVisible(true);//show();
                break;
            }
            case MSG_STATUS_FILE_DOWN_FAIL:
            case MSG_STATUS_FILE_UNDOWN:
                if(!file.exists()){
                    ui.button_file_open->setText(DOWNLOAD_FILE);
                    ui.button_file_opendir->setText(SAVE_OTHER_FILE);
                    ui.label_file_isdownload->setText("");
                    ui.button_cancel_upload->setVisible(false);//hide();
                }
                break;
            case MSG_STATUS_FILE_SUC:
                ui.label_file_isdownload->hide();
                if(!file.exists()){
                    ui.button_file_open->setText(DOWNLOAD_FILE);
                    ui.button_file_opendir->setText(SAVE_OTHER_FILE);
                    ui.label_file_isdownload->setText("");
                    ui.button_cancel_upload->setVisible(false);//hide();
                }
                break;
            default:
                break;
            }
            break;
        }
        default:
            ui.label_file_isdownload->hide();
            break;
        }
        break;
    default:
        break;
    }
}

void TNFileBrowser::setFileData()
{
	qint64 file_size = 0;
	QString fileSuffix, file_name;
	//找出文件后缀
    switch(_data->getMsgSendOrRecv()){
    case MESSAGE_SEND:{
        if(QFile::exists(_data->getFileLocalPath())){
            QFileInfo file_info(_data->getFileLocalPath());
            file_name = file_info.fileName();
            fileSuffix = file_info.suffix();
            file_size = file_info.size();
        }else{
            file_name = _data->getFileName();
            file_size = _data->getFileSize();
            QStringList down_suffix_list = file_name.split(".");
            int size = down_suffix_list.size();
            if (size > 0)
                fileSuffix = down_suffix_list[size - 1];
        }
        break;
    }
    case MESSAGE_RECV:
    case MESSAGE_CONVERT:{
        file_name = _data->getFileName();
        file_size = _data->getFileSize();
        QStringList down_suffix_list = file_name.split(".");
        int size = down_suffix_list.size();
        if (size > 0)
            fileSuffix = down_suffix_list[size - 1];
        break;
    }
    }
    if(_data->GetMessageType() == em_video){
        fileSuffix = "mp4";
    }
	setFileIcon(fileSuffix);
	QString qs_result_size;
	float result;
	int g = file_size / GB;
	int m, k, b;
	if (g > 0){
		m = file_size % GB;
		result = g + (float)m / GB;
		qs_result_size.sprintf("%.2fGB", result);
	}
	else if (file_size / MB > 0){
		m = file_size / MB;
		k = file_size % MB;
		result = m + (float)k / MB;
		qs_result_size.sprintf("%.2fMB", result);
	}
	else if (file_size / KB > 0){
		k = file_size / KB;
		b = file_size % KB;
		result = k + (float)b / KB;
		qs_result_size.sprintf("%.2fKB", result);
	}else{
		qs_result_size = QString("%1bytes").arg(file_size);
	}
    if(file_size == 0){
        ui.label_file_size->setText("");
    }else{
        ui.label_file_size->setText(qs_result_size);
    }
	ui.label_file_name->setText(file_name);
}

void TNFileBrowser::setFileIcon(const QString& file_suffix)
{
    QImage image;
    if (image.load(TNPathUtil::getFileIcon(file_suffix)))
    {
        ui.label_file_pic->setPixmap(QPixmap::fromImage(image));
    }
}

void TNFileBrowser::setProgressBarValue(int value)
{
	ui.progressBar_file->setValue(value);
}

void TNFileBrowser::onClickedOpenfile()
{
    emit TNNotifyCenter::instance()->signalHideGroupChatMemberWidget();
	QString bn_text = ui.button_file_open->text();
	if (bn_text == OPEN_FILE){//打开
        QString path = _data->getFileLocalPath();
        if(!QFile::exists(path)){//文件被删除或者移动
            //notice 日志
            QString qs_log = "[Notice] [TNFileBrowser] onClickedOpenfile failed path:" + path;
            qInfo() << qs_log;
            TNMessageBox messageBox(this);
            messageBox.setMsg(NOT_EXISTS);
            messageBox.exec();
            ui.button_file_open->setText(DOWNLOAD_FILE);
            ui.button_file_opendir->setText(SAVE_OTHER_FILE);
            return;
        }
		QString dir_name = "file:///" + path;
		QDesktopServices::openUrl(QUrl(dir_name, QUrl::TolerantMode));
	}else if (bn_text == DOWNLOAD_FILE){//下载
		//download
        QString file_path = TNPathUtil::getUserRecFile() + _data->getFileName();
        if(_data->GetMessageType() == em_video){
            file_path += ".mp4";
        }
		startToDown(file_path);
	}
}

void TNFileBrowser::onClickedOpendir()
{
    emit TNNotifyCenter::instance()->signalHideGroupChatMemberWidget();
	QString bn_text = ui.button_file_opendir->text();
	if (bn_text == OPEN_DIR){//打开文件夹
        QString path = _data->getFileLocalPath();
        if(!QFile::exists(path)){
            //notice 日志
            QString qs_log = "[Notice] [TNFileBrowser] onClickedOpendir failed path:" + path;
            qInfo() << qs_log;
            TNMessageBox messageBox(this);
            messageBox.setMsg(NOT_EXISTS);
            messageBox.exec();
            ui.button_file_open->setText(DOWNLOAD_FILE);
            ui.button_file_opendir->setText(SAVE_OTHER_FILE);
            return;
        }
		QFileInfo file_info(path);
#ifdef Q_OS_WIN
        /*
		QString argsStr = "/select, "+ file_info.filePath().replace("/","\\");
		QTextCodec* codec = QTextCodec::codecForName("GB18030");
		ShellExecuteA(NULL, "open", "explorer", 
			codec->fromUnicode(argsStr).constData(),
			NULL, SW_SHOWDEFAULT);//将UTF-8转换为GBK再转换为const char* 类型  
        */
        QString argsStr = file_info.filePath().replace("/","\\");
        CoInitialize(NULL);
        ITEMIDLIST* pidl = ILCreateFromPath(tnwinconvert::Utf8ToUnicode(argsStr.toStdString()).c_str());
        if(pidl) SHOpenFolderAndSelectItems(pidl,0,0,0);
        CoUninitialize();
#else
		QString dir_name = "file:///" + file_info.path();
		QDesktopServices::openUrl(QUrl(dir_name, QUrl::TolerantMode));
#endif
	}else if (bn_text == SAVE_OTHER_FILE){//另存为
		QString file_suffix, file_name;
        int last_index = _data->getFileName().lastIndexOf(".");
		if (last_index != -1){
            file_name = _data->getFileName().mid(0, last_index);
		}else{
            file_name = _data->getFileName();
		}

        QStringList down_suffix_list = _data->getFileName().split(".");
		int size = down_suffix_list.size();
        if (size > 1)
			file_suffix = down_suffix_list[size - 1];
        if(_data->GetMessageType() == em_video){
            file_suffix = "mp4";
        }

        QString file_path = QFileDialog::getSaveFileName(NULL, ("另存为"),
			_oldSelectPath + "/" + file_name, file_suffix);
        //如果当前的这条消息widget销毁了,直接返回
        if (file_path.isEmpty() || !find_fileBrowser()){
			return;
		}
		last_index = file_path.lastIndexOf("/");
		if (-1 != last_index){
			_oldSelectPath = file_path.mid(0,last_index);
		}
		file_path += ".";
		file_path += file_suffix;
		startToDown(file_path);
	}
}

void TNFileBrowser::onDownloadFinish(bool success, QString file, QString msgId)
{
    Q_UNUSED(msgId);
	if (success){
        //下载完成
        _data->setMsgFileStatus(MSG_STATUS_FILE_SUC);
		ui.button_file_open->setText(OPEN_FILE);
		ui.button_file_opendir->setText(OPEN_DIR);
		ui.button_file_open->setCursor(Qt::PointingHandCursor);
		ui.button_file_opendir->setCursor(Qt::PointingHandCursor);
        ui.button_file_open->show();
        ui.button_file_opendir->show();
        _data->setFileLocalPath(file);
    }else{
        _data->setMsgFileStatus(MSG_STATUS_FILE_DOWN_FAIL);
        ui.button_file_open->setText(DOWNLOAD_FILE);
        ui.button_file_opendir->setText(SAVE_OTHER_FILE);
        ui.button_file_open->setCursor(Qt::PointingHandCursor);
        ui.button_file_opendir->setCursor(Qt::PointingHandCursor);
        ui.button_file_open->show();
        ui.button_file_opendir->show();
        ui.label_file_isdownload->setText(FILE_DOWNLOAD_FIAL);
        //ui.label_file_isdownload->show();
        _data->setFileLocalPath("");
    }
    endProgressBar(success);
}

void TNFileBrowser::startProgressBar(int pos)
{
	//一秒触发一次
	ui.progressBar_file->show();
    setProgressBarValue(pos);
}

void TNFileBrowser::updateProgressBar(int pos)
{
    setProgressBarValue(pos);
}

void TNFileBrowser::endProgressBar(bool success)
{
	setProgressBarValue(100);//得到传送完成消息后完成
	ui.progressBar_file->hide();
    ui.button_cancel_upload->setVisible(false);//hide();
    if(success){
        ui.button_file_sendForward->show();
    }
}

void TNFileBrowser::InitMenu()
{
	_pop_menu = new QMenu();
	QAction *revokeAction = new QAction(this);
    QAction *del = new QAction(this);
    del->setText(("删除"));
	revokeAction->setText(("撤回"));
	revokeAction->setVisible(_isShowRevoke);
	//清除原有菜单
    _pop_menu->addAction(del);
    _pop_menu->addAction(revokeAction);

	connect(revokeAction, SIGNAL(triggered()), this, SIGNAL(actionRevote()));
    connect(del, SIGNAL(triggered()), this, SIGNAL(delFileMsg()));
}
void TNFileBrowser::contextMenuEvent(QContextMenuEvent *e)
{
    switch(_data->getMsgSendOrRecv()){
    case MESSAGE_CONVERT:
        _pop_menu->exec(e->globalPos());
        break;
    case MESSAGE_RECV:
        _pop_menu->exec(QCursor::pos());
        break;
    case MESSAGE_SEND:
        if(_data->getMsgStatus() == MSG_STATUS_SEND_SUC){
            _pop_menu->exec(QCursor::pos());
        }
        break;
    }
}
void TNFileBrowser::startToDown(QString filePath)
{
	//下载
    _data->setMsgFileStatus(MSG_STATUS_FILE_DOWNLOADING);
    TNIMCoreClient::GetIMClient()->SetMsgFileStatus(_data->GetMsgID(),_data->getSessionId(),MSG_STATUS_FILE_DOWNLOADING);
    startProgressBar(0);
    ui.button_file_open->setText("");
    ui.button_file_opendir->setText("");
    ui.button_file_open->setCursor(Qt::ArrowCursor);
    ui.button_file_opendir->setCursor(Qt::ArrowCursor);
    ui.label_file_isdownload->hide();
    ui.button_cancel_upload->setVisible(true);//show();
    _imClient->DownloadFile(_data->GetUserMessage(), _data->GetMsgID(), _data->getSessionId(), filePath);
}

void TNFileBrowser::onCancelUploading()
{
    if(_data->getMsgFileStatus() == MSG_STATUS_FILE_DOWNLOADING){
        _imClient->cancelDownLoad(_data->GetMsgID(),_data->getSessionId());
        onDownloadFinish(false,"",_data->GetMsgID());
        emit cancelFileDownOrUploading(false);
    }else if(_data->getMsgFileStatus() == MSG_STATUS_FILE_UPLOADING){
        _imClient->cancelUpLoad(_data->GetMsgID());
        emit cancelFileDownOrUploading(true);
    }
}

void TNFileBrowser::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(ui.widget_file_content->rect().contains(event->pos()) && event->button() == Qt::LeftButton){
        onClickedOpenfile();
    }
}

void TNFileBrowser::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list")){
        event->acceptProposedAction();
    }else{
        event->ignore();
    }
}

void TNFileBrowser::dragEnterEvent(QDragEnterEvent *event)
{
    return QWidget::dragEnterEvent(event);
}

void TNFileBrowser::dropEvent(QDropEvent *event)
{
    return QWidget::dropEvent(event);
}

void TNFileBrowser::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        _startPos = event->pos();
    }
    return QWidget::mousePressEvent(event);
}

void TNFileBrowser::mouseReleaseEvent(QMouseEvent *event)
{
    _isCreatedDrag = false;
    return QWidget::mouseReleaseEvent(event);
}

void TNFileBrowser::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        if(!_data->getFileLocalPath().isEmpty() && !_isCreatedDrag){
            int distance = (event->pos() - _startPos).manhattanLength();
            if(distance >= QApplication::startDragDistance() && !this->rect().contains(event->pos())){
                _isCreatedDrag = true;
                QMimeData *mimeData = new QMimeData;
                QUrl url = QUrl::fromLocalFile(_data->getFileLocalPath());
                QString sUrl = url.toString();
                mimeData->setData("text/uri-list",sUrl.toStdString().c_str());

                QDrag* drag = new QDrag(this);
                drag->setMimeData(mimeData);
                drag->setHotSpot(event->pos());
                drag->exec(Qt::CopyAction, Qt::CopyAction);
                _isCreatedDrag = false;
            }
        }
    }
    return QWidget::mouseMoveEvent(event);
}
