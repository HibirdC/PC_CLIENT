#ifndef TNBATCHSENDFILECONFIRMDIALOG_H
#define TNBATCHSENDFILECONFIRMDIALOG_H

#include "TNDbUtil.h"
#include "TNPathUtil.h"
#include "notice_global.h"
#include "DropShadowWidget.h"

#include <QLabel>
#include <QFileInfo>
#include <QDialog>
#include <QPushButton>
#include <QToolButton>
#include <QGridLayout>
#include <QStyleOption>

namespace Ui {
class TNBatchSendFileConfirmDialog;
}

class fXPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit fXPushButton(const QString &fileName, QWidget *parent = 0) : QPushButton(parent), m_fileName(fileName)
    {
    }

    QString m_fileName;
};

class FileToolButton : public QWidget
{
    Q_OBJECT

public:
    explicit FileToolButton(const QString &fileName, QWidget *parent = 0) : QWidget(parent)
    {
        //发送附件时
        QGridLayout *m_pFileLayout = new QGridLayout(this);
        QLabel *m_pFileIconLabel = new QLabel(this);
        m_pFileIconLabel->setFixedSize(50, 50);
        m_pFileLayout->addWidget(m_pFileIconLabel, 0, 0, 2, 1);
        //文件名标签
        QLabel *m_pFileNameLabel = new QLabel(this);
        m_pFileNameLabel->setObjectName("m_pFileNameLabel");
        m_pFileNameLabel->setContentsMargins(0,6,0,0);
        m_pFileLayout->addWidget(m_pFileNameLabel, 0, 1, 1, 1, Qt::AlignLeft);
        //文件大小
        QLabel *m_pFileSizeLabel = new QLabel(this);
        m_pFileSizeLabel->setObjectName("m_pFileSizeLabel");
        m_pFileSizeLabel->setContentsMargins(10,0,0,10);
        m_pFileLayout->addWidget(m_pFileSizeLabel, 1, 1, 1, 1, Qt::AlignLeft);
        //文件大小);
        m_pFileLayout->setContentsMargins(20,10,20,10);
        this->setLayout(m_pFileLayout);

        QFileInfo fileInfo(fileName);
        QImage image;
        if (image.load(TNPathUtil::getFileIcon(fileInfo.suffix())))
        {
            m_pFileIconLabel->setPixmap(QPixmap::fromImage(image));
            QString base_fileName = fileInfo.fileName();
            m_pFileNameLabel->setText(QStringLiteral("  ") + base_fileName);
            m_pFileSizeLabel->setText(QStringLiteral("附件大小：") + getFileSizeTitle(fileName));
        }

        m_removeButton = new fXPushButton(fileName, this);
        m_removeButton->setObjectName("fileRemoveButton");
        m_removeButton->raise();
        m_removeButton->setFixedSize(16, 16);
        m_removeButton->move(268, 30);
        m_removeButton->setVisible(false);
        m_removeButton->setCursor(Qt::PointingHandCursor);
    }

    void setXPushButtonVisible(bool visible)
    {
        m_removeButton->setVisible(visible);
    }

protected:
    virtual void paintEvent(QPaintEvent * event)
    {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }

    QString getFileSizeTitle(const QString &fileNamePath)
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

public:
    fXPushButton *m_removeButton;
};

class TNBatchSendFileConfirmDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNBatchSendFileConfirmDialog(const QStringList &fileNames, QWidget *parent = 0);
    ~TNBatchSendFileConfirmDialog();

    QStringList getFileNames() const;

public Q_SLOTS:
    virtual void accept();

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void slotRemoveFile();

private:
    Ui::TNBatchSendFileConfirmDialog *ui;

    void initialTableWidget(const QStringList &fileNames);
    void updateTableWidget();
    QStringList m_validFileNames;
};

#endif // TNBATCHSENDFILECONFIRMDIALOG_H
