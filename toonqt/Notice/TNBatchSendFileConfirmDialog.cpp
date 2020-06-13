#include "TNBatchSendFileConfirmDialog.h"
#include "ui_TNBatchSendFileConfirmDialog.h"

#include "tnimagectr.h"
#include "TNPathUtil.h"
#include "TNDataCache.h"
#include "tncommondealavator.h"
#include "TNHttpCloudApi.h"
#include "TNUserDataHelper.h"
#include "TNNetAvatarDown.h"

#include <QTextCursor>
#include <QFileInfo>
#include <QTimer>

TNBatchSendFileConfirmDialog::TNBatchSendFileConfirmDialog(const QStringList &fileNames, QWidget *parent) :
    /*QDialog*/DropShadowWidget(parent),
    ui(new Ui::TNBatchSendFileConfirmDialog)
{
    ui->setupUi(this);

    ui->warningTipLabel->setVisible(false);
    initialTableWidget(fileNames);

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

TNBatchSendFileConfirmDialog::~TNBatchSendFileConfirmDialog()
{
    delete ui;
}

QStringList TNBatchSendFileConfirmDialog::getFileNames() const
{
    return m_validFileNames;
}

void TNBatchSendFileConfirmDialog::accept()
{
    QDialog::accept();
}

void TNBatchSendFileConfirmDialog::initialTableWidget(const QStringList &fileNames)
{
    ui->cardTableWidget->setShowGrid(false);
    ui->cardTableWidget->setFixedSize(328, 260);
    ui->cardTableWidget->horizontalHeader()->setVisible(false);
    ui->cardTableWidget->verticalHeader()->setVisible(false);
    ui->cardTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cardTableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->cardTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->cardTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->cardTableWidget->setFocusPolicy(Qt::NoFocus);

    bool isOverSize  = false;
    bool isOverCount = false;
    m_validFileNames.clear();
    foreach (const QString &fileName, fileNames)
    {
        QFileInfo fileInfo(fileName);
        if (fileInfo.size() > MAX_FILE_SIZE)
        {
            isOverSize = true;
            continue;
        }

        m_validFileNames.append(fileName);
        if (m_validFileNames.size()>9)
        {
            m_validFileNames.removeLast();
            isOverCount = true;
            break;
        }
    }

    QString warningText;
    if (isOverCount)
        warningText = tr(QString(QStringLiteral("一次发送的附件数不能超过9个")).toUtf8().data());
    if (isOverSize)
        warningText = tr(QString(QStringLiteral("单个附件的大小不能超过60M")).toUtf8().data());

    if (!warningText.isEmpty())
    {
        this->setFixedSize(360, 422);
        ui->warningTipLabel->setText(warningText);
        ui->warningTipLabel->setVisible(true);
    }

    updateTableWidget();
}

void TNBatchSendFileConfirmDialog::updateTableWidget()
{
    QTime time;
    time.start();

    if (m_validFileNames.isEmpty())
    {
        this->accept();
    }

    qInfo()<<"[Notice][TNBatchSendFileConfirmDialog]updateTableWidget-validFileNames.size="<<m_validFileNames.size();
    ui->cardTableWidget->clearContents();
    int rowNum = m_validFileNames.size();
    ui->cardTableWidget->setRowCount(rowNum);
    ui->cardTableWidget->setColumnCount(1);
    for (int iRow = 0; iRow < rowNum; iRow++)
    {
        int index = iRow;
        if (index < 0 || index >= m_validFileNames.size())
        {
            break;
        }

        const QString fileName = m_validFileNames.at(index);
        FileToolButton *imageButton = new FileToolButton(fileName);
        imageButton->installEventFilter(this);
        imageButton->setObjectName("batchFileButton");
        imageButton->setFixedSize(300, 76);
        connect(imageButton->m_removeButton, SIGNAL(clicked()), this, SLOT(slotRemoveFile()));
        ui->cardTableWidget->setCellWidget(iRow, 0, imageButton);
        ui->cardTableWidget->setColumnWidth(0, 328);
        ui->cardTableWidget->setRowHeight(iRow, 86);
    }

    qInfo()<<"[Notice][TNBatchSendFileConfirmDialog]updateTableWidget-time="<<time.elapsed();
}

bool TNBatchSendFileConfirmDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (FileToolButton *imageButton = qobject_cast<FileToolButton*>(watched))
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

void TNBatchSendFileConfirmDialog::slotRemoveFile()
{
    fXPushButton *xButton = qobject_cast<fXPushButton *>(sender());
    if (xButton == nullptr)
        return;

    foreach (const QString &fileName, m_validFileNames)
    {
        if (fileName == xButton->m_fileName)
        {
            m_validFileNames.removeOne(fileName);
            break;
        }
    }

    qInfo()<<"[Notice][TNBatchSendFileConfirmDialog]m_validFileNames.size="<<m_validFileNames.size();
    updateTableWidget();
}
