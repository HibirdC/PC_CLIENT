#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QToolTip>
#include <QLabel>
#include <QTimer>
#include <QMovie>
#include <QFileDialog>
#include <QDateTime>
#include "TNPictureViewerDialog.h"
#include "TNPathUtil.h"
#include "tnimagectr.h"
#include "TNHttpCloudApi.h"
#include "TNUserDataHelper.h"
#include "TNResizerDecorator.h"
#include "TNVersionInfo.h"

//方案一
//以下下载相关代码即将废弃，因为图片消息已经改成即使下载，查看大图时不会再跑以下代码
//但是为了能查看历史还未下载的图片，暂时留着，后续删除
//方案二2017.12.29
//在消息中同时下载大图和缩略图，如果在点击看大图时， 未下载完成，先显示缩略图 。大图浏览器直接转圈，等待下载完成（不参与下载）
//在槽orig_image_finished中响应下完大图
#define defalutSuffix ".jpg"

TNPictureViewerDialog * TNPictureViewerDialog::s_Instance = nullptr;
TNPictureViewerDialog * TNPictureViewerDialog::getInstance()
{
    if (s_Instance == nullptr)
    {
        s_Instance = new TNPictureViewerDialog(nullptr);
    }
    return s_Instance;
}

void TNPictureViewerDialog::freeInstance()
{
    if (s_Instance != nullptr)
    {
        delete s_Instance;
        s_Instance = nullptr;
    }
}

TNPictureViewerDialog::TNPictureViewerDialog(QWidget *parent)
    : DropShadowWidget(parent)
    , m_rotateAngle(0)
    , m_isFirstPicture(true)
    , m_nCurrentPicIndex(-1)
    , m_dImageHeight(0)
    , m_dImageWidth(0)
    , m_pLoadingMovie(nullptr)
    , m_httpCloudApi(nullptr)
    , m_bCanSwitchNextPic(true)
	, m_isNeedPaint(false)
	, m_isPictureBeyondClient(false)
	, m_isPressAtPicture(false)
{
	setAttribute(Qt::WA_QuitOnClose, false);
	setWindowTitle(("图片浏览器"));
    //主布局：竖直布局
    QVBoxLayout * pMainLayout = new QVBoxLayout(this);
	pMainLayout->setSpacing(0);
	pMainLayout->setContentsMargins(0,10,0,0);
    setLayout(pMainLayout);

    //顶部关闭按钮所在水平布局
    QHBoxLayout * pTopHLayout = new QHBoxLayout(this);
#ifdef Q_OS_WIN
    pTopHLayout->setAlignment(Qt::AlignRight);
    pTopHLayout->setContentsMargins(0, 0, 10, 5);
    pTopHLayout->setSpacing(0);
#else
    pTopHLayout->setAlignment(Qt::AlignLeft);
    pTopHLayout->setContentsMargins(15, 0, 0, 5);
    pTopHLayout->setSpacing(20);
#endif
	pTopHLayout->setObjectName("pictureTop");
    pMainLayout->addLayout(pTopHLayout);

    m_minBtn = new QPushButton(this);
    m_minBtn->setContentsMargins(0, 0, 0, 0);
    m_minBtn->setToolTip(("最小化")); 
    m_minBtn->setMouseTracking(true);

    m_maxBtn = new QPushButton(this);
    m_maxBtn->setContentsMargins(0, 0, 0, 0);
    m_maxBtn->setToolTip(("最大化")); 
    m_maxBtn->setCheckable(true);
    m_maxBtn->setChecked(false);
    m_maxBtn->setMouseTracking(true);

    m_closeBtn = new QPushButton(this);
    m_closeBtn->setContentsMargins(0, 0, 0, 0);
    m_closeBtn->setToolTip(("关闭")); 
    m_closeBtn->setMouseTracking(true);

#ifdef Q_OS_WIN
    m_minBtn->setObjectName("pictureMinButton");
    m_maxBtn->setObjectName("pictureMaxButton");
    m_closeBtn->setObjectName("pictureCloseButton");
    pTopHLayout->addWidget(m_minBtn);
    pTopHLayout->addWidget(m_maxBtn);
    pTopHLayout->addWidget(m_closeBtn);
#else
    m_minBtn->setObjectName("macMin");
    m_maxBtn->setObjectName("macMax");
    m_closeBtn->setObjectName("macClose");
    pTopHLayout->addWidget(m_closeBtn);
    pTopHLayout->addWidget(m_minBtn);
    pTopHLayout->addWidget(m_maxBtn);
#endif

    //中间的图片显示控件 
    m_picViewer = new QLabel(this);
    m_picViewer->setAlignment(Qt::AlignCenter);
    m_picViewer->setMinimumSize(200, 200);
    m_picViewer->installEventFilter(this);
    m_picViewer->setObjectName("pictureViewer");
    m_picViewer->setContentsMargins(0, 0, 0, 0);
    m_picViewer->setMouseTracking(true);
    pMainLayout->addWidget(m_picViewer);

    //底部放大、缩小等按钮所在水平布局
	QVBoxLayout *pBtmVLayout = new QVBoxLayout(this);
	pBtmVLayout->setAlignment(Qt::AlignHCenter);
	pMainLayout->addLayout(pBtmVLayout);
	QHBoxLayout *pBtmWidgetLayout = new QHBoxLayout(this);
    pBtmWidgetLayout->setSpacing(0);
	pBtmWidgetLayout->setContentsMargins(0,5,0,0);
    pBtmWidgetLayout->setAlignment(Qt::AlignHCenter);
	
	m_pBtmBtnWidget = new QWidget(this);
    m_pBtmBtnWidget->setMouseTracking(true);
	m_pBtmBtnWidget->setFixedSize(260, 40);
	m_pBtmBtnWidget->setObjectName("pictureFoot");
	m_pBtmBtnWidget->setLayout(pBtmWidgetLayout);
	pBtmVLayout->addWidget(m_pBtmBtnWidget);
	pMainLayout->addLayout(pBtmVLayout);

    m_zoomInBtn = new QPushButton(this);
    m_zoomInBtn->setObjectName("zoomInButton");
    m_zoomInBtn->setContentsMargins(0, 0, 0, 0);
    m_zoomInBtn->setToolTip(("放大")); 
    pBtmWidgetLayout->addWidget(m_zoomInBtn);

    m_zoomOutBtn = new QPushButton(this);
    m_zoomOutBtn->setObjectName("zoomOutButton");
    m_zoomOutBtn->setContentsMargins(0, 0, 0, 0);
    m_zoomOutBtn->setToolTip(("缩小")); 
    pBtmWidgetLayout->addWidget(m_zoomOutBtn);

    m_rotateBtn = new QPushButton(this);
    m_rotateBtn->setObjectName("rotateButton");
    m_rotateBtn->setContentsMargins(0, 0, 0, 0);
    m_rotateBtn->setToolTip(("旋转"));  
    pBtmWidgetLayout->addWidget(m_rotateBtn);

    m_saveAsBtn = new QPushButton(this);
    m_saveAsBtn->setObjectName("savePictureButton");
    m_saveAsBtn->setContentsMargins(0, 0, 0, 0);
    m_saveAsBtn->setToolTip(("另存为")); 
    pBtmWidgetLayout->addWidget(m_saveAsBtn);

    m_previousBtn = new QPushButton(this);
    m_previousBtn->setObjectName("previousOne");
    m_previousBtn->setToolTip(("上一张")); 
    m_previousBtn->setMouseTracking(true);
    m_previousBtn->setFixedSize(80, 80);
    m_previousBtn->setVisible(false);
    
    m_nextBtn = new QPushButton(this);
    m_nextBtn->setObjectName("nextOne");
    m_nextBtn->setToolTip(("下一张")); 
    m_nextBtn->setFixedSize(80, 80);
    m_nextBtn->setMouseTracking(true);
    m_nextBtn->setVisible(false);

    connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(onCloseBtnClicked()));
    connect(m_zoomInBtn, SIGNAL(clicked()), this, SLOT(onZoonInBtnClicked()));
    connect(m_zoomOutBtn, SIGNAL(clicked()), this, SLOT(onZoonOutBtnClicked()));
    connect(m_rotateBtn, SIGNAL(clicked()), this, SLOT(onRotateBtnClicked()));
    connect(m_saveAsBtn, SIGNAL(clicked()), this, SLOT(onSaveAsBtnClicked()));
    connect(m_previousBtn, SIGNAL(clicked()), this, SLOT(onPreviousBtnClicked()));
    connect(m_nextBtn, SIGNAL(clicked()), this, SLOT(onNextBtnClicked()));
    connect(m_maxBtn, SIGNAL(clicked()), this, SLOT(onMaxBtnClicked()));
    connect(m_minBtn, SIGNAL(clicked()), this, SLOT(showMinimized()));
    setMinimumSize(QSize(360, 386));
    setResizable(true);
    setAttribute(Qt::WA_DeleteOnClose, true);

    this->setWindowIcon(TOON_ICON);
    this->installEventFilter(this);
}

TNPictureViewerDialog::~TNPictureViewerDialog()
{
    m_Thread.quit();
    s_Instance = nullptr;
    delete m_httpCloudApi;
}

void TNPictureViewerDialog::updatePictureList(QList<PictureItem> newPicItemList, int nCurrentIndex)
{
    if (newPicItemList.isEmpty())
    {
        return;
    }
    m_isFirstPicture = true;//单击消息切换图片时，应该自动适应窗体大小
    if (nCurrentIndex != -1)
    {
        m_nCurrentPicIndex = nCurrentIndex;
    }
    else if (m_nCurrentPicIndex != -1)
    {
        for (int i = 0; i < newPicItemList.size(); i++)
        {
            if (newPicItemList[i].strMsgID == m_pictureList[m_nCurrentPicIndex].strMsgID)
            {
                m_nCurrentPicIndex = i;
            }
            else
            {
                Q_ASSERT(false);
                m_nCurrentPicIndex = newPicItemList.size() - 1;
            }
        }
    }
    m_pictureList = newPicItemList;
    m_bCanSwitchNextPic = true;
    m_pBtmBtnWidget->setVisible(true);
    showCurrentPicture();
}

bool TNPictureViewerDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_picViewer)
    {
        if (event->type() == QEvent::Paint && m_isNeedPaint)
        {
            QPainter painter(m_picViewer);
            painter.translate(m_picViewer->width() / 2, m_picViewer->height() / 2);
            painter.rotate(m_rotateAngle);
            painter.translate(-m_picViewer->width() / 2, -m_picViewer->height() / 2);
            if (m_picViewer->rect().contains(m_picRect))
            {
                m_isPictureBeyondClient = false;
            }
            else
            {
                m_isPictureBeyondClient = true;
            }
            autoAjustDrawingRect();
            painter.drawPixmap(m_picRect, m_picture);
        }
        if (event->type() == QEvent::Resize || event->type() == QEvent::Move)
        {
            int y = height() / 2 - m_previousBtn->height() / 2;
            m_previousBtn->move(15, y);
            m_nextBtn->move(width() - 15 - m_previousBtn->width(), y);
            m_picViewer->repaint();
        }
        if (event->type() == QEvent::MouseMove)
        {
            if (!m_isPictureBeyondClient || !m_pResizerDecorator->isMousePress())//图片移动过程中，不需要显示“上一张”和“下一张”按钮
            {
                QMouseEvent *pMouseEvent = dynamic_cast<QMouseEvent *>(event);
				if (pMouseEvent != nullptr){
					QRect previosRect = QRect(0, 0, 120, height());
					QRect nextRect = QRect(width() - 120, 0, 120, height());
					if (m_bCanSwitchNextPic && previosRect.contains(pMouseEvent->pos()))
					{
						m_previousBtn->setVisible(true);
					}
					else
					{
						m_previousBtn->setVisible(false);
					}

					if (m_bCanSwitchNextPic && nextRect.contains(pMouseEvent->pos()))
					{
						m_nextBtn->setVisible(true);
					}
					else
					{
						m_nextBtn->setVisible(false);
					}
					m_picViewer->update();
				}
            }
        }
    }
    return DropShadowWidget::eventFilter(watched, event);
}

void TNPictureViewerDialog::initDialogSize()
{
    //窗体默认尺寸随着图片大小改变
    QSize defaultDialogSize = QSize(
        m_dImageWidth + 1,
        m_dImageHeight + 75
        );

    //但是最大尺寸不能比最大化还大
    QRect clientRect = QApplication::desktop()->availableGeometry();
    if (defaultDialogSize.width() >= clientRect.width() || defaultDialogSize.height() >= clientRect.height())
    {
		/*
		如果图片分辨率大于当前屏幕时，根据当前分辨率进行自适应
		*/
        //showMaximized();
        //m_maxBtn->setChecked(true);
		defaultDialogSize = QSize(clientRect.width(), clientRect.height());
    }
    //else
    //{
    //    showNormal();
    //    resize(defaultDialogSize);
    //    //移动到桌面中间
    //    QPoint center = clientRect.center();
    //    double x = center.x() - width() / 2;
    //    double y = center.y() - height() / 2;
    //    move(x, y);
    //}
	showNormal();
	resize(defaultDialogSize);
	//移动到桌面中间
	QPoint center = clientRect.center();
	double x = center.x() - width() / 2;
	double y = center.y() - height() / 2;
	move(x, y);
}

void TNPictureViewerDialog::initDrawingTargetRect()
{
    if (m_isFirstPicture)
    {
        initDialogSize();
        m_isFirstPicture = false;
    }
    double viewerWidgetHight = height() - 74;
    double viewerWidgetWidth = width();
    double heightScale = (double)m_dImageHeight / viewerWidgetHight;
    double widthScale = (double)m_dImageWidth / viewerWidgetWidth;
    double scale = std::max<double>(heightScale, widthScale);
    scale = std::max<double>(scale, 1);

    double drawHeight = m_dImageHeight / scale;
    double drawWidth = m_dImageWidth / scale;

    QPoint center = QPoint(viewerWidgetWidth / 2, viewerWidgetHight / 2);
    int left = center.x() - drawWidth / 2;
    int right = center.x() + drawWidth / 2;
    int top = center.y() - drawHeight / 2;
    int bottom = center.y() + drawHeight / 2;
    m_picRect = QRect(QPoint(left, top), QPoint(right, bottom));
}

void TNPictureViewerDialog::scaleDrawingTargetRect(double dScaling)
{
    QPoint center = QPoint(m_picViewer->width() / 2, m_picViewer->height() / 2);
    int left = center.x() + (m_picRect.left() - center.x()) * dScaling;
    int right = center.x() + (m_picRect.right() - center.x()) * dScaling;
    int top = center.y() + (m_picRect.top() - center.y()) * dScaling;
    int bottom = center.y() + (m_picRect.bottom() - center.y()) * dScaling;
	if ((right - left < 20 && bottom - top < 20) || (right - left > 5* m_dImageWidth && bottom - top > 5*m_dImageHeight))
    {
		if (dScaling < 1.0)
		{
			m_zoomOutBtn->setEnabled(false);
			m_zoomOutBtn->setToolTip(("已经到最小"));
			QToolTip::showText(QCursor::pos(), ("已经到最小"));
		}
		else
		{
			m_zoomInBtn->setEnabled(false);
			m_zoomInBtn->setToolTip(("已经到最大"));
			QToolTip::showText(QCursor::pos(), ("已经到最大"));
		}
        return;
    }
    m_picRect = QRect(QPoint(left, top), QPoint(right, bottom));
}

void TNPictureViewerDialog::moveDrawingTargetRect(QPoint moveVector)
{
    //旋转后的图片，移动向量也要根据角度旋转下
    double a = -m_rotateAngle * M_PI / 180;
    double x = moveVector.x();
    double y = moveVector.y();
    moveVector = QPoint(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    if (m_picRect.left() >= 0 && m_picRect.right() <= m_picViewer->width())
    {
        moveVector.setX(0);
    }
    if (m_picRect.top() >= 0 && m_picRect.bottom() <= m_picViewer->height())
    {
        moveVector.setY(0);
    }
    m_picRect.moveTo(m_picTopLeftAtPress + moveVector);
}

void TNPictureViewerDialog::autoAjustDrawingRect()
{
    //自动调整，保证界面不会因拖动产生空白区、以及当图片两边都是空白时应中间对齐
    int nAjustX = 0;
    int nAjustY = 0;

    //限制图片边界拖动范围
    if (m_picRect.left() > 0 && m_picRect.right() > m_picViewer->width())
    {
        nAjustX = -m_picRect.left();
    }

    if (m_picRect.left() >= 0 && m_picRect.right() <= m_picViewer->width())
    {
        nAjustX = m_picViewer->width() / 2 - (m_picRect.right() + m_picRect.left()) / 2;
    }

    if (m_picRect.left() < 0 && m_picRect.right() < m_picViewer->width())
    {
        nAjustX = m_picViewer->width() - m_picRect.right();
    }

    if (m_picRect.top() > 0 && m_picRect.bottom() > m_picViewer->height())
    {
        nAjustY = -m_picRect.top();
    }

    if (m_picRect.top() >= 0 && m_picRect.bottom() <= m_picViewer->height())
    {
        nAjustY = m_picViewer->height() / 2 - (m_picRect.bottom() + m_picRect.top()) / 2;
    }
    if (m_picRect.top() < 0 && m_picRect.bottom() < m_picViewer->height())
    {
        nAjustY = m_picViewer->height() - m_picRect.bottom();
    }
    m_picRect.moveTo(m_picRect.topLeft() + QPoint(nAjustX, nAjustY));

}

void TNPictureViewerDialog::showCurrentPicture()
{
    m_rotateAngle = 0;
    QMovie *pGifMovie = m_picViewer->movie();
    if (nullptr != pGifMovie && m_pLoadingMovie != pGifMovie)
    {
        pGifMovie->stop();
        delete pGifMovie;
    }
    m_picViewer->clear();
    QString currentPicPath = getOrignalImage(m_pictureList[m_nCurrentPicIndex]);
    if (currentPicPath.isEmpty())
    {
        return;
    }
	qInfo() << "[TNMVD][TNPictureViewerDialog]showCurrentPicture,path: " << currentPicPath;
	if (currentPicPath.right(4) != "_org") //当前显示的是缩略图
	{
		if (m_pLoadingMovie == nullptr)
		{
			m_pLoadingMovie = new QMovie(":/Resources/loading.gif");
			m_pLoadingMovie->setScaledSize(QSize(80, 80));
		}
		m_picViewer->setMovie(m_pLoadingMovie);
		m_pLoadingMovie->start();
	}
    m_fileSuffix = TNImageCtr::getImageTypeRetString(currentPicPath);
    if (m_fileSuffix.contains("gif"))
    {
        m_isNeedPaint = false;
        QMovie *movie = new QMovie(currentPicPath);
        m_picViewer->setMovie(movie);
        movie->start();
        movie->setPaused(true);
        m_dImageHeight = movie->currentImage().height();
        m_dImageWidth = movie->currentImage().width();
    }
    else
    {
        m_isNeedPaint = true;
		//此处的图片一定是存在的
        if (QFile::exists(currentPicPath))
        {
            if (nullptr != m_pLoadingMovie)
            {
                m_picViewer->clear();
            }
        }
        QFileInfo fileInfo(currentPicPath);
        qint64 file_size = fileInfo.size();
        if(file_size > MAX_PIC_SIZE){
            QImage image;
            QSize adjust_size(800,600);
            if(!TNImageCtr::speedLoadImage(currentPicPath,true,image,adjust_size,
                                       m_fileSuffix,50)){
                return;
            }
            if(!m_picture.convertFromImage(image))
                return;
        }else{
            if(!m_picture.load(currentPicPath,m_fileSuffix.toStdString().c_str())){
                return;
            }
        }
        m_dImageHeight = m_picture.height();
        m_dImageWidth = m_picture.width();
    }
    initDrawingTargetRect();
    if (m_fileSuffix.contains("gif"))
    {
        resizeMovie();
        m_picViewer->movie()->setPaused(false);
    }
    update();
}

void TNPictureViewerDialog::showSpecifiedPicture(QString strPicName)
{
	Q_ASSERT(!strPicName.isEmpty());

	resize(QSize(360, 386));
	m_isFirstPicture = false;
	m_isNeedPaint = true;
	if (m_picture.load(strPicName)){
		m_nCurrentPicIndex = -1;
		m_currentSpecialPic = strPicName;
		m_dImageHeight = m_picture.height();
		m_dImageWidth = m_picture.width();
		initDrawingTargetRect();
		m_bCanSwitchNextPic = false;
		m_pBtmBtnWidget->setVisible(true);
		update();
	}
}

void TNPictureViewerDialog::onZoonInBtnClicked()
{
	if (m_zoomOutBtn->isEnabled() == false)
	{
		m_zoomOutBtn->setEnabled(true);
		m_zoomOutBtn->setToolTip(("缩小"));
	}
    scaleDrawingTargetRect(1.2);
    update();
}

void TNPictureViewerDialog::onZoonOutBtnClicked()
{
	if (m_zoomInBtn->isEnabled() == false)
	{
		m_zoomInBtn->setEnabled(true);
		m_zoomInBtn->setToolTip(("放大"));
	}
    scaleDrawingTargetRect(1 / 1.2);
    update();
}
void TNPictureViewerDialog::initDrawingTargetRectForRotate(qreal Angle)
{
	double viewerWidgetHight = height() - 74;
	double viewerWidgetWidth = width();
	double heightScale;
	double widthScale;
	if (((int)Angle / 90) % 2 == 1)
	{
		heightScale = (double)m_dImageHeight / viewerWidgetWidth;
		widthScale = (double)m_dImageWidth / viewerWidgetHight;
	}
	else
	{
		heightScale = (double)m_dImageHeight / viewerWidgetHight;
		widthScale = (double)m_dImageWidth / viewerWidgetWidth;
	}
	double scale = std::max<double>(heightScale, widthScale);
	scale = std::max<double>(scale, 1);

	double drawHeight = m_dImageHeight / scale;
	double drawWidth = m_dImageWidth / scale;

	QPoint center = QPoint(viewerWidgetWidth / 2, viewerWidgetHight / 2);
	int left = center.x() - drawWidth / 2;
	int right = center.x() + drawWidth / 2;
	int top = center.y() - drawHeight / 2;
	int bottom = center.y() + drawHeight / 2;
	m_picRect = QRect(QPoint(left, top), QPoint(right, bottom));
}
void TNPictureViewerDialog::onRotateBtnClicked()
{
    m_rotateAngle += 90;
	initDrawingTargetRectForRotate(m_rotateAngle);
    update();
}

void TNPictureViewerDialog::onSaveAsBtnClicked()
{
	bool isSpecial = false;
    QString defaltPath = TNPathUtil::getUserRecFile();
    QString defaltName = ("toon图片") + QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
	if (m_nCurrentPicIndex == -1 && !m_currentSpecialPic.isEmpty())
	{
		isSpecial = true;
		m_fileSuffix = TNImageCtr::getImageTypeRetString(m_currentSpecialPic);
	}
	if (m_fileSuffix.isEmpty())
		m_fileSuffix = defalutSuffix;
    QString fileName = QFileDialog::getSaveFileName(
        this,
        ("文件另存为"),
        defaltPath + defaltName, 
        QString("Config Files (*%1)").arg(m_fileSuffix)
        );
    
	if (fileName.isEmpty())
		return;
	if (isSpecial)	{
		QFile::copy(m_currentSpecialPic, fileName);
		return;
	}
    QString strMsgID = m_strCurrentMsgID;
    m_strCurrentMsgID = "";
    QFile::copy(getOrignalImage(m_pictureList[m_nCurrentPicIndex]), fileName);
    m_strCurrentMsgID = strMsgID;
}

inline QString TNPictureViewerDialog::getOrignalImage(PictureItem)
{
    return getOrignalImage(
        m_pictureList[m_nCurrentPicIndex].strMsgID, 
        m_pictureList[m_nCurrentPicIndex].strPicUrl,
        m_pictureList[m_nCurrentPicIndex].bIsSendFromLocal
        );
}

void TNPictureViewerDialog::wheelEvent(QWheelEvent * event)
{
    int nNumberSteps = event->angleDelta().y() / 120;
    double dScaling = 1.0;
    if (nNumberSteps > 0)
    {
        dScaling = qPow(1.1, nNumberSteps);
    }
    else
    {
        dScaling = qPow(1.0 / 1.1, -nNumberSteps);
    }
    if (dScaling < 0.05)
    {
        dScaling = 0.05;
    }
    scaleDrawingTargetRect(dScaling);
    update();
}

void TNPictureViewerDialog::onMaxBtnClicked()
{
#ifndef Q_OS_MAC
	if (isMaximized())
#else
	if (isFullScreen())
#endif
    {
        showNormal();
    }
    else
    {
        showMaximized();
    }
}

void TNPictureViewerDialog::onCloseBtnClicked()
{
    QMovie *pGifMovie = m_picViewer->movie();
    if (nullptr != pGifMovie && pGifMovie != m_pLoadingMovie)
    {
        pGifMovie->stop();
        delete pGifMovie;
    }
    if (nullptr != m_pLoadingMovie)
    {
        delete m_pLoadingMovie;
        m_pLoadingMovie = nullptr;
    }
	this->close();
    //if (m_bIsDownPicSuccess)
    //{
    //    close();
    //}
    //else
    //{
    //    m_isFirstPicture = true;
    //    m_picViewer->clear();
    //    DropShadowWidget::init();
    //    hide();
    //}
}
void TNPictureViewerDialog::mousePressEvent(QMouseEvent *event)
{
    m_isPressAtPicture = m_picViewer->rect().contains(m_picViewer->mapFromGlobal(event->globalPos()));
    if (m_isPictureBeyondClient)
    {
        m_picTopLeftAtPress = m_picRect.topLeft();
    }
    DropShadowWidget::mousePressEvent(event);
}

void TNPictureViewerDialog::mouseMoveEvent(QMouseEvent *event)
{
    //是否需要改变图标样式：图片超出客户区，并且在图片上滑动
    bool bNeedChangeCursor = false;
    if (m_picViewer->rect().contains(m_picViewer->mapFromGlobal(event->globalPos())))
    {
        if (!m_nextBtn->rect().contains(m_nextBtn->mapFromGlobal(event->globalPos()))
            && !m_previousBtn->rect().contains(m_previousBtn->mapFromGlobal(event->globalPos())))
        {
            if (m_isPictureBeyondClient && m_isNeedPaint)
            {
                bNeedChangeCursor = true;
            }
        }
    }

    //如果按在了图片上，并且在图片上拖动,则应该移动图片
    if (m_isPressAtPicture && m_pResizerDecorator->isMousePress() && bNeedChangeCursor)
    {
        moveDrawingTargetRect(event->globalPos() - m_pResizerDecorator->posAtPressMouse());
        update();
        return;
    }

    //按在了图片上, 并且图片大小超出客户区时，不再需要移动窗体
    if (!m_pResizerDecorator->isMousePress() || !m_isPressAtPicture || !m_isPictureBeyondClient)
    {
        DropShadowWidget::mouseMoveEvent(event);
    }
    if (bNeedChangeCursor)
    {
        m_pResizerDecorator->setMovable(false);
        setCursor(Qt::SizeAllCursor);
    }
    else
    {
        if (m_pResizerDecorator->getCurrentResizeRegion() == TNResizerDecorator::Default)
        {
            setCursor(Qt::ArrowCursor);
        }
        if (!m_pResizerDecorator->isMousePress())
        {
            m_pResizerDecorator->setMovable(true);
        }
    }
}

void TNPictureViewerDialog::resizeEvent(QResizeEvent *event)
{
    if (m_fileSuffix.contains("gif"))
    {
        resizeMovie();
    }
    else
    {
        m_picViewer->repaint();
    }
#ifndef Q_OS_MAC
    if (isMaximized())
#else
	if (isFullScreen())
#endif
    {
        m_maxBtn->setToolTip(("还原")); 
        m_maxBtn->setChecked(true);
#ifdef Q_OS_MAC
        m_minBtn->setEnabled(false);
#endif
    }
    else
    {
#ifdef Q_OS_MAC
        m_minBtn->setEnabled(true);
#endif
        m_maxBtn->setToolTip(("最大化")); 
        m_maxBtn->setChecked(false);
    }
}

void TNPictureViewerDialog::resizeMovie()
{
    double dScaleHeight = m_dImageHeight / (height() - 74);
    double dScaleWidth = m_dImageWidth / width();
    double dScale = std::max<double>(dScaleHeight, dScaleWidth);
    dScale = std::max<double>(dScale, 1);
    QSize scaleSize(m_dImageWidth / dScale, m_dImageHeight / dScale);
    m_picViewer->movie()->setScaledSize(scaleSize);
}
void TNPictureViewerDialog::onPreviousBtnClicked()
{
    if (m_nCurrentPicIndex == 0)
    {
        m_previousBtn->setToolTip(("已是第一张"));
        QToolTip::showText(QCursor::pos(), ("已是第一张"));
        return;
    }
	if (m_nextBtn->toolTip() == ("已是最后一张"))
	{
		m_nextBtn->setToolTip(("下一张"));
	}
    m_nCurrentPicIndex--;
    showCurrentPicture();
    if (m_nCurrentPicIndex == 0)
    {
        m_previousBtn->setToolTip(("已是第一张"));
        QToolTip::showText(QCursor::pos(), ("已是第一张"));
        return;
    }
    else
    {
        m_previousBtn->setToolTip(("上一张"));
    }
}

void TNPictureViewerDialog::onNextBtnClicked()
{
    if (m_nCurrentPicIndex == m_pictureList.size() - 1)
    {
        m_nextBtn->setToolTip(("已是最后一张"));
        QToolTip::showText(QCursor::pos(), ("已是最后一张"));
        return;
    }
	if (m_previousBtn->toolTip() == ("已是第一张"))
	{
		m_previousBtn->setToolTip(("上一张"));
	}
    m_nCurrentPicIndex++;
    showCurrentPicture();
    if (m_nCurrentPicIndex == m_pictureList.size() - 1)
    {
        m_nextBtn->setToolTip(("已是最后一张"));
        QToolTip::showText(QCursor::pos(), ("已是最后一张"));
        return;
    }
    else
    {
        m_nextBtn->setToolTip(("下一张"));
    }
}

QString TNPictureViewerDialog::getOrignalImage(QString strMsgID, QString strURL, bool bIsSendFromLocal)
{
    m_strCurrentMsgID = strMsgID;
    QString strOrinalFile;
    if (!bIsSendFromLocal)
    {
        strOrinalFile = TNPathUtil::getUserRecFile() + strMsgID + "_org";
    }
    else
    {
		strOrinalFile = strURL+ "_org";
    }
    QFile file(strOrinalFile);
    if (!file.exists())
    {
		qInfo() << "[TNMVD][TNPictureViewerDialog]getOrignalImage ,the original pic is not exist,return thumbnail";
		strOrinalFile = strURL; //先显示缩略图
    }
    return strOrinalFile;
}

void TNPictureViewerDialog::showMaximized()
{
#ifndef Q_OS_MAC
	DropShadowWidget::showMaximized();
#else
	DropShadowWidget::showFullScreen();
#endif

    m_maxBtn->setToolTip(("还原")); 
    m_maxBtn->setChecked(true);
}

void TNPictureViewerDialog::showNormal()
{
    DropShadowWidget::showNormal();
    m_maxBtn->setToolTip(("最大化")); 
    m_maxBtn->setChecked(false);
}

void TNPictureViewerDialog::adjustImageSize(int &width, int &height)
{
    if (width > 800){
        int new_width = 800;
        float rate = new_width * 1.0f / width;
        height = rate * height;
        width = new_width;
    }
    if (height > 600){
        int new_height = 600;
        float rate = new_height * 1.0f / height;
        width = rate * width;
        height = new_height;
    }
}
void TNPictureViewerDialog::originalDownFinished(bool status, QString msgId, QString file_path)
{
	qInfo() << "[TNMVD][TNPictureViewerDialog]originalDownFinished,recieve msgId:" << msgId << " status:" << status<<" ";
	if (status && msgId == m_strCurrentMsgID)
	{
		if (nullptr != m_pLoadingMovie)
		{
			m_pLoadingMovie->stop();
		}
		m_isFirstPicture = true;
		showCurrentPicture();
	}
}