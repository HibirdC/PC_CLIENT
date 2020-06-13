#ifndef TNIMAGESENDCONFIRMDIALOG_H
#define TNIMAGESENDCONFIRMDIALOG_H

#include "DropShadowWidget.h"
#include "TNElidedLabel.h"

class QLabel;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class TNSendConfirmDialog : public DropShadowWidget
{
    Q_OBJECT

public:
    TNSendConfirmDialog(QWidget *parent = 0);
    ~TNSendConfirmDialog();

    void setLabelTitle(const QString &title);
    void setPixmap(const QString &filePath,const QString &suffix = "");
    void setImagePath(const QString &fileName,const QString &suffix = "");
    void setFilePath(const QString &fileName);

private:
    QLabel *pTittle;
    QLabel *m_pImageLabel;
    QLabel *m_pImageSizeLabel;
    QVBoxLayout *m_pImageLayout;

    QLabel *m_pFileIconLabel;
    TNElidedLabel *m_pFileNameLabel;
    QLabel *m_pFileSizeLabel;
    QGridLayout *m_pFileLayout;

    QPushButton *m_pSendButton;
    QPushButton *m_pCloseBtn;
	QWidget * m_pFileWidget;

    QString getFileSizeTitle(const QString &fileNamePath);
};

#endif // TNIMAGESENDCONFIRMDIALOG_H
