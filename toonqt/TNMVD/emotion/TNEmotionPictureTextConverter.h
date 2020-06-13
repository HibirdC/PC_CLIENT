#ifndef TNEMOTIONPICTURETEXTCONVERTER_H
#define TNEMOTIONPICTURETEXTCONVERTER_H

#include <QObject>

class TNEmotionPictureTextConverter : public QObject
{
    Q_OBJECT

public:
    explicit TNEmotionPictureTextConverter(QObject *parent = 0);
    ~TNEmotionPictureTextConverter();

    static QString emotionPictureToText(const QString &htmlText);
};

#endif // TNEMOTIONPICTURETEXTCONVERTER_H
