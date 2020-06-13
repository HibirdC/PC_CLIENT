#ifndef TNCOMMONDEALAVATOR_H
#define TNCOMMONDEALAVATOR_H

#include "TNMVD_global.h"
#include "TNNameSpace.h"

#include <QObject>
#include <QImage>
#include <QIcon>
#include <map>

class TNMVD_EXPORT TNCommonDealAvator : public QObject
{
	Q_OBJECT

public:
	TNCommonDealAvator(QObject *parent);
	~TNCommonDealAvator();

	static Cust_Type getCustomType(const QString &feedId);

	static QImage getTypeQImage(const QString& avatorPath, QSize size,
		Cust_Type type = cust_radius, TN::AvatarType sizeType = TN::Normal); 

	static QPixmap getTypeQPixmap(const QString& avatorPath, QSize size,
		Cust_Type type = cust_radius, TN::AvatarType sizeType = TN::Normal);

	static QIcon getTypeQIcon(const QString& avatorPath, QSize size,
		Cust_Type type = cust_radius, TN::AvatarType sizeType = TN::Normal);

    static bool speedLoadImage(const QString& image_path,
                                           const QString& image_type,
                                           QImage& image,
                                           const QSize& pic_size);
private:
    std::map<QString,QImage>  _map_image_avator;
};

#endif // TNCOMMONDEALAVATOR_H
