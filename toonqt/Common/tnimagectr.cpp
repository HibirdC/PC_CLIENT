#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <QDebug>
#include <QImageReader>
#include <QFileInfo>
#include <QDir>

#include "tnimagectr.h"

using namespace std;

TNImageCtr::TNImageCtr(QObject *parent)
	: QObject(parent)
{

}

TNImageCtr::~TNImageCtr()
{

}
TN::ImageType TNImageCtr::getImageType(const QString& imagePath)
{
	TN::ImageType result = TN::nothing;
#ifdef WIN32
	ifstream inFile(imagePath.toStdWString().c_str(), ios::binary);
#else
	ifstream inFile(imagePath.toStdString().c_str(), ios::binary);
#endif
	if (!inFile.is_open()){
        qInfo() << "[Common] [getImageType] getImageType:" << strerror(errno) << "image_path:" << imagePath;
		return TN::nothing;
    }else{
        qDebug() << "getImageType succssed-------------" << "image_path" << imagePath;
    }

	unsigned char PNGHeader[] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A }; //PNG
	unsigned char BmpHeader[] = { 0x42, 0x4d, 0xf6, 0xb8, 0x59 }; //BMP
	unsigned char JPGHeader[] = { 0xff, 0xd8, 0xff, 0xe1 };   //JPG,JPEG
	unsigned char GIFHeader[] = { 0x47, 0x49, 0x46, 0x38 }; //GIF

	unsigned char file_head[8] = { 0 };
    for(int i=0;i<8;i++){
        inFile >> file_head[i];
    }
	switch (file_head[0])
	{
	case 0xff:
		if (file_head[1] == JPGHeader[1])
			result = TN::jpg;//jpeg
		break;
	case 0x42:
		if (file_head[1] == BmpHeader[1])
			result = TN::bmp;//bmp
		break;
	case 0x89:
		if (file_head[1] == PNGHeader[1] && file_head[2] == PNGHeader[2] && file_head[3] == PNGHeader[3])
			result = TN::png;//png
		break;
	case 0x47:
        if (file_head[1] == GIFHeader[1] && file_head[2] == GIFHeader[2] && file_head[3] == GIFHeader[3])
			result = TN::gif;
		break;
	default:
		result = TN::nothing;
	}
	inFile.close();
	return result;
}
QString TNImageCtr::getImageTypeRetString(const QString &imagePath)
{
	QString file_suffix;
	switch (getImageType(imagePath))
	{
	case TN::bmp:
		file_suffix = ".bmp";
		break;
	case TN::jpg:
		file_suffix = ".jpg";
		break;
	case TN::png:
		file_suffix = ".png";
		break;
	case TN::gif:
		file_suffix = ".gif";
		break;
	default:
		break;
	}
	return file_suffix;
}

bool TNImageCtr::speedLoadImage(const QString &imagePath,
                                bool adjust,
                                QImage& image_result,
                                QSize& adjust_size,
                                QString suffix,
                                int quaLity)
{
    if(suffix.isEmpty()){
        suffix = getImageTypeRetString(imagePath);
    }
    QImageReader imageReader(imagePath,suffix.toStdString().c_str());
    int image_width = imageReader.size().width();
    int image_height = imageReader.size().height();
    QSize ori_sze(image_width,image_height);
    if(adjust){
        if(ori_sze.width() > adjust_size.width() ||
                ori_sze.height() > adjust_size.height()){
            adjustImageSize(ori_sze,adjust_size);
        }else{
            adjust_size = ori_sze;
        }
    }
    imageReader.setScaledSize(adjust_size);
    imageReader.setQuality(quaLity);
    if(!imageReader.canRead())
        return false;
    image_result = imageReader.read();
    if(image_result.isNull())
        return false;
    return true;
}

void TNImageCtr::adjustImageSize(const QSize &ori_size,
                                 QSize& adjusted_size)
{
    if (ori_size.width() > adjusted_size.width()){
        int new_width = adjusted_size.width();
        float rate = new_width * 1.0f / ori_size.width();
        adjusted_size.setHeight(rate * ori_size.height());
        adjusted_size.setWidth(new_width);
    }
    if (ori_size.height() > adjusted_size.height()){
        int new_height = adjusted_size.height();
        float rate = new_height * 1.0f / ori_size.height();
        adjusted_size.setWidth(rate * ori_size.width());
        adjusted_size.setHeight(new_height);
    }
}

bool TNImageCtr::isImageFile(const QString &filePath)
{
    bool yes = false;

    QFileInfo fileInfo(filePath);
    if (fileInfo.size() > MAX_PIC_SIZE){
        return false;
    }

    QString suffix = fileInfo.suffix();
    QString picSuffix = "png,jpg,jpeg,bmp,gif";
    QStringList picSuffixList = picSuffix.split(",");
    if (picSuffixList.indexOf(suffix) != -1 || picSuffixList.indexOf(suffix.toLower()) != -1){
        yes = true;
    }else{
        TN::ImageType image_type = getImageType(filePath);
        if ((image_type == TN::jpg) || (image_type == TN::bmp) || (image_type == TN::png) || (image_type == TN::gif)){
            yes = true;
        }
    }
    return yes;
}
