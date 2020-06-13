#ifndef TNIMAGEHELPER_H
#define TNIMAGEHELPER_H

#include <QImage>

class TNImageHelper
{
public:
    TNImageHelper();
    static bool rgb32ToRaw(QImage& image);
    static void rgb24Tobgr24(QImage& image);
    static void rgb32tobgr24(const QImage& image,unsigned char* dst);
};

#endif // TNIMAGEHELPER_H
