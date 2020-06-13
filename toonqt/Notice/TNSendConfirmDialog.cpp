#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QDebug>
#include "TNSendConfirmDialog.h"
#include "TNPathUtil.h"
#include "notice_global.h"
#include "tnimagectr.h"
#include "TNMVD_global.h"
#include "QCoreApplication"

TNSendConfirmDialog::TNSendConfirmDialog(QWidget *parent)
    : DropShadowWidget(parent)
{
    // setWindowTitle(("发送图片"));
    QVBoxLayout *pMainLayout = new QVBoxLayout();
    this->setLayout(pMainLayout);
    pMainLayout->setAlignment(Qt::AlignCenter);
	pMainLayout->setContentsMargins(0, 0, 0, 0);

    //顶部关闭按钮所在水平布局
    QHBoxLayout * pTopHLayout = new QHBoxLayout(this);
    pTittle = new QLabel(this);
	pTittle->setText(tr(QStringLiteral("发送图片").toUtf8().data()));
	pTittle->setObjectName("sendTitle");
	pTopHLayout->addStretch();
    pTopHLayout->addWidget(pTittle);
    pTopHLayout->addStretch();
    pTopHLayout->setAlignment(Qt::AlignVCenter);
    pTopHLayout->setContentsMargins(0, 10, 0, 16);
    pTopHLayout->setSpacing(0);

    pTopHLayout->setObjectName("pictureTop");
    pMainLayout->addLayout(pTopHLayout);

    //发送图片时用
    m_pImageLayout = new QVBoxLayout(this);
    m_pImageLayout->addStretch();
    m_pImageLabel = new QLabel(this);
    m_pImageLabel->setFixedSize(300, 220);
    m_pImageLayout->addWidget(m_pImageLabel);
    //m_pImageLayout->addStretch();
    m_pImageSizeLabel = new QLabel(this);
    m_pImageSizeLabel->setObjectName("m_pImageSizeLabel");
    m_pImageSizeLabel->setAlignment(Qt::AlignCenter);
    m_pImageSizeLabel->setVisible(false);
    //m_pImageLayout->addWidget(m_pImageSizeLabel);
    m_pImageLayout->setContentsMargins(28,0,28,0);
    pMainLayout->addLayout(m_pImageLayout);

	m_pFileWidget = new QWidget(this);
	m_pFileWidget->setFixedSize(300,90);
	m_pFileWidget->setObjectName("m_pFileWidget");

    //发送附件时
    m_pFileLayout = new QGridLayout(this);
    m_pFileIconLabel = new QLabel(this);
    m_pFileIconLabel->setFixedSize(50, 50);
    m_pFileLayout->addWidget(m_pFileIconLabel, 0, 0, 2, 1);
    //文件名标签
    m_pFileNameLabel = new TNElidedLabel(this);
    m_pFileNameLabel->setElideMode(Qt::ElideMiddle);
	m_pFileNameLabel->setObjectName("m_pFileNameLabel");
    m_pFileNameLabel->setContentsMargins(10,0,0,0);
    m_pFileLayout->addWidget(m_pFileNameLabel, 0, 1, 1, 1, Qt::AlignLeft);
    //文件大小
    m_pFileSizeLabel = new QLabel(this);
	m_pFileSizeLabel->setObjectName("m_pFileSizeLabel");
    m_pFileSizeLabel->setContentsMargins(10,0,0,0);
    m_pFileLayout->addWidget(m_pFileSizeLabel, 1, 1, 1, 1, Qt::AlignLeft);
    //文件大小);
	m_pFileLayout->setContentsMargins(20,20,20,20);
	m_pFileWidget->setLayout(m_pFileLayout);

	QHBoxLayout * fileBoxHLayout = new QHBoxLayout(this);
	fileBoxHLayout->addStretch();
	fileBoxHLayout->addWidget(m_pFileWidget);
	fileBoxHLayout->addStretch();
	fileBoxHLayout->setContentsMargins(0, 0, 0, 0);
	pMainLayout->addLayout(fileBoxHLayout);

    QHBoxLayout * pBtmHLayout = new QHBoxLayout(this);
    pMainLayout->addLayout(pBtmHLayout);


    m_pSendButton = new QPushButton(this);
    pBtmHLayout->addStretch();
    pBtmHLayout->addWidget(m_pSendButton);
	pBtmHLayout->setContentsMargins(0, 30, 0, 30);
	m_pSendButton->setText(tr(QStringLiteral("发送").toUtf8().data()));
	m_pSendButton->setObjectName("sendOkButton");
	m_pSendButton->setCursor(QCursor(Qt::PointingHandCursor));
	m_pSendButton->setContentsMargins(0, 0, 0, 0);
    m_pSendButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	pBtmHLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

    m_pCloseBtn = new QPushButton(this);
    m_pCloseBtn->setContentsMargins(0, 0, 0, 0);
    m_pCloseBtn->setMouseTracking(true);
	m_pCloseBtn->setText(tr(QStringLiteral("取消").toUtf8().data()));
	m_pCloseBtn->setObjectName("sendCloseButton");
	m_pCloseBtn->setCursor(QCursor(Qt::PointingHandCursor));
    m_pCloseBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pBtmHLayout->addWidget(m_pCloseBtn);
    pBtmHLayout->addStretch();

    connect(m_pCloseBtn, SIGNAL(clicked()), this, SLOT(reject()));
    connect(m_pSendButton, SIGNAL(clicked()), this, SLOT(accept()));
}

TNSendConfirmDialog::~TNSendConfirmDialog()
{ 

}

void TNSendConfirmDialog::setLabelTitle(const QString &title)
{
    pTittle->setText(title);
}

void TNSendConfirmDialog::setPixmap(const QString& path,const QString& suffix)
{
	setFixedSize(360, 376);
	m_pImageLabel->setVisible(true);
    //m_pImageSizeLabel->setVisible(true);
	m_pFileWidget->setVisible(false);
    const double refWidth = m_pImageLabel->width();
    const double refHeight = m_pImageLabel->height();

    QPixmap tempPixmap;
    QImage image;
    QSize adjust_size(refWidth, refHeight);
    if(!TNImageCtr::speedLoadImage(path,true,image,adjust_size,suffix,50))
        return;
    if(!tempPixmap.convertFromImage(image))
        return;

    if(tempPixmap.width() > (int)refWidth ||
            tempPixmap.height() > (int)refHeight){
        tempPixmap = tempPixmap.scaled(QSize(refWidth,refHeight),Qt::KeepAspectRatio);
    }
    m_pImageLabel->setPixmap(tempPixmap);
    m_pImageLabel->setAlignment(Qt::AlignCenter);
	m_pImageSizeLabel->setText(tr(QStringLiteral("图片大小：").toUtf8().data()) + getFileSizeTitle(path));
}

void TNSendConfirmDialog::setImagePath(const QString &fileName, const QString &suffix)
{
    setPixmap(fileName,suffix);
}

void TNSendConfirmDialog::setFilePath(const QString &fileName)
{
    setFixedSize(360, 226);
    m_pImageLabel->setVisible(false);
    m_pImageSizeLabel->setVisible(false);
    m_pFileWidget->setVisible(true);

    QFileInfo fileInfo(fileName);
    QImage image;
    if (image.load(TNPathUtil::getFileIcon(fileInfo.suffix())))
    {
        m_pFileIconLabel->setPixmap(QPixmap::fromImage(image));
        QString base_fileName = fileInfo.fileName();
        m_pFileNameLabel->setText(("  ") + base_fileName);
		m_pFileSizeLabel->setText(tr(QStringLiteral("附件大小：").toUtf8().data()) + getFileSizeTitle(fileName));
    }
}

QString TNSendConfirmDialog::getFileSizeTitle(const QString &fileNamePath)
{
    QFileInfo info(fileNamePath);
    if (info.isFile()){
        qint64 file_size = info.size();
        QString qs_result_size;
        float result;
        int g = file_size / GB;
        int m, k, b;
        if (g > 0){
            m = file_size % GB;
            result = g + (float)m / GB;
            qs_result_size.sprintf("%.2fGB", result);
        }else if (file_size / MB > 0){
            m = file_size / MB;
            k = file_size % MB;
            result = m + (float)k / MB;
            qs_result_size.sprintf("%.2fMB", result);
        }else if (file_size / KB > 0){
            k = file_size / KB;
            b = file_size % KB;
            result = k + (float)b / KB;
            qs_result_size.sprintf("%.2fKB", result);
        }else{
            qs_result_size = QString("%1bytes").arg(file_size);
        }
        return qs_result_size;
    }
    return QString::null;
}
