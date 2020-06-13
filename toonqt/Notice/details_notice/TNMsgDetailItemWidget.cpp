#include "TNMsgDetailItemWidget.h"
#include <QPen>
#include <QDebug>
#include <QTime>
#include <QCoreApplication>
#include <QTextDocument>
#include <QImageReader>
#include <QXmlStreamReader>
#include <QMovie>
#include <QTime>
#include <qfiledialog.h>
#include <qbuffer.h>
#include "emotion/TNEmojiSingleton.h"
#include "network/tnsendimsg.h"
#include "tnfilebrowser.h"
#include "tnothermessagebrowser.h"
#include "tnaudiobrowser.h"
#include "TNNoticeMessageOperate.h"
#include "TNMessageBox.h"
#include "TNUserDataHelper.h"
#include "TNHttpCloudApi.h"
#include "SendFowardSelectContactDialog.h"
#include "tnnotifycenter.h"
#include "TNPathUtil.h"
#include "tnimagectr.h"
#include "emotion/tnconvertrichedit.h"
#include "frames/TNFrameViewer.h"
#include "TNDataStatistics.h"
#include "TNMVD_global.h"
#include "image_progress_bar.h"
#include "TNUtil.h"

#define DEFAULT_MOVIE_WIDTH		96
#define DEFAULT_MOVIE_HEIGHT	96
#define SHOW_MAX_PIC_SIZE 3 * 1024 * 1024
#define DEFAULT_IMAGE_PATH "toonpc://image.png"


TNMsgDetailItemWidget::TNMsgDetailItemWidget(TNModelUserMessage* data,
	const QModelIndex& index, 
    const QSize& parentSize,
    QWidget *parent /* = 0 */,
	TNMsgDetailModel* detailModel /* = 0 */, 
	bool first_message /* = false */,
	bool time_visible /* = true */) :
QWidget(parent),
_rectAngleSpaceWidth(7),
_rectAngleSpaceHeight(7),
_labelTextTriangleWidth(10),
_messageSpaceToNext(20),
_labelTextSpaceToEnd(63),
_leftColor(0xFDFDFD),
_rightColor(0xF3F3F3),
_resizeFlag(false),
_labelText(NULL),
_fileBrowser(NULL),
_picProgress(NULL),
_isFirstMessage(first_message),
_isTimeVisible(time_visible),
_tnMsgDetailModel(detailModel),
_tnOtherMsgBrowser(NULL),
_tnAudioBrowser(NULL),
_tnLabelStatus(NULL),
_tnLabelStatusWidth(32),
_data(data),
_tnIndex(index),
_labelName(NULL),
_isCreateName(false),
_nameSpaceText(4)
{
	qRegisterMetaType<TNModelUserMessage>("TNModelUserMessage");
    connect(this, SIGNAL(createSendFinish(TNModelUserMessage,QModelIndex)),
        this, SLOT(onCreateSendFinished(TNModelUserMessage,QModelIndex)),
            Qt::QueuedConnection);
    connect(this, SIGNAL(createRecvFinish(TNModelUserMessage,QModelIndex)),
        this, SLOT(onCreateRecvFinished(TNModelUserMessage,QModelIndex)),
            Qt::QueuedConnection);
	connect(this, SIGNAL(downLoadAvatorIcon(TNModelUserMessage)),
        this, SLOT(onLoadAvatorIcon(TNModelUserMessage)), Qt::QueuedConnection);
    setParentSize(parentSize);
	init();
    setHeadpic(_data->GetPhotoIcon());

    decodeContent(_data);
}

TNMsgDetailItemWidget::~TNMsgDetailItemWidget()
{
	if (_labelPeople != NULL){
		delete _labelPeople;
		_labelPeople = NULL;
	}
	if (_labelText != NULL){
		_labelText->clear();
		delete _labelText;
		_labelText = NULL;
	}
	if (_labelTime != NULL){
		delete _labelTime;
		_labelTime = NULL;
	}
	if (_picProgress != NULL){
		delete _picProgress;
		_picProgress = NULL;
	}
	if (_fileBrowser != NULL){
		delete _fileBrowser;
		_fileBrowser = NULL;
	}
	if (_tnAudioBrowser != NULL){
		delete _tnAudioBrowser;
		_tnAudioBrowser = NULL;
	}
	if (_tnOtherMsgBrowser != NULL){
		delete _tnOtherMsgBrowser;
		_tnOtherMsgBrowser = NULL;
	}
	if (_tnLabelStatus != NULL){
		delete _tnLabelStatus;
		_tnLabelStatus = NULL;
	}
	if (_labelName != NULL){
		delete _labelName;
		_labelName = NULL;
	}
}

void TNMsgDetailItemWidget::setAavtorCustType()
{
    QString fromId = _data->getFromId();
	if (fromId.startsWith("c_")){
		_labelPeople->setCustType(cust_ellipse);
	}
	else if (fromId.startsWith("g_")){
		_labelPeople->setCustType(cust_hexagon);
	}
	else if (fromId.startsWith("gc_")){
		_labelPeople->setCustType(cust_radius);
	}
}

void TNMsgDetailItemWidget::init()
{
	_labelPeople = new TNAvatorButton(this);
    _labelPeople->setCursor(Qt::PointingHandCursor);
	_labelPeople->setObjectName("DetailItemAvatorButton");
	_labelPeople->setGeometry(_labelPeopleInitRect);
	_labelPeople->setSmallMask(TN::Small);
    connect(_labelPeople, SIGNAL(clicked()), this, SLOT(slotFeedFrame()));

	_labelTime = new QLabel(this);
	_labelTime->setObjectName("LabelMessageTime");
	resizeTimeCtr();
	resizeAvaCtr();
	getMaxTextWidth();
}

void TNMsgDetailItemWidget::setHeadpic(QString dir)
{
    _labelPeople->setAvatorImagePath(_data->GetPhotoIcon());
}

void TNMsgDetailItemWidget::paintEvent(QPaintEvent *e)
{
	switch (_messageType)
	{
	case em_text:
        paintEmojiAndText(e);
		break;
	case em_image:
        paintImage(e);
		break;
	case em_single_operate:
	case em_group_operate:
	case em_groupchat_notice:
	case em_notsupport:
    case em_card_not_exist:
    case em_red_card:
        paintNotifyText(e);
		break;
    default:
        break;
	}
}

void TNMsgDetailItemWidget::paintNotifyText(QPaintEvent* e)
{
	if (!_resizeFlag){
		_tnOtherMsgBrowser->paintEvent(e);
		resizeOtherMsgBrowser();
		_resizeFlag = true;
	}
}

void TNMsgDetailItemWidget::paintImage(QPaintEvent* e)
{
	if (!_resizeFlag){
		_labelText->paintEvent(e);
		resizeImage();
		_resizeFlag = true;
	}
}

void TNMsgDetailItemWidget::paintEmojiAndText(QPaintEvent* e)
{
	//显示调用TextEdit拿到高度、宽度
	if (!_resizeFlag){
		_labelText->paintEvent(e);
		createStatusLabel();
		resizeEmojiAndText();
		_resizeFlag = true;
	}
	
	QPainter painter(this);
	//在label_text外画矩形框
	QRectF rectangle(_labelText->geometry().left() - _rectAngleSpaceWidth,
		_labelText->geometry().top() - _rectAngleSpaceHeight,
		_labelText->width() + _rectAngleSpaceWidth * 2,
		_labelText->height() + _rectAngleSpaceHeight * 2);

	QPen pen;
    if (_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER)
	{
		pen.setColor(QColor(0xEBEDF0));
		painter.setBrush(QBrush(_leftColor));
	}
	else
	{
		pen.setColor(_rightColor);
		painter.setBrush(QBrush(_rightColor));
	}
	pen.setWidthF(0.8f);
	pen.setCapStyle(Qt::RoundCap);
	painter.setPen(pen);
	painter.drawRoundedRect(rectangle, 2, 2);
}

void TNMsgDetailItemWidget::createStatusLabel()
{
	if (_tnLabelStatus != NULL){
		return;
	}
	_tnLabelStatus = new TNStatusLabel(this);
	_tnLabelStatus->setFixedSize(QSize(_tnLabelStatusWidth, _tnLabelStatusWidth));
	//初始化状态框
    _tnLabelStatus->setData(_data);
	_tnLabelStatus->setModel(_tnMsgDetailModel);
	//图片文字发送接收状态
    switch (_data->getMsgSendOrRecv()){
	case MESSAGE_SEND:
        switch(_data->getMsgStatus()){
        case MSG_STATUS_SENDING:
        case MSG_STATUS_UNSEND:
        case MSG_STATUS_RESEND:
            _tnLabelStatus->setStatus(TNStatusLabel::em_loading);
            break;
        case MSG_STATUS_SEND_FAIL:
        case MSG_STATUS_SEND_FAIL_Card:
        case MSG_STATUS_SEND_FAIL_CoCard:
        case MSG_STATUS_SEND_FAIL_OrCard:
            _tnLabelStatus->setStatus(TNStatusLabel::em_failed);
            break;
        case MSG_STATUS_SEND_SUC:
            _tnLabelStatus->setStatus(TNStatusLabel::em_successed);
            break;
        default:
            break;
		}
		break;
    case MESSAGE_RECV:
        switch(_data->getMsgStatus()){
        case MSG_STATUS_SEND_SUC:
            switch(_data->getMsgFileStatus()){
            case MSG_STATUS_FILE_DOWNLOADING:
                _tnLabelStatus->setStatus(TNStatusLabel::em_loading);
                break;
            case MSG_STATUS_FILE_DOWN_FAIL:
                _tnLabelStatus->setStatus(TNStatusLabel::em_failed);
                break;
            case MSG_STATUS_FILE_UNDOWN:
            case MSG_STATUS_FILE_SUC:
                if(_data->GetMessageType() == em_image){
                    QString localPath = _data->getFileLocalPath();
                    QFile file(localPath);
                    if(file.exists()){
                        _tnLabelStatus->setStatus(TNStatusLabel::em_successed);
                    }else{
                        _tnLabelStatus->setStatus(TNStatusLabel::em_loading);
                    }
                }else{
                    _tnLabelStatus->setStatus(TNStatusLabel::em_successed);
                }
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        break;
        default:
		break;
	}
}

void TNMsgDetailItemWidget::decodeContent(TNModelUserMessage* data)
{
    _messageType = data->GetMessageType();
	setAavtorCustType();
    if (_data->getSessionType() == MSG_BIZ_GROUPCHAT &&
        _data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER){
        switch (_data->GetMessageType()){
		case em_text:
		case em_image:
		case em_file:
		case em_audio:
        case em_video:
			_isCreateName = true;
			break;
		default:
			break;
		}
	}
	calculationTextBrowser();
}

bool TNMsgDetailItemWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == _labelText){
        if(event->type() == QEvent::FocusIn){
            emit TNNotifyCenter::instance()->signalHideGroupChatMemberWidget();
        }
    }else if (watched == _labelText->viewport()){
        if (_messageType == em_image){
            QMouseEvent *pMouseEvent = dynamic_cast<QMouseEvent *>(event);
            if (nullptr != pMouseEvent && pMouseEvent->button() == Qt::LeftButton){
                if (event->type() == QEvent::MouseButtonPress){
                    _isMouseButtonPress = true;
                }
                else if (event->type() == QEvent::MouseButtonRelease){
                    if (_isMouseButtonPress){
                        showOrignalImage();
                    }
                    _isMouseButtonPress = false;
                }
                else if (event->type() == QEvent::MouseButtonDblClick){
                    showOrignalImage();
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void TNMsgDetailItemWidget::showOrignalImage()
{
    //如果原图未下载,在这里重新下载,补充机制(图片在创建item时会下载原图和缩略图,但是原图有可能会下载失败)
    if(!QFile::exists(_data->getFileLocalPath() + "_org"))
        TNSendIMsg::getInstance()->downLoadOrgImage(*_data);
    TNPictureViewerDialog *picViewer = TNPictureViewerDialog::getInstance();
	Q_ASSERT(picViewer);
    QList<TNPictureViewerDialog::PictureItem> picPathList;
    int nCurrentIndex = getPicList(picPathList);
    if (picViewer->isMinimized())
    {
        picViewer->showNormal();
    }
    else
    {
        picViewer->show();
    }
	connect(TNSendIMsg::getInstance(), SIGNAL(orig_image_finished(bool, QString, QString)), picViewer, SLOT(originalDownFinished(bool, QString, QString))
		, Qt::QueuedConnection); //此处应该用队列方式connect
    picViewer->activateWindow();
    picViewer->raise();
    picViewer->updatePictureList(picPathList, nCurrentIndex);
}

void TNMsgDetailItemWidget::createTextBrowser()
{
    _labelText = new TNGrowingTextBrowser(_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT,
                                          _data->GetMessageType() == em_image, this);
    _labelText->installEventFilter(this);
    _labelText->viewport()->installEventFilter(this);
    _labelText->setFixedWidth(_max_text_width);
	_labelText->setObjectName("GrowingTextBrowser");
	_labelText->setFrameStyle(QFrame::NoFrame);
    _labelText->setMessageType(_data->GetMessageType());
	_labelText->setLineWrapMode(QTextEdit::WidgetWidth);
    _labelText->setData(_data);
    if (_data->GetMessageType() == em_text){
		QPalette pal(_labelText->palette());
        if (_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER){
			pal.setColor(QPalette::Base, _leftColor);
		}else{
			pal.setColor(QPalette::Base, _rightColor);
		}
		_labelText->setAutoFillBackground(true);
		_labelText->setPalette(pal);
	}
	QObject::connect(_labelText, SIGNAL(actionRevote()), this, SLOT(onActionMsgRevoke()));
    QObject::connect(_labelText, SIGNAL(actionSendForward()), this, SLOT(onActionSendFoward()));
	QObject::connect(_labelText, SIGNAL(actionSaveAs()), this, SLOT(onActionSaveAs()));
	QObject::connect(_labelText, SIGNAL(actionDeleteMsg()), this, SLOT(onActionDeleteMsg()));
}

void TNMsgDetailItemWidget::setStatusLabel(bool success)
{
    if(_tnLabelStatus == NULL){
        return;
    }
    if (success){
        _tnLabelStatus->setStatus(TNStatusLabel::em_successed);
	}else{
		_tnLabelStatus->setStatus(TNStatusLabel::em_failed);
    }
}

void TNMsgDetailItemWidget::createFileBrowser()
{
    _fileBrowser = new TNFileBrowser(_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT,
        _data,
		_tnMsgDetailModel,
		this);
	resizeFileBrowser();
    connect(_fileBrowser, SIGNAL(actionRevote()), this, SLOT(onActionMsgRevoke()));
    connect(_fileBrowser, SIGNAL(actionSendForward()), this, SLOT(onActionSendFoward()));
    connect(_fileBrowser, SIGNAL(delFileMsg()), this, SLOT(onActionDeleteMsg()));
    connect(_fileBrowser, SIGNAL(cancelFileDownOrUploading(bool)), this, SLOT(onCancelFileDownOrUploading(bool)));
}

void TNMsgDetailItemWidget::calculationTextBrowser()
{
	createLabelName();
	switch (_messageType)
	{
	case em_file:
    case em_video:
        createFileBrowser();
		break;
	case em_text:
        createTextBrowser();
        calculationImageTextBrowser();
		break;
	case em_image:
	{
		QTime time;
		time.start();
		createTextBrowser();
        calculationImageBrowser();
		//notice 日志
        QString qs_log(QString("[Notice] [TNMsgDetailItemWidget] calculationImageBrowser take time:%1").arg(time.elapsed()));
        qInfo() << qs_log;
		break;
	}
	case em_audio:
		createAudioBrowser();
		break;
	case em_single_operate:
	case em_group_operate:
	case em_groupchat_notice:
	case em_notsupport:
    case em_card_not_exist:
    case em_red_card:
        createOtherMessageBrowser(_data->GetUserMessage(), _messageType);
		break;
	default:
		break;
	}
	//界面创建完成
    if (_data->getMsgSendOrRecv() == MESSAGE_SEND){
        emit createSendFinish(*_data,_tnIndex);
	}
    else if (_data->getMsgSendOrRecv() == MESSAGE_RECV &&
        (_data->GetMessageType() == em_image || _data->GetMessageType() == em_audio)){
        emit createRecvFinish(*_data,_tnIndex);
	}
	//是否下载头像
    if (!QFile::exists(_data->GetPhotoIcon())){
        emit downLoadAvatorIcon(*_data);
    }
    //notice 日志
    QString qs_log(QString("[Notice] [TNMsgDetailItemWidget] calculationTextBrowser end."));
    qInfo() << qs_log;
}

void TNMsgDetailItemWidget::calculationImageTextBrowser()
{
    QString data = _data->GetUserMessage();
    TNConvertRichEdit::reverseRichEdit(_labelText,data);
}

void TNMsgDetailItemWidget::adjustImage(int& width, int& height)
{
    if (width > (_max_text_width * 1 / 3)){
		int new_width = _max_text_width * 1 / 3;
		float rate = new_width * 1.0f / width;
		height = rate * height;
		width = new_width;
	}
    /*
    if (height > (_parentMaxheight * 2 / 3)){
        int new_height = _parentMaxheight * 1 / 3;
		float rate = new_height * 1.0f / height;
		width = rate * width;
		height = new_height;
	}
    */
}

void TNMsgDetailItemWidget::calculationImageBrowser()
{
    //创建progress
    if(_data->getMsgSendOrRecv() != MESSAGE_CONVERT){
        _picProgress = new image_progress_bar(this);
        _picProgress->setRange(0,100);
        _picProgress->setValue(0);
    }
    switch (_data->getMsgSendOrRecv())
    {
    case MESSAGE_RECV://下载数据(接收)
        dealDownloadData();
        break;
    case MESSAGE_SEND://上传数据(发送)
        dealUploadData();
        break;
    case MESSAGE_CONVERT://转发的数据
        dealConvertData();
        break;
    default:
        break;
    }
}

void TNMsgDetailItemWidget::dealConvertData()
{
    QString image_path = _data->getFileLocalPath();
    QString suffix = _data->getFileSuffix();
    if(suffix.isEmpty()){
        suffix = TNImageCtr::getImageType(image_path);
        _data->setFileSuffix(suffix);
    }
    QImage image;
    QSize pic_size;
    QFileInfo file_info(image_path);
    bool adjust_size = false;
    if(file_info.size() > SHOW_MAX_PIC_SIZE){
        adjust_size = true;
    }
    if(!speedLoadImage(image_path,suffix.mid(1),image,pic_size,adjust_size)){
        return;
    }
    _labelText->clear();
    insertImage("",image);
}

void TNMsgDetailItemWidget::dealUploadData()
{
    bool isUpLoaded = _data->getMsgFileStatus() == MSG_STATUS_FILE_SUC;
    QString image_path = _data->getFileLocalPath();
    QString suffix = _data->getFileSuffix();
    if(suffix.isEmpty()){
        suffix = TNImageCtr::getImageType(image_path);
        _data->setFileSuffix(suffix);
    }
    QImage image;
    QSize pic_size;
    QFileInfo file_info(image_path);
    bool adjust_size = false;
    if(file_info.size() > SHOW_MAX_PIC_SIZE){
        adjust_size = true;
    }
    if(_data->getFileSuffix().isEmpty())
        _data->setFileSuffix(TNImageCtr::getImageTypeRetString(image_path));
    if (!speedLoadImage(image_path, _data->getFileSuffix(), image, pic_size, adjust_size)){
        return;
    }
    qInfo() << "[Notice] [dealUploadData] image path:" << image_path;
    if (isUpLoaded){
        _labelText->clear();
        if (_picProgress != NULL){
            _picProgress->setVisible(false);
        }
        insertImage("",image);
    }else{
        switch(_data->getMsgFileStatus()){
        case MSG_STATUS_FILE_UPLOAD_FAIL:
            if (_picProgress != NULL){
                _picProgress->setVisible(false);
            }
            break;
        default:
            break;
        }
        _labelText->clear();
        insertImage("",image);
    }
}

void TNMsgDetailItemWidget::dealDownloadData()
{
    bool isLoaded = (_data->getMsgStatus() == MSG_STATUS_SEND_SUC &&
                     _data->getMsgFileStatus() == MSG_STATUS_FILE_SUC);
    QFile file(_data->getFileLocalPath());
    bool isExits = file.exists();
    if (isLoaded && isExits){
        QString image_path = _data->getFileLocalPath();
		if (!image_path.isEmpty()){

            _labelText->clear();
			if (_picProgress != NULL){
				_picProgress->setVisible(false);
			}
            insertImage(image_path);
        }
	}else{//没下载成功
        if(_data->getMsgFileStatus() == MSG_STATUS_FILE_DOWN_FAIL){
            _picProgress->hide();
        }
        int pre_image_width = _data->getPicSize().width();
        int pre_image_height = _data->getPicSize().height();


		QString image_path = ":/Resources/gray.jpg";
		QImage image(TNEmojiSingleton::GetInstance()->getGrayImage());
		if (image.isNull()){
			return;
		}
        QUrl Uri(DEFAULT_IMAGE_PATH);
		QTextCursor cursor = _labelText->textCursor();
		QTextImageFormat imageFormat;
		adjustImage(pre_image_width, pre_image_height);
        _data->setPicSize(QSize(pre_image_width, pre_image_height));

		imageFormat.setWidth(pre_image_width);
		imageFormat.setHeight(pre_image_height);

        if (_data->getFileSuffix().toUpper().contains(IMAGE_TYPE_GIF)){
			_labelText->InsertGifImage(image_path, image_path);
            imageFormat.setName(image_path);
            cursor.insertImage(imageFormat);
        }else{
			QTextDocument * textDocument = _labelText->document();
			textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant(image));
            imageFormat.setName(DEFAULT_IMAGE_PATH);
            cursor.insertImage(imageFormat);
        }
	}
}

void TNMsgDetailItemWidget::insertImage(QString image_path,const QImage& source)
{
    QImage image;
    QSize pic_size;
    if(source.isNull()){
        if(_data->getFileSuffix().isEmpty())
            _data->setFileSuffix(TNImageCtr::getImageTypeRetString(image_path));
        if (!speedLoadImage(image_path, _data->getFileSuffix(), image, pic_size, true)){
            return;
        }
    }else{
        image = source;
        pic_size = source.size();
    }
    QUrl Uri(DEFAULT_IMAGE_PATH);
    QTextCursor cursor = _labelText->textCursor();
    QTextImageFormat imageFormat;
    _data->setPicSize(pic_size);
    imageFormat.setWidth(pic_size.width());
    imageFormat.setHeight(pic_size.height());

    if (_data->getFileSuffix().toUpper().contains(IMAGE_TYPE_GIF)){
        image_path = _data->getFileLocalPath();
        imageFormat.setName(image_path);
        _labelText->InsertGifImage(image_path, image_path);
        cursor.insertImage(imageFormat);
        return;
    }
    QTextDocument * textDocument = _labelText->document();
    textDocument->addResource(QTextDocument::ImageResource, Uri, QVariant(image));
    imageFormat.setName(DEFAULT_IMAGE_PATH);
    cursor.insertImage(imageFormat);
}

void TNMsgDetailItemWidget::setTime(QString time)
{
	_labelTime->setText(time);
}

void TNMsgDetailItemWidget::setTimeVisble(bool flag /* = true */)
{
	_isTimeVisible = flag;
	_labelTime->setVisible(flag);
	//隐藏labeltime后,相应的坐标要减去labeltime的height
	if (!flag){
		_rightPeopleInitRect = QRect(_parentMaxwidth - 23 - 30, 0, 30, 30);
		_labelPeopleInitRect = QRect(15, 0, 30, 30);

        if (_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER){//左边
			_labelPeople->setGeometry(_labelPeopleInitRect);
		}
		else{//右边
			_labelPeople->setGeometry(_rightPeopleInitRect);
		}
	}
}

void TNMsgDetailItemWidget::updateImage(bool success, QString data)
{
    if (_data->getMsgSendOrRecv() == MESSAGE_RECV){
		if (success){
            _data->setFileLocalPath(data);
			QString image_path = data;
			if (!image_path.isEmpty()){
				QImage image;
				QSize pic_size;
                if(_data->getFileSuffix().isEmpty())
                    _data->setFileSuffix(TNImageCtr::getImageTypeRetString(image_path));
                if (!speedLoadImage(image_path, _data->getFileSuffix(), image, pic_size, true)){
					return;
				}
				///停止loading显示
				if (_picProgress != NULL)
					_picProgress->setVisible(false);
                if(_labelText != NULL){
                    _labelText->clear();
                    insertImage("",image);
                }
			}
        }else{
            if (_picProgress != NULL)
                _picProgress->hide();
        }
        //设置状态
        setStatusLabel(success);
    }else{
		if (success){
            _data->SetUserMessage(data);
			if (_picProgress != NULL){
				delete _picProgress;
				_picProgress = NULL;
			}
		}else{
			if (_picProgress != NULL)
				_picProgress->hide();
            //失败以后设置状态
            setStatusLabel(success);
        }
    }
}
void TNMsgDetailItemWidget::updateFile(bool success, QString file_path, QString msgId)
{
	if (_tnMsgDetailModel != NULL){
		_tnMsgDetailModel->updateFileData(msgId, file_path, success);
	}
}

void TNMsgDetailItemWidget::setMovieSize(const QRect& rect)
{
    QRect newRect = QRect(rect.left() + 4,rect.top() + 4,rect.width() - 7,rect.height() - 7);
    _picProgress->setGeometry(newRect);
}

void TNMsgDetailItemWidget::onCreateSendFinished(TNModelUserMessage data,QModelIndex q_index)
{
    Q_UNUSED(q_index);
	TNSendIMsg* pIm = TNSendIMsg::getInstance();
#ifdef QT_DEBUG
    QTime time;
    time.start();
#endif
    if(data.getMsgStatus() == MSG_STATUS_UNSEND ||
            data.getMsgStatus() == MSG_STATUS_RESEND)
        pIm->ProcessIMMSG(data);
#ifdef QT_DEBUG
    //notice log
    QString qs_log = "[Notice] [TNMsgDetailItemWidget] onCreateSendFinished ProcessIMMSG time:"
        + QString("%1").arg(time.elapsed());
    qDebug() << qs_log;
#endif
}

void TNMsgDetailItemWidget::onCreateRecvFinished(TNModelUserMessage data,QModelIndex q_index)
{
    Q_UNUSED(q_index);
	TNSendIMsg* pIm = TNSendIMsg::getInstance();
    if(data.getMsgStatus() != MSG_STATUS_SEND_SUC){
        return;
    }
    switch (data.getMsgFileStatus()) {
    case MSG_STATUS_FILE_DOWNLOADING:
    case MSG_STATUS_FILE_DOWN_FAIL:
    case MSG_STATUS_FILE_READED:
        return;
    case MSG_STATUS_FILE_SUC:{
        QString localPath = data.getFileLocalPath();
        QFile  file(localPath);
        if(file.exists()){
            return;
        }else{
            _tnMsgDetailModel->updateMsgFileStatus(data.GetMsgID(),
                MSG_STATUS_FILE_DOWNLOADING);
        }
    }
        break;
    default:
        break;
    }
    switch (data.GetMessageType()){
	case em_image:
        pIm->DownloadImage(data);
		break;
	case em_audio:
        pIm->DownloadAudio(data);
		break;
    default:
        break;
	}
}

void TNMsgDetailItemWidget::endProgressBar(bool success)
{
    _fileBrowser->endProgressBar(success);
    if(!success){
        setStatusLabel(success);
    }
}

void TNMsgDetailItemWidget::updateProgressBar(MESSAGE_TYPE type,int progress)
{
    switch(type){
    case em_file:
    case em_video:
        _fileBrowser->updateProgressBar(progress);
        break;
    case em_image:
        _picProgress->setValue(progress);
        break;
    default:
        break;
    }
}

void TNMsgDetailItemWidget::onFileDownloadFinish(bool success, QString file, QString msgId)
{
	_fileBrowser->onDownloadFinish(success, file, msgId);
    if(!success){
        setStatusLabel(success);
    }
}

bool TNMsgDetailItemWidget::speedLoadImage(const QString& image_path,
                                           const QString& image_type,
                                           QImage& image,
                                           QSize& pic_size,
                                           bool adjust)
{
    QFileInfo fileInfo(image_path);
    QImageReader image_reader(image_path, image_type.toStdString().c_str());
	if (!image_reader.canRead()){
		return false;
	}

	int image_width = image_reader.size().width();
	int image_height = image_reader.size().height();
    adjustImage(image_width, image_height);
    if (adjust){
        if(fileInfo.size() > SHOW_MAX_PIC_SIZE){
            image_reader.setQuality(50);
        }
    }
	image_reader.setScaledSize(QSize(image_width, image_height));
	pic_size.setWidth(image_width);
	pic_size.setHeight(image_height);

	image = image_reader.read();
	if (image.isNull()){
		return false;
	}
	return true;
}

void TNMsgDetailItemWidget::createOtherMessageBrowser(const QString& data, MESSAGE_TYPE type)
{
	if (_tnOtherMsgBrowser == NULL){
		_tnOtherMsgBrowser = new TNOtherMessageBrowser(this);
	}
	_labelPeople->hide();//隐藏头像
	if (type == em_notsupport){
		_tnOtherMsgBrowser->setMessage(tr(NOTSUPPORT_TEXT));
    }else if(type == em_red_card){
        _tnOtherMsgBrowser->setMessage(tr(RED_ENVELOPES));
	}else{
		_tnOtherMsgBrowser->setMessage(data);
	}
}

void TNMsgDetailItemWidget::createAudioBrowser()
{
	QTime time;
	time.start();
	if (_tnAudioBrowser == NULL){
        _tnAudioBrowser = new TNAudioBrowser(_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT,
                                             _data, _tnMsgDetailModel, this);
		resizeAudioBrowser();
	}
	//notice 日志
    QString qs_log(QString("[Notice] [TNMsgDetailItemWidget] createAudioBrowser take time:%1").arg(time.elapsed()));
    qInfo() << qs_log;
	QObject::connect(_tnAudioBrowser, SIGNAL(actionRevote()), this, SLOT(onActionMsgRevoke()));
	QObject::connect(_tnAudioBrowser, SIGNAL(actionDeleteMsg()), this, SLOT(onActionDeleteMsg()));
}

void TNMsgDetailItemWidget::stopPlay()
{
	_tnAudioBrowser->stopPlay();
}

void TNMsgDetailItemWidget::audioDownloadFinish(bool success,QString fileUrl)
{
	_tnAudioBrowser->downloadFinished(fileUrl, success);
}

void TNMsgDetailItemWidget::onLoadAvatorIcon(TNModelUserMessage data)
{
	TNSendIMsg* pIm = TNSendIMsg::getInstance();
    pIm->DownloadAvatar(data.getAvatorUrl(),data.getFromId(),
                        data.GetMsgID(),data.GetPhotoIcon());
}

void TNMsgDetailItemWidget::onActionMsgRevoke()
{
    //埋点
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_NoticeDetail_Revert,
        TNUserDataHelper::GetInstance()->_pluginParam);
    qint64 time = qAbs(QDateTime::currentDateTime().secsTo(_data->getTime()));
	if (time >120){
        //超时，无法撤回
        MESSAGE_TYPE type = _data->getSessionType() == MSG_BIZ_SINGLECHAT
			? em_single_operate : em_group_operate;
        emit sendRevokeSignal(0, type, _data->getTime().toMSecsSinceEpoch(),
                              _data->getSessionId(), _data->GetMsgID(), "");
		return;
	}
    TNNoticeMessageOperate::GetInstance()->ProcessMsgRevokeAction(_data);
}

void TNMsgDetailItemWidget::onActionSendFoward()
{
    //埋点
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_NoticeDetail_SendForward,
        TNUserDataHelper::GetInstance()->_pluginParam);

    emit TNNotifyCenter::instance()->signalHideGroupChatMemberWidget();
    QString belongFeedId = _data->getMyFeedId();
    Q_ASSERT(!belongFeedId.isEmpty());
    SendFowardSelectContactDialog *pDialog = SendFowardSelectContactDialog::getInstance();
    TNUtil::moveCenterInMainWidget(pDialog);
    pDialog->setData(belongFeedId);
    pDialog->setWindowModality(Qt::ApplicationModal);
    connect(pDialog,
        SIGNAL(selectFinished(QList<TNMessageListAdapter>, QList<TNFriend>, QList<TNStructGroupChat>)),
        this,
        SLOT(onSelectContactFinised(QList<TNMessageListAdapter>, QList<TNFriend>, QList<TNStructGroupChat>))
        );
    pDialog->show();
}

void TNMsgDetailItemWidget::onSelectContactFinised(QList<TNMessageListAdapter> selectSessions,
                                                   QList<TNFriend> selectFriendList,
                                                   QList<TNStructGroupChat> selectGroupChats)
{
	//结构：feedid， msgid
    QMap<QString, QString> feedList;
    QList<TNMessageListAdapter> msgListAdapter;

    for (int i = 0; i < selectSessions.size(); ++i)
    {
        const TNMessageListAdapter &item = selectSessions[i];

        QString from = item.getMyFeedId();
        QString to = item.getToFeed();
        QString sessionId = item.getSessionId();
        if (sessionId == _data->getSessionId())
        {
            TNModelUserMessage *message = new TNModelUserMessage();
            *message = *_data;
            message->SetMsgID(TNIMCoreClient::GetMsgId());
            message->setFromId(from);
            message->setTime();
            message->setMessageSendFrom(GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT);
            message->setAvatorUrl(item.getAvatarPhotoUrl());
            message->SetPhotoIcon(TNPathUtil::getFeedAvatarPath(from));
            message->setMsgSendOrRecv(MESSAGE_CONVERT);
            //向当前会话转发时
            if(!_tnMsgDetailModel->insertData(_tnMsgDetailModel->rowCount(), message)){
                delete message;
                continue;
            }
            feedList[to] = message->GetMsgID();
        }
        else
            feedList[to] = TNIMCoreClient::GetMsgId();
        TNMessageListAdapter tempMessageListAdapter(sessionId, MSG_BIZ_GROUPCHAT);
        tempMessageListAdapter.setPhotoResID(item.getAvatarPhotoUrl());
        tempMessageListAdapter.setName(item.getName());
        tempMessageListAdapter.setMyFeedId(from);
        tempMessageListAdapter.setUserId(_data->getUserId());
        tempMessageListAdapter.setToFeed(to);
        switch (_data->GetMessageType())
        {
        case em_text:
            tempMessageListAdapter.setLastMessage(_data->GetUserMessage());
            break;
        case em_file:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_FILE_LAST_MESSAGE));
            break;
        case em_image:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_IMAGE_LAST_MESSAGE));
            break;
        case em_audio:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_AUDIO_LAST_MESSAGE));
            break;
        case em_video:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_VIDEO_LAST_MESSAGE));
            break;
        default:
            break;
        }
        QDateTime curTime = QDateTime::currentDateTime();
        tempMessageListAdapter.setTime(curTime.toTime_t());
        msgListAdapter.push_back(tempMessageListAdapter);
    }

    for (int i = 0; i < selectFriendList.size(); i++)
    {
        const TNFriend &item = selectFriendList[i];
        QString from = item.m_belongFeedId;
        QString to = item.m_friendFeedId;
        QString usrId = item.m_userId;
        QString usrName = item.m_nickName;
        QString sessionId = TNIMCoreClient::GetSessionId(from, to, MSG_BIZ_SINGLECHAT);
		if (sessionId == _data->getSessionId())
		{
			TNModelUserMessage *message = new TNModelUserMessage();
			*message = *_data;
			message->SetMsgID(TNIMCoreClient::GetMsgId());
			message->setFromId(from);
            message->setToFeedId(to);
            message->setUserId(usrId);
            message->SetFeedName(usrName);
			message->setTime();
			message->setMsgSendOrRecv(MESSAGE_CONVERT);
			message->setMessageSendFrom(GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT);
			message->SetPhotoIcon(TNPathUtil::getFeedAvatarPath(from));
			//向当前会话转发时
            if(!_tnMsgDetailModel->insertData(_tnMsgDetailModel->rowCount(), message)){
                delete message;
                continue;
            }
			feedList[item.m_friendFeedId] = message->GetMsgID();
		}
		else
			feedList[item.m_friendFeedId] = TNIMCoreClient::GetMsgId();
        TNMessageListAdapter tempMessageListAdapter(sessionId, MSG_BIZ_SINGLECHAT);
        tempMessageListAdapter.setPhotoResID(item.m_avatarResourceFile);
        tempMessageListAdapter.setName(item.m_nickName);
        tempMessageListAdapter.setMyFeedId(from);
        tempMessageListAdapter.setUserId(item.m_userId);
        tempMessageListAdapter.setToFeed(to);
        tempMessageListAdapter.setAvatarPhotoUrl(item.m_avatarURL);
        QDateTime curTime = QDateTime::currentDateTime();
        tempMessageListAdapter.setTime(curTime.toTime_t());
        switch (_data->GetMessageType())
        {
        case em_text:
            tempMessageListAdapter.setLastMessage(_data->GetUserMessage());
            break;
        case em_file:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_FILE_LAST_MESSAGE));
            break;
        case em_image:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_IMAGE_LAST_MESSAGE));
            break;
        case em_audio:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_AUDIO_LAST_MESSAGE));
            break;
        case em_video:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_VIDEO_LAST_MESSAGE));
            break;
        default:
            break;
        }
        msgListAdapter.push_back(tempMessageListAdapter);
    }

    for (int i = 0; i < selectGroupChats.size(); i++)
    {
        const TNStructGroupChat &item = selectGroupChats[i];

        QString from = item.m_groupChatFeed->GetMyFeedId();
        QString to = item.m_groupChatFeed->GetTopic();
        QString sessionId = TNIMCoreClient::GetSessionId(from, to, MSG_BIZ_GROUPCHAT);
        if (sessionId == _data->getSessionId())
        {
            TNModelUserMessage *message = new TNModelUserMessage();
            *message = *_data;
            message->SetMsgID(TNIMCoreClient::GetMsgId());
            message->setFromId(from);
            message->setTime();
            message->setMessageSendFrom(GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT);
            message->setAvatorUrl(item.m_groupChatFeed->GetHeaderImage());
            message->SetPhotoIcon(TNPathUtil::getFeedAvatarPath(from));
            message->setMsgSendOrRecv(MESSAGE_CONVERT);
            //向当前会话转发时
            if(!_tnMsgDetailModel->insertData(_tnMsgDetailModel->rowCount(), message)){
                delete message;
                continue;
            }
			feedList[item.m_groupChatFeed->GetGroupId()] = message->GetMsgID();
        }
		else
			feedList[item.m_groupChatFeed->GetGroupId()] = TNIMCoreClient::GetMsgId();
        TNMessageListAdapter tempMessageListAdapter(sessionId, MSG_BIZ_GROUPCHAT);
        tempMessageListAdapter.setPhotoResID(item.m_groupChatFeed->GetHeaderImage());
        tempMessageListAdapter.setName(item.m_groupChatFeed->GetName());
        tempMessageListAdapter.setMyFeedId(from);
        tempMessageListAdapter.setUserId(_data->getUserId());
        tempMessageListAdapter.setToFeed(to);
        switch (_data->GetMessageType())
        {
        case em_text:
            tempMessageListAdapter.setLastMessage(_data->GetUserMessage());
            break;
        case em_file:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_FILE_LAST_MESSAGE));
            break;
        case em_image:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_IMAGE_LAST_MESSAGE));
            break;
        case em_audio:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_AUDIO_LAST_MESSAGE));
            break;
        case em_video:
            tempMessageListAdapter.setLastMessage(tr(DEFAULT_VIDEO_LAST_MESSAGE));
            break;
        default:
            break;
        }
        QDateTime curTime = QDateTime::currentDateTime();
        tempMessageListAdapter.setTime(curTime.toTime_t());
        msgListAdapter.push_back(tempMessageListAdapter);
    }

    TNNoticeMessageOperate::GetInstance()->ProcessMsgForwordAction(_data, feedList);
    TNNotifyCenter::instance()->postNotifySendForward(msgListAdapter);

    TNMessageBox messagebox(this);
    messagebox.setObjectName("sendFowardMsg");
    messagebox.setFixedSize(100,100);
    messagebox.setMsg(("已转发"));
    messagebox.exec();
}
int TNMsgDetailItemWidget::getPicList(QList<TNPictureViewerDialog::PictureItem> &picList)
{
    TNModelUserMessage *pMsg = nullptr;
    int nCurrentIndex = -1;
    for (int i = 0; i < _tnMsgDetailModel->rowCount(); i++)
    {
        QModelIndex index = _tnMsgDetailModel->index(i, 0);
        if (index.isValid())
        {
            pMsg = reinterpret_cast<TNModelUserMessage *>(_tnMsgDetailModel->data(index).toLongLong());
            if (pMsg->GetMessageType() == em_image)
            {
                QString strPicPath = pMsg->getFileLocalPath();
                if (strPicPath.isEmpty())
                {
                    picList.push_back({ pMsg->GetMsgID(), pMsg->GetUserMessage(), false });
                }
                else
                {
                    picList.push_back({ pMsg->GetMsgID(), strPicPath, true });
                }
                if (pMsg->GetMsgID() == _data->GetMsgID())
                {
                    nCurrentIndex = picList.size() - 1;
                }
            }
        }
    }
    return nCurrentIndex;
}

void TNMsgDetailItemWidget::reSize(const QSize& size)
{
    setParentSize(size);
	getMaxTextWidth();
	resizeTimeCtr();
	resizeAvaCtr();
	resizeLabelName();
    switch (_data->GetMessageType())
	{
	case em_text:
		resizeEmojiAndText();
		break;
	case em_image:
		resizeImage();
		break;
	case em_file:
		resizeFileBrowser();
		break;
	case em_audio:
		resizeAudioBrowser();
		break;
	case em_groupchat_notice:
	case em_notsupport:
	case em_group_operate:
	case em_single_operate:
    case em_red_card:
		resizeOtherMsgBrowser();
		break;
	default:
		break;
	}
}

void TNMsgDetailItemWidget::setParentSize(const QSize &size)
{
    _parentMaxwidth = size.width();
    _parentMaxheight = size.height();
    this->setFixedWidth(_parentMaxwidth);
}

void TNMsgDetailItemWidget::resizeTimeCtr()
{
	if (_labelTime == NULL){
		return;
	}
	if (_isFirstMessage){
        _labelTime->setGeometry(_parentMaxwidth / 2 - 70, _messageSpaceToNext, 140, 15);
		_rightPeopleInitRect = QRect(_parentMaxwidth - 23 - 30, 32 + _messageSpaceToNext, 30, 30);
		_labelPeopleInitRect = QRect(15, 32 + _messageSpaceToNext, 30, 30);
	}
	else{
        _labelTime->setGeometry(_parentMaxwidth / 2 - 70, 0, 140, 15);
		_rightPeopleInitRect = QRect(_parentMaxwidth - 23 - 30, 32, 30, 30);
		_labelPeopleInitRect = QRect(15, 32, 30, 30);

		//是否隐藏掉时间
		setTimeVisble(_isTimeVisible);
	}

	_labelTime->setAlignment(Qt::AlignCenter);
}

void TNMsgDetailItemWidget::resizeAvaCtr()
{
	if (_labelPeople == NULL){
		return;
	}
    if (_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER){//左边
		_labelPeople->setGeometry(_labelPeopleInitRect);
	}
	else{//右边
		_labelPeople->setGeometry(_rightPeopleInitRect);
	}
}

void TNMsgDetailItemWidget::createLabelName()
{
	if (_isCreateName){
		_labelName = new QLabel(this);
		_labelName->setObjectName("detailFeedName");
		_labelName->setWordWrap(false);
        if(!_data->getRemark().isEmpty()){
            _labelName->setText(_data->getRemark());
        }else{
            _labelName->setText(_data->GetFeedName());
        }
		_labelName->adjustSize();
		_labelName->setAlignment(Qt::AlignLeft);
		resizeLabelName();
	}
}

void TNMsgDetailItemWidget::updateSendName()
{
    if(_isCreateName){
        Q_ASSERT(_labelName);
        if(!_data->getRemark().isEmpty()){
            _labelName->setText(_data->getRemark());
        }else{
            _labelName->setText(_data->GetFeedName());
        }
        resizeLabelName();
    }
}

void TNMsgDetailItemWidget::resizeLabelName()
{
	if (_labelName != NULL && _isCreateName){
		QRect rect(_labelPeopleInitRect.width() + _labelTextTriangleWidth + _labelPeopleInitRect.left(),
			_labelPeopleInitRect.top(),//保证外层矩形框和_labelPeople top对齐
			_labelName->width(),
			_labelName->height());
		_labelName->setGeometry(rect);
	}
}

void TNMsgDetailItemWidget::getMaxTextWidth()
{
	//当前label控件显示最大的宽度为tableview(detailarea);
	int max_width = 690;//_parentMaxwidth;
	//注意间隔width=画聊天消息时的三角边长 + 在label_text外层画矩形框到label_text的距离
	int space_width = _labelTextTriangleWidth + _rectAngleSpaceWidth;
	//label_text最大宽度=label控件最大宽度-_labelPeople宽度-labelText和labelPeople之间隔-
	_max_text_width = max_width - _labelPeopleInitRect.width()
		- space_width - _labelPeopleInitRect.left() - _labelTextSpaceToEnd
		- _rectAngleSpaceWidth;
}

void TNMsgDetailItemWidget::resizeEmojiAndText()
{
	if (_labelText == NULL){
		return;
	}
	//注意间隔width=画聊天消息时的三角边长 + 在label_text外层画矩形框到label_text的距离
	int space_width = _labelTextTriangleWidth + _rectAngleSpaceWidth;
    if (_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER){
		QRect rect;
		if (!_isCreateName){
			rect = QRect(_labelPeopleInitRect.width() + space_width + _labelPeopleInitRect.left(),
				_labelPeopleInitRect.top() + _rectAngleSpaceHeight,//保证外层矩形框和_labelPeople top对齐
				_labelText->width(), _labelText->height());
		}else{
			rect = QRect(_labelPeopleInitRect.width() + space_width + _labelPeopleInitRect.left(),
				_labelName->geometry().bottom() + _rectAngleSpaceHeight + _nameSpaceText,
				_labelText->width(), _labelText->height());
		}
		_labelText->setGeometry(rect);
		resizeStatusLabel(rect);
	}else{
		QRect rect(_rightPeopleInitRect.left() - space_width - _labelText->width(),
			_rightPeopleInitRect.top() + _rectAngleSpaceHeight,
			_labelText->width(), _labelText->height());
		
		_labelText->setGeometry(rect);
		resizeStatusLabel(rect);
	}
	if (!_resizeFlag){
		int auto_height = 0;
		if (!_isCreateName){
			auto_height = _labelText->height() + 2 * _rectAngleSpaceHeight +
				_labelPeople->geometry().top() + _messageSpaceToNext;
		}else{
			auto_height = _labelText->height() + 2 * _rectAngleSpaceHeight +
				_labelPeople->geometry().top() + _messageSpaceToNext +
				_labelName->height() + _nameSpaceText;
		}
		this->setFixedHeight(auto_height);
		emit autoHeight(auto_height, _tnIndex);
	}
}

void TNMsgDetailItemWidget::resizeStatusLabel(const QRect& rect)
{
	if (_tnLabelStatus == NULL){
		return;
	}
	QRect statusRect;
	///////////////////////////////////////////
    if (_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_CURRENT_ACCOUNT){
		statusRect = QRect(rect.left() - _labelTextTriangleWidth - _tnLabelStatusWidth - 2,
			rect.top() + (rect.height() / 2) - (_tnLabelStatusWidth / 2),
			_tnLabelStatusWidth, _tnLabelStatusWidth);
		_tnLabelStatus->setGeometry(statusRect);
	}
	else{
		statusRect = QRect(rect.right() + _labelTextTriangleWidth + 2,
			rect.top() + (rect.height() / 2) - (_tnLabelStatusWidth / 2),
			_tnLabelStatusWidth, _tnLabelStatusWidth);
		_tnLabelStatus->setGeometry(statusRect);
	}
}

void TNMsgDetailItemWidget::resizeImage()
{
	if (_labelText == NULL){
		return;
	}
	//注意间隔width=画聊天消息时的三角边长
	int space_width = _labelTextTriangleWidth;
    if (_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER){
		QRect rect;
		if (!_isCreateName){
			rect = QRect(_labelPeopleInitRect.width() + space_width + _labelPeopleInitRect.left() - 3,
				_labelPeopleInitRect.top() - 3,//保证外层矩形框和_labelPeople top对齐
				_labelText->width(), _labelText->height());
		}
		else{
			rect = QRect(_labelPeopleInitRect.width() + space_width + _labelPeopleInitRect.left() - 3,
				_labelName->geometry().bottom() + _nameSpaceText - 3,
				_labelText->width(), _labelText->height());
		}
		_labelText->setGeometry(rect);
		if (_picProgress != NULL){//显示loading
			setMovieSize(rect);
		}
		createStatusLabel();
		resizeStatusLabel(rect);
	}else{
		QRect rect(_labelPeople->geometry().left() - space_width - _labelText->width() + 3,
			_labelPeopleInitRect.top() - 3,
			_labelText->width(), _labelText->height());
		_labelText->setGeometry(rect);
		if (_picProgress != NULL){//显示loading
			setMovieSize(rect);
		}
		createStatusLabel();
		resizeStatusLabel(rect);
	}
	if (!_resizeFlag){
		int auto_height = 0;
		if (!_isCreateName){
			auto_height = _labelText->height() + _labelPeople->geometry().top()
				+ _messageSpaceToNext;
		}
		else{
			auto_height = _labelText->height() + _labelPeople->geometry().top()
				+ _messageSpaceToNext + _labelName->height() + _nameSpaceText;
		}
		this->setFixedHeight(auto_height);
		emit autoHeight(auto_height, _tnIndex);
	}
}

void TNMsgDetailItemWidget::resizeFileBrowser()
{
	QRect statusRect;
    if (_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER)
	{
		QRect rect;
		if (!_isCreateName){
			rect = QRect(_labelPeopleInitRect.right() + _labelTextTriangleWidth,
				_labelPeopleInitRect.top(),
				_fileBrowser->width(),
				_fileBrowser->height());
		}
		else{
			rect = QRect(_labelPeopleInitRect.right() + _labelTextTriangleWidth,
				_labelName->geometry().bottom() + _nameSpaceText,
				_fileBrowser->width(),
				_fileBrowser->height());
		}
		_fileBrowser->setGeometry(rect);
		statusRect = rect;
	}
	else
	{
		QRect rect(_rightPeopleInitRect.left() - _labelTextTriangleWidth - _fileBrowser->width(),
			_labelPeopleInitRect.top(),
			_fileBrowser->width(),
			_fileBrowser->height());
		_fileBrowser->setGeometry(rect);
		statusRect = rect;
	}
    if (_data->getMsgSendOrRecv() == MESSAGE_SEND){
		createStatusLabel();
		resizeStatusLabel(statusRect);
	}
	int auto_height = 0;
	if (!_isCreateName)
		auto_height = _fileBrowser->height() + _labelPeopleInitRect.top()
		+ _messageSpaceToNext;
	else
		auto_height = _fileBrowser->height() + _labelPeopleInitRect.top()
		+ _messageSpaceToNext + _labelName->height() + _nameSpaceText;
	this->setFixedHeight(auto_height);
}

void TNMsgDetailItemWidget::resizeAudioBrowser()
{
    if (_data->getMessageSendFrom() == GROUP_MESSAGE_TYPE_OTHER){
		QRect rect;
		if (!_isCreateName){
			rect = QRect(_labelPeopleInitRect.right() + _labelTextTriangleWidth,
				_labelPeopleInitRect.top(),
				_tnAudioBrowser->width(),
				_tnAudioBrowser->height());
		}
		else{
			rect = QRect(_labelPeopleInitRect.right() + _labelTextTriangleWidth,
				_labelName->geometry().bottom() + _nameSpaceText,
				_tnAudioBrowser->width(),
				_tnAudioBrowser->height());
		}
		_tnAudioBrowser->setGeometry(rect);
	}
	else{
		QRect rect(_rightPeopleInitRect.left() - _labelTextTriangleWidth - _tnAudioBrowser->width(),
			_labelPeopleInitRect.top(),
			_tnAudioBrowser->width(),
			_tnAudioBrowser->height());
		_tnAudioBrowser->setGeometry(rect);
	}
	int auto_height = 0;
	if (!_isCreateName)
		auto_height = _tnAudioBrowser->height() + _labelPeopleInitRect.top()
		+ _messageSpaceToNext;
	else
		auto_height = _tnAudioBrowser->height() + _labelPeopleInitRect.top()
		+ _messageSpaceToNext + _labelName->height() + _nameSpaceText;
	this->setFixedHeight(auto_height);
}

void TNMsgDetailItemWidget::resizeOtherMsgBrowser()
{
	int left_to = (_parentMaxwidth - _tnOtherMsgBrowser->width()) / 2;

	QRect rect(left_to,
		_labelPeopleInitRect.top(),
		_tnOtherMsgBrowser->width(),
		_tnOtherMsgBrowser->height());

	_tnOtherMsgBrowser->setGeometry(rect);

	int auto_height = _tnOtherMsgBrowser->height() +
		_labelPeopleInitRect.top() + _messageSpaceToNext;
	this->setFixedHeight(auto_height);
	if (!_resizeFlag)
		emit autoHeight(auto_height, _tnIndex);
}

void TNMsgDetailItemWidget::onActionSaveAs()
{
    QString srcFile = _data->getFileLocalPath();
    Q_ASSERT(srcFile.size() > 4);
    if(srcFile.right(4) != "_org"){
        srcFile += "_org";
    }
    QString defalutDir = TNPathUtil::getUserRecFile();
    QString suffix = TNImageCtr::getImageTypeRetString(srcFile);
    QString defaltName = ("toon图片") + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");;
    QString desPath = QFileDialog::getSaveFileName(
        this,
        ("文件另存为"),
        defalutDir + defaltName,
        QString("Config Files (*%1)").arg(suffix)
        );

    if (TNImageCtr::getImageType(srcFile) != TN::ImageType::nothing) //图片
    {
		QString original_image;
        original_image = srcFile;
        if (QFile::exists(original_image))
        {
            copyFileToPath(original_image, desPath, true);
        }
    }
	Q_ASSERT("Never here");
}
void TNMsgDetailItemWidget::onActionDeleteMsg()
{
    //埋点
    TNDataStatistics::RecordFuncStatisData(FUNC_TYPE_NoticeDetail_Del,
        TNUserDataHelper::GetInstance()->_pluginParam);
    emit deleteMsgSignal(_data->GetMsgID());
}
void TNMsgDetailItemWidget::slotFeedFrame()
{
    emit TNNotifyCenter::instance()->signalHideGroupChatMemberWidget();
    QString currentFeedId = _data->getFromId();
    QString belongFeedId = _data->getMyFeedId();
    TNFrameViewer::instance()->showFrame(currentFeedId, belongFeedId);
}
bool TNMsgDetailItemWidget::copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
{
	toDir.replace("\\", "/");
	if (sourceDir == toDir)
		return true;
	if (!QFile::exists(sourceDir))
		return false;
	if (QFile::exists(toDir)){
		if (coverFileIfExist){
			QFile::remove(toDir);
		}
	}
	if (!QFile::copy(sourceDir, toDir))
		return false;
	return true;
}

void TNMsgDetailItemWidget::onCancelFileDownOrUploading(bool upload)
{
    if(upload)
        emit deleteMsgSignal(_data->GetMsgID());
    else{
        emit jumpToMsg(_data->GetMsgID());
    }
}
