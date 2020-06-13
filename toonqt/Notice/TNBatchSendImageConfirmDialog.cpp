#include "TNBatchSendImageConfirmDialog.h"
#include "ui_TNBatchSendImageConfirmDialog.h"

#include "tnimagectr.h"
#include "TNPathUtil.h"
#include "TNDataCache.h"
#include "tncommondealavator.h"
#include "TNHttpCloudApi.h"
#include "TNUserDataHelper.h"
#include "TNNetAvatarDown.h"
#include "TNImageLoadThread.h"

#include <QTextCursor>
#include <QFileInfo>
#include <QTimer>

TNBatchSendImageConfirmDialog::TNBatchSendImageConfirmDialog(const QStringList &fileNames, QWidget *parent) :
    /*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNBatchSendImageConfirmDialog)
{
    ui->setupUi(this);

    ui->warningTipLabel->setVisible(false);
    initialTableWidget(fileNames);    

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

TNBatchSendImageConfirmDialog::~TNBatchSendImageConfirmDialog()
{
    delete ui;
}

void TNBatchSendImageConfirmDialog::setLabelTitle(const QString &title)
{
    ui->chooseCardTitleLabel->setText(title);
}

QStringList TNBatchSendImageConfirmDialog::getFileNames() const
{
    return m_validImageFileNames;
}

void TNBatchSendImageConfirmDialog::accept()
{
    QDialog::accept();
}

void TNBatchSendImageConfirmDialog::initialTableWidget(const QStringList &fileNames)
{
    ui->cardTableWidget->setShowGrid(false);
    ui->cardTableWidget->setFixedSize(300, 300);
    ui->cardTableWidget->horizontalHeader()->setVisible(false);
    ui->cardTableWidget->verticalHeader()->setVisible(false);
    ui->cardTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cardTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->cardTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cardTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->cardTableWidget->setFocusPolicy(Qt::NoFocus);
    ui->cardTableWidget->setContentsMargins(0,20,0,0);

    bool isOverSize  = false;
    bool isOverCount = false;
    m_validImageFileNames.clear();
    foreach (const QString &fileName, fileNames)
    {
        QFileInfo fileInfo(fileName);
        if (fileInfo.size() > MAX_PIC_SIZE)
        {
            isOverSize = true;
            continue;
        }

        m_validImageFileNames.append(fileName);
        if (m_validImageFileNames.size()>9)
        {
            m_validImageFileNames.removeLast();
            isOverCount = true;
            break;
        }
    }

    QString warningText;
    if (isOverCount)
        warningText = tr(QString(QStringLiteral("一次发送的图片数不能超过9个")).toUtf8().data());
    if (isOverSize)
        warningText = tr(QString(QStringLiteral("超过10M的图片将自动转为附件发送")).toUtf8().data());

    if (!warningText.isEmpty())
    {
        this->setFixedSize(360, 454);
        ui->warningTipLabel->setText(warningText);
        ui->warningTipLabel->setVisible(true);
    }

    updateTableWidget();
}

ImageToolButton *TNBatchSendImageConfirmDialog::makeImageToolButton(const QString &fileName)
{
    QSize IconSize(80, 80);
    ImageToolButton *imageButton = new ImageToolButton(fileName);
    imageButton->setObjectName("imageButton");
    imageButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    imageButton->setIconSize(IconSize);
    imageButton->setFixedSize(80,80);

    if (!m_fileNameToImage.contains(fileName))
    {
        /* QTime time;
        time.start();
        QImage image;
        QString suffix = TNImageCtr::getImageTypeRetString(fileName);
        if(TNImageCtr::speedLoadImage(fileName, true, image, IconSize, suffix, 50))
        {
            m_fileNameToImage[fileName] = image;
        }
        qInfo()<<"[Notice][TNBatchSendImageConfirmDialog]speedLoadImage-time="<<time.elapsed(); */

        m_fileNameToButton[fileName] = imageButton;
        QThread *thread = new TNImageLoadThread(fileName, IconSize, this);
        connect(thread, SIGNAL(loadFinished(const QString&, const QImage&)), this, SLOT(addThumbnail(const QString&, const QImage&)));
        connect(thread, SIGNAL(loadFailed(const QString&)), this, SLOT(showError(const QString&)));
        thread->start();
    }
    imageButton->setIcon(QIcon(QPixmap::fromImage(m_fileNameToImage[fileName])));

    return imageButton;
}
void TNBatchSendImageConfirmDialog::updateTableWidget()
{
    QTime time;
    time.start();

    if (m_validImageFileNames.isEmpty())
    {
        this->accept();
    }

    ui->cardTableWidget->clearContents();
    int colNum = 3;
    int rowNum = 3;
    ui->cardTableWidget->setRowCount(rowNum);
    ui->cardTableWidget->setColumnCount(colNum);
    for (int iRow = 0; iRow < rowNum; iRow++)
    {
        for (int iCol = 0; iCol < colNum; iCol++)
        {
            int index = iRow*colNum + iCol;
            if (index < 0 || index >= m_validImageFileNames.size())
            {
                break;
            }

            const QString fileName = m_validImageFileNames.at(index);
            ImageToolButton *imageButton = makeImageToolButton(fileName);
            imageButton->installEventFilter(this);
            connect(imageButton->m_removeButton, SIGNAL(clicked()), this, SLOT(slotRemoveImage()));
            ui->cardTableWidget->setCellWidget(iRow, iCol, imageButton);
            ui->cardTableWidget->setColumnWidth(iCol, 100);
        }
        ui->cardTableWidget->setRowHeight(iRow, 100);
    }

    Q_ASSERT(m_validImageFileNames.size() == m_fileNameToImage.size());
    qInfo()<<"[Notice][TNBatchSendImageConfirmDialog]updateTableWidget-m_validImageFileNames.size="<<m_validImageFileNames.size();
    qInfo()<<"[Notice][TNBatchSendImageConfirmDialog]updateTableWidget-m_fileNameToImage.size="<<m_fileNameToImage.size();
    qInfo()<<"[Notice][TNBatchSendImageConfirmDialog]updateTableWidget-time="<<time.elapsed();
}

bool TNBatchSendImageConfirmDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (ImageToolButton *imageButton = qobject_cast<ImageToolButton*>(watched))
    {
        if (event->type() == QEvent::Enter)
        {
            imageButton->setXPushButtonVisible(true);
        }
        if (event->type() == QEvent::Leave)
        {
            imageButton->setXPushButtonVisible(false);
        }
    }

    return QDialog::eventFilter(watched, event);
}

void TNBatchSendImageConfirmDialog::slotRemoveImage()
{
    XPushButton *xButton = qobject_cast<XPushButton *>(sender());
    if (xButton == nullptr)
        return;

    foreach (const QString &fileName, m_validImageFileNames)
    {
        if (fileName == xButton->m_fileName)
        {
            m_validImageFileNames.removeOne(fileName);
            m_fileNameToImage.remove(fileName);
            break;
        }
    }

    Q_ASSERT(m_validImageFileNames.size() == m_fileNameToImage.size());
    qInfo()<<"[Notice][TNBatchSendImageConfirmDialog]m_validImageFileNames.size="<<m_validImageFileNames.size();
    qInfo()<<"[Notice][TNBatchSendImageConfirmDialog]m_fileNameToImage.size="<<m_fileNameToImage.size();
    updateTableWidget();
}

void TNBatchSendImageConfirmDialog::addThumbnail(const QString &fileName, const QImage &buttonImage)
{
    if (m_fileNameToImage.contains(fileName) && m_fileNameToButton.contains(fileName))
    {
        m_fileNameToImage[fileName] = buttonImage;
        m_fileNameToButton[fileName]->setIcon(QIcon(QPixmap::fromImage(m_fileNameToImage[fileName])));
    }
}

void TNBatchSendImageConfirmDialog::showError(const QString &fileName)
{
    // 加载显示一张破图？
}
