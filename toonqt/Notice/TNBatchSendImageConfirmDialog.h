#ifndef TNBATCHSENDIMAGECONFIRMDIALOG_H
#define TNBATCHSENDIMAGECONFIRMDIALOG_H

#include "TNDbUtil.h"
#include "DropShadowWidget.h"

#include <QDialog>
#include <QPushButton>
#include <QToolButton>

namespace Ui {
class TNBatchSendImageConfirmDialog;
}

class XPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit XPushButton(const QString &fileName, QWidget *parent = 0) : QPushButton(parent), m_fileName(fileName)
    {
    }

    QString m_fileName;
};

class ImageToolButton : public QToolButton
{
    Q_OBJECT

public:
    explicit ImageToolButton(const QString &fileName, QWidget *parent = 0) : QToolButton(parent)
    {
        m_removeButton = new XPushButton(fileName, this);
        m_removeButton->setObjectName("removeButton");
        m_removeButton->raise();
        m_removeButton->setFixedSize(80, 80);
        m_removeButton->move(0, 0);
        m_removeButton->setVisible(false);
    }

    void setXPushButtonVisible(bool visible)
    {
        m_removeButton->setVisible(visible);
    }

    XPushButton *m_removeButton;
};

class TNBatchSendImageConfirmDialog : public /*QDialog*/DropShadowWidget
{
    Q_OBJECT

public:
    explicit TNBatchSendImageConfirmDialog(const QStringList &fileNames, QWidget *parent = 0);
    ~TNBatchSendImageConfirmDialog();

    void setLabelTitle(const QString &title);
    QStringList getFileNames() const;

public Q_SLOTS:
    virtual void accept();

private slots:
    void slotRemoveImage();
    void addThumbnail(const QString &fileName, const QImage &buttonImage);
    void showError(const QString &fileName);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::TNBatchSendImageConfirmDialog *ui;

    void initialTableWidget(const QStringList &fileNames);
    void updateTableWidget();
    QStringList m_validImageFileNames;
    QMap<QString, QImage> m_fileNameToImage;
    QMap<QString, ImageToolButton*> m_fileNameToButton;
    ImageToolButton *makeImageToolButton(const QString &fileName);
};

#endif // TNBATCHSENDIMAGECONFIRMDIALOG_H
