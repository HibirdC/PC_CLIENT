#include <QProcessEnvironment> 
#include <pugixml.hpp>
#include "XmlSingleton.h"
#include <QFile>
#include <qcoreapplication.h>
#include <qdebug.h>
#include "qtextcodec.h"

XmlSingleton* XmlSingleton::_Instance = NULL;
XmlSingleton::XmlSingleton()
{
	ReadAllAllPlugin();
}


XmlSingleton::~XmlSingleton()
{
	if (_Instance != NULL)
	{
		delete _Instance;
		_Instance = NULL;
	}
}

XmlSingleton* XmlSingleton::GetInstance()
{
	if (_Instance == NULL)
	{
		_Instance = new XmlSingleton();
	}
	return _Instance;
}

void XmlSingleton::ReadAllAllPlugin()
{
	QString fileName = "Plugin.xml";
	QString xmlPath = QCoreApplication::applicationDirPath() + "/" + fileName;
	Q_ASSERT(QFile::exists(xmlPath));

	pugi::xml_document doc;
#ifdef Q_OS_WIN
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	std::string stdPath = code->fromUnicode(xmlPath).data();
	pugi::xml_parse_result result = doc.load_file(stdPath.c_str());
#else
    pugi::xml_parse_result result = doc.load_file(xmlPath.toStdString().c_str());
#endif
	if (result)
	{
		pugi::xml_node cfg_node = doc.child("PluginCfg");
		for (pugi::xml_node plugin_node = cfg_node.first_child(); plugin_node; plugin_node = plugin_node.next_sibling())
		{
			std::shared_ptr<XmlPluginStruct> XmlPluginStructPtr = std::make_shared<XmlPluginStruct>();
			XmlPluginStructPtr->strName = plugin_node.attribute("Name").as_string();
			XmlPluginStructPtr->strDescribe = plugin_node.attribute("Describe").as_string();
			XmlPluginStructPtr->strPath = plugin_node.attribute("Path").as_string();
			XmlPluginStructPtr->nDimension = plugin_node.attribute("Dimension").as_int();
			XmlPluginStructPtr->bEnable = plugin_node.attribute("Enable").as_bool();
            _PluginVec.push_back(XmlPluginStructPtr);
		}
	}
	else
	{
		return;
	}
}

XmlPluginStructVec XmlSingleton::GetAllPlugin()
{
	return _PluginVec;
}

XmlPluginStructVec XmlSingleton::GetPluginsByDimension(int Dimension)
{
	XmlPluginStructVec tempXmlPluginStructVec;
    std::vector<std::shared_ptr<XmlPluginStruct> >::iterator iter = _PluginVec.begin();
	for (; iter != _PluginVec.end(); iter++)
	{
		if ((*iter)->nDimension == Dimension)
		{
			tempXmlPluginStructVec.push_back(*iter);
		}
	}
	return tempXmlPluginStructVec;
}

XmlPluginStructVec XmlSingleton::GetEnablePluginsByDimension(int Dimension)
{
	XmlPluginStructVec tempXmlPluginStructVec;
    std::vector<std::shared_ptr<XmlPluginStruct> >::iterator iter = _PluginVec.begin();
    for (; iter != _PluginVec.end(); iter++)
	{
		if (((*iter)->nDimension == Dimension) && ((*iter)->bEnable))
		{
			tempXmlPluginStructVec.push_back(*iter);
		}
	}
	return tempXmlPluginStructVec;
}
