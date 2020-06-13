#include "TNEmojiSingleton.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>

TNEmojiSingleton::TNEmojiSingleton()
{
	init();
	initImage();
}

TNEmojiSingleton::~TNEmojiSingleton()
{

}

TNEmojiSingleton* TNEmojiSingleton::GetInstance()
{
	static TNEmojiSingleton instance;
	return &instance;
}

void TNEmojiSingleton::init()
{
	QFile file(":/Resources/Emoji.plist");
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		return;
	}
	QXmlStreamReader xmlReader(&file);
	if (xmlReader.readNextStartElement()){
		if (xmlReader.name() == "plist"){
			while (!xmlReader.atEnd()){
				QString name = xmlReader.name().toString();
				QString key;
				if (name == "key"){
					key = xmlReader.readElementText();
					xmlReader.readNextStartElement();
					name = xmlReader.name().toString();
					if (name == "string"){
						_mapEmojiI[key] = xmlReader.readElementText();
						xmlReader.readNextStartElement();
					}
				}
				else if (name == "dict"){
					xmlReader.readNextStartElement();
				}
				else{
					xmlReader.readNextStartElement();
				}
			}
		}
	}
	file.close();
}

void TNEmojiSingleton::initImage()
{
	QMap<QString, QString>::const_iterator itera = _mapEmojiI.begin();
	for (; itera != _mapEmojiI.end(); ++itera){
		QString image_path = ":/Resources/images/" + itera.value();
		QImage image;
		if (image.load(image_path)){
			_mapEmoji_Image[itera.key()] = image;
		}
	}
	//Ä¬ÈÏµÄ»ÒÉ«Í¼Æ¬±³¾°
	_grayImage.load(":/Resources/gray.jpg");
}