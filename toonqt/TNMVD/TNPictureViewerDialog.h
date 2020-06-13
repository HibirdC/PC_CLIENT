#ifndef TNPICTUREVIEWERDIALOG_H
#define TNPICTUREVIEWERDIALOG_H

#include "DropShadowWidget.h"
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include <QThread>
class QPushButton;
class QLabel;
class TNHttpCloudApi;
#include "TNMVD_global.h"

class TNMVD_EXPORT TNPictureViewerDialog : public DropShadowWidget
{
    Q_OBJECT

public:
    static TNPictureViewerDialog * getInstance();
    static void freeInstance();
    ~TNPictureViewerDialog();

    struct PictureItem
    {
        QString strMsgID;
        QString strPicUrl;
        bool bIsSendFromLocal;
    };

    void updatePictureList(QList<PictureItem> picPathList, int nCurrentIndex);
    QString getOrignalImage(QString strMsgID, QString strURL, bool bIsSendFromLocal);
    void showSpecifiedPicture(QString strPicName);

public slots:
	void originalDownFinished(bool, QString msgId, QString file_path);

public:
    void showMaximized();
    void showNormal();
signals:
    void downBigPicOver();
protected:
    void showCurrentPicture();
    bool eventFilter(QObject *watched, QEvent *event);
    void initDialogSize();
    void initDrawingTargetRect();
	void initDrawingTargetRectForRotate(qreal Angle);
    void scaleDrawingTargetRect(double dScale);
    void moveDrawingTargetRect(QPoint moveVector);
    void autoAjustDrawingRect();
    void wheelEvent(QWheelEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    QString getOrignalImage(PictureItem item);
    void resizeMovie();

protected slots:
    void onZoonInBtnClicked();
    void onZoonOutBtnClicked();
    void onRotateBtnClicked();
    void onSaveAsBtnClicked();
    void onPreviousBtnClicked();
    void onNextBtnClicked();
    void onMaxBtnClicked();
    void onCloseBtnClicked();

private:
    TNPictureViewerDialog(QWidget *parent);
    void adjustImageSize(int& width,int& height);
    QPixmap m_picture;
private:
    QLabel *m_picViewer;   
    QPushButton *m_maxBtn;
    QPushButton *m_minBtn;
    QPushButton *m_closeBtn;
    QPushButton *m_zoomInBtn;
    QPushButton *m_zoomOutBtn;
    QPushButton *m_rotateBtn;
    QPushButton *m_saveAsBtn;
    QPushButton *m_previousBtn;
    QPushButton *m_nextBtn;   
    qreal m_rotateAngle;     
    QWidget *m_pBtmBtnWidget;

    bool m_isNeedPaint;    
    bool m_isPictureBeyondClient;  
    bool m_isPressAtPicture;  
    bool m_isFirstPicture;
    //bool m_bIsDownPicSuccess; //此值已废弃
    bool m_bCanSwitchNextPic;   //是否可切换下一张
    int m_nCurrentPicIndex;
    double m_dImageHeight;
    double m_dImageWidth;

	QRect m_picRect;          
	QPoint m_picTopLeftAtPress;
    QString m_fileSuffix;
    QString m_strCurrentMsgID;
    QThread m_Thread;
    QMovie *m_pLoadingMovie;
    QList<PictureItem> m_pictureList;
	QString m_currentSpecialPic; //特殊图片路径，如头像
private:
    static TNPictureViewerDialog *s_Instance;
    TNHttpCloudApi *m_httpCloudApi;
};

#endif // TNPICTUREVIEWERDIALOG_H
