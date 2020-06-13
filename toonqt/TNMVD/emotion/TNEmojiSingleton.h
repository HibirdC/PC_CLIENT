#ifndef TNEMOJISINGLETON_H
#define TNEMOJISINGLETON_H

#include "TNMVD_global.h"
#include <QMap>
#include <QImage>

class TNMVD_EXPORT TNEmojiSingleton
{
public:
	~TNEmojiSingleton();
	static TNEmojiSingleton* GetInstance();

	QMap<QString, QString> _mapEmojiI;
	QMap<QString, QImage>  _mapEmoji_Image;//±íÇé»º´æ
	QImage& getGrayImage(){ return _grayImage; }
private:
	TNEmojiSingleton();
	void init();
	void initImage();
private:
	QImage				   _grayImage;
};
#endif
