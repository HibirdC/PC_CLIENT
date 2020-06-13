#ifndef TNIMAGECTR_H
#define TNIMAGECTR_H

#include <QObject>
#include "TNNameSpace.h"
#include "common_global.h"

class COMMON_EXPORT TNImageCtr : public QObject
{
	Q_OBJECT

public:
	TNImageCtr(QObject *parent);
	~TNImageCtr();
    static TN::ImageType getImageType(const QString& imagePath);
	static QString getImageTypeRetString(const QString &imagePath);
    static bool speedLoadImage(const QString &imagePath,
                               bool adjust,
                               QImage& image_result,
                               QSize& adjust_size,
                               QString suffix="",
                               int quaLity=100);
    static bool isImageFile(const QString &filePath);
private:
    static void adjustImageSize(const QSize& ori_size,
                                QSize& adjusted_size);

};

#endif // TNIMAGECTR_H
