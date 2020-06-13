#include "tncommondealavator.h"

#include <QPainter>
#include <QBitmap>
#include <QImageReader>
#include <QDebug>
#include <QFileInfo>
TNCommonDealAvator::TNCommonDealAvator(QObject *parent)
: QObject(parent)
{

}

TNCommonDealAvator::~TNCommonDealAvator()
{

}

Cust_Type TNCommonDealAvator::getCustomType(const QString &feedId)
{
	if (feedId.startsWith("g_"))
		return cust_hexagon;
	if (feedId.startsWith("c_"))
		return cust_ellipse;
	if (feedId.startsWith("gc_"))
		return cust_radius;
	return cust_radius;
}

QImage TNCommonDealAvator::getTypeQImage(const QString& avatorPath, QSize size,
	Cust_Type type /* = cust_radius */, TN::AvatarType sizeType)
{
    Q_UNUSED(sizeType);
	//统一产出80*80，遮罩统一为80*80，外部缩放。
	size = QSize(80, 80);
	QImage image;
    if(!speedLoadImage(avatorPath,".png",image,size)){
        image.load(QStringLiteral(":/Resources/DefaltAvarta.png"));
    }

	if (image.isNull()){
		return QImage();
	}
	QImage mask;
	switch (type)
	{
	case cust_hexagon:
		mask.load(":/Resources/mask_hexagon.png");
        break;
	case cust_ellipse:
		mask.load(":/Resources/mask_ellipse.png");
        break;
	case cust_radius:
		mask.load(":/Resources/mask-radius.png");
		break;
	default:
		break; 
	}
	if (!mask.isNull()){
		QImage pixMap = image.scaled(image.width(), image.height());
		QImage resultImage(size, QImage::Format_ARGB32_Premultiplied);
		QPainter painter(&resultImage);
		painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
		painter.setCompositionMode(QPainter::CompositionMode_Source);
		painter.fillRect(resultImage.rect(), Qt::transparent);
		//painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
		painter.setCompositionMode(QPainter::CompositionMode_Source);
		painter.drawImage(0, 0, mask);
		painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
		painter.drawImage(0, 0, pixMap.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
		painter.end();
		return resultImage;
	}else{
		return image.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}
}

QPixmap TNCommonDealAvator::getTypeQPixmap(const QString& avatorPath, QSize size, Cust_Type type, TN::AvatarType sizeType)
{
	QImage drawImage = TNCommonDealAvator::getTypeQImage(avatorPath, size, type, sizeType);
	return QPixmap::fromImage(drawImage);
}

QIcon TNCommonDealAvator::getTypeQIcon(const QString& avatorPath, QSize size, Cust_Type type, TN::AvatarType sizeType)
{
	return QIcon(TNCommonDealAvator::getTypeQPixmap(avatorPath, size, type, sizeType));
}

bool TNCommonDealAvator::speedLoadImage(const QString& image_path,
                                           const QString& image_type,
                                           QImage& image,
                                           const QSize& pic_size)
{
    QFileInfo file_info(image_path);
    if(!file_info.exists()){
        return false;
    }
    int size = file_info.size();
    //qDebug() << "file_info size:" << size;
    QImageReader image_reader(image_path, image_type.toStdString().c_str());
    if (!image_reader.canRead()){
        return false;
    }

    image_reader.setScaledSize(pic_size);
    image_reader.setQuality(100);

    image = image_reader.read();
    if (image.isNull()){
        return false;
    }
    return true;
}
