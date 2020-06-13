/*******************************************************************
*  Copyright(c) 2000-2018 syswin
*  All rights reserved.
*
*  文件名称: TNScreenshotEditOptionData.h
*  说明:    截屏编辑选项数据类
******************************************************************/
#ifndef TNSCREENSHOTEDITOPTIONDATA_H
#define TNSCREENSHOTEDITOPTIONDATA_H
#include <QColor>
class TNScreenShotTextEdit;

//命令
enum CommandType
{
    ctNull = 0,
    ctRectangle,
    ctEllipse,
    ctArrow,
    ctBrush,
    ctText
};


//线宽
enum LineWidthSize
{
    lwsSmall = 0,
    lwsMiddle,
    lwsLarge
};

//矩形属性
struct RectangleAttribute
{
    LineWidthSize lineWidthSize;
    int nColorIndex;
};

//椭圆属性
struct EllipseAttribute
{
    LineWidthSize lineWidthSize;
    int nColorIndex;
};

//箭头属性
struct ArrowAttribute
{
    LineWidthSize lineWidthSize;
    int nColorIndex;
};

//画刷属性
struct BrushAttribute
{
    LineWidthSize lineWidthSize;
    int nColorIndex;
};

//文字属性
struct TextAttribute
{
    int nFontSize;
    int nColorIndex;
};


class TNScreenshotEditOptionData
{
public:
    CommandType currentCommand;
    RectangleAttribute rectangleAttribute;
    EllipseAttribute ellipseAttribute;
    ArrowAttribute arrowAttribute;
    BrushAttribute brushAttribute;
    TextAttribute textAttribute;
    TNScreenShotTextEdit *currentTextEdit;
    QColor getColor(CommandType type)
    {
        int nColorIndex = 0;
        switch (type)
        {
        case ctRectangle:
            nColorIndex = rectangleAttribute.nColorIndex;
            break;
        case ctEllipse:
            nColorIndex = ellipseAttribute.nColorIndex;
            break;
        case ctArrow:
            nColorIndex = arrowAttribute.nColorIndex;
            break;
        case ctBrush:
            nColorIndex = brushAttribute.nColorIndex;
            break;
        case ctText:
            nColorIndex = textAttribute.nColorIndex;
            break;
        default:
            break;
        }
        return colorList[nColorIndex];
    }
    static TNScreenshotEditOptionData * instance()
    {
        if (m_data == 0)
            m_data = new TNScreenshotEditOptionData();

        return m_data;
    }
    static void freeInstance()
    {
        delete m_data;
        m_data = 0;
    }

private:
    QList<QColor> colorList;
    static TNScreenshotEditOptionData *m_data;

private:
    TNScreenshotEditOptionData()
    {
        currentCommand = ctNull;
        rectangleAttribute.lineWidthSize = lwsSmall;
        rectangleAttribute.nColorIndex = 0;
        ellipseAttribute.lineWidthSize = lwsSmall;
        ellipseAttribute.nColorIndex = 0;
        arrowAttribute.lineWidthSize = lwsSmall;
        arrowAttribute.nColorIndex = 0;
        brushAttribute.lineWidthSize = lwsSmall;
        brushAttribute.nColorIndex = 0;
        textAttribute.nFontSize = 11;
        textAttribute.nColorIndex = 0;

        colorList.append(QColor(252, 55, 70));
        colorList.append(QColor(253, 96, 150));
        colorList.append(QColor(208, 90, 206));
        colorList.append(QColor(33, 170, 212));
        colorList.append(QColor(23, 162, 73));
        colorList.append(QColor(254, 206, 91));
        colorList.append(QColor(252, 103, 59));
        colorList.append(QColor(0, 0, 0));
        currentTextEdit = nullptr;
    }
};

#endif // TNSCREENSHOTEDITOPTIONDATA_H
