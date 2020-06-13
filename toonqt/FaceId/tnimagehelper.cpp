#include "tnimagehelper.h"

TNImageHelper::TNImageHelper()
{

}

bool TNImageHelper::rgb32ToRaw(QImage &image)
{
    QImage rawImg(image.size(), QImage::Format_Indexed8);
    int height = image.height();
    int width = image.width();
    bool flag = false;
    QImage::Format image_format = image.format();
    switch (image_format) {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        /*
         * 精度高但效率要低一些
        for(int i=0;i<height;++i){
            uchar* line_src = image.scanLine(i);
            uchar* line_raw = rawImg.scanLine(i);
            for(int j=0;j<width;++j){
                //bgr
                int r_32 = line_src[j * 4 + 2];
                int g_32 = line_src[j * 4 + 1];
                int b_32 = line_src[j * 4];
                line_raw[j] = qGray(r_32,g_32,b_32);
            }
        }
        flag = true;
        image = rawImg;
        break;
        */
        for(int i = 0; i < height; i ++){
            const QRgb *pSrc = (QRgb *)image.constScanLine(i);
            uchar *pDest = (uchar *)rawImg.scanLine(i);
            for( int j = 0; j < width; j ++){
                 pDest[j] = qGray(pSrc[j]);
            }
        }
        flag = true;
        break;
    case QImage::Format_RGB888:
        for(int i=0;i<height;++i){
            uchar* line_src = image.scanLine(i);
            uchar* line_raw = rawImg.scanLine(i);
            for(int j=0;j<width;++j){
                //rgb
                int r_24 = line_src[j * 3];
                int g_24 = line_src[j * 3 + 1];
                int b_24 = line_src[j * 3 + 2];
                line_raw[j] = qGray(r_24,g_24,b_24);
            }
        }
        flag = true;
        break;
    default:
        break;
    }
    rawImg.setColorCount(256);
    for(int i = 0; i < 256; i++){
        rawImg.setColor(i, qRgb(i, i, i));
    }
    image = rawImg;
    return flag;
}

void TNImageHelper::rgb24Tobgr24(QImage &image)
{
    int height = image.height();
    int width = image.width();
    QImage::Format image_format = image.format();
    switch (image_format) {
    case QImage::Format_RGB888:
        for(int i=0;i<height;++i){
            uchar* line_src = image.scanLine(i);
            for(int j=0;j<width;++j){
                //rgb
                int r_24 = line_src[j * 3];
                int g_24 = line_src[j * 3 + 1];
                int b_24 = line_src[j * 3 + 2];
                line_src[j * 3] = b_24;
                line_src[j * 3 + 1] = g_24;
                line_src[j * 3 + 2] = r_24;
            }
        }
        break;
    default:
        break;
    }
}

void TNImageHelper::rgb32tobgr24(const QImage& image,unsigned char* dst)
{
    int height = image.height();
    int width = image.width();
    const unsigned char* src = image.bits();
    QImage::Format image_format = image.format();
    switch (image_format) {
    case QImage::Format_RGB32:
        for(int i=0;i<height;++i){
            for(int j=0;j<width;++j){
                memcpy(dst + i * width * 3 + j * 3,src + i * width * 4 + j * 4,3);
            }
        }
        break;
    default:
        break;
    }
}
