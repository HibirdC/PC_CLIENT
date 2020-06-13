#ifndef XMLSINGLETON_H
#define XMLSINGLETON_H

#include <QObject> 

#include "common_global.h"

class COMMON_EXPORT XmlSingleton: public QObject
{
	Q_OBJECT
public:
	
	~XmlSingleton();
	static XmlSingleton* GetInstance();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets all plugin. </summary>
	///
	/// <remarks>	田恒, 2016/12/8. </remarks>
	///
	/// <returns>	all plugin. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	XmlPluginStructVec GetAllPlugin();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets plugins by dimension. </summary>
	///
	/// <remarks>	田恒, 2016/12/8. </remarks>
	///
	/// <param name="Dimension">	The dimension. </param>
	///
	/// <returns>	The plugins by dimension. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	XmlPluginStructVec GetPluginsByDimension(int Dimension);
	XmlPluginStructVec GetEnablePluginsByDimension(int Dimension);

private:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Reads all plugin. </summary>
	///
	/// <remarks>	田恒, 2016/12/8. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void ReadAllAllPlugin();

protected:
	XmlSingleton();

private:
	static XmlSingleton* _Instance;
	XmlPluginStructVec _PluginVec;
};

#endif

