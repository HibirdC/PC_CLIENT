/*******************************************************************
*  Copyright(c) 2000-2018 syswin
*  All rights reserved.
*
*  文件名称: TNScreenShotTextEdit.h
*  说明:    截图用文本编辑框
******************************************************************/

#ifndef TNSCREENSHOTTEXTEDIT_H
#define TNSCREENSHOTTEXTEDIT_H

#include <QTextEdit>

class TNScreenShotTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    TNScreenShotTextEdit(int nFontPointSize, const QColor &fontColor, QWidget *parent);
    ~TNScreenShotTextEdit();
    void setFontSize(int pointSize);
    void setFontColor(QColor color);

protected slots:
    void adjustSize();
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void insertFromMimeData(const QMimeData *source);

signals:
    void editFinished();
private:
    QPoint m_relativeCursorPosAtPress; //鼠标按下时，光标距离窗体原点的相对位置
    bool m_bIsMousePress; //鼠标是否按下
    int m_nFontPointSize; //字体磅值
    QColor m_FontColor;
};

#endif // TNSCREENSHOTTEXTEDIT_H
