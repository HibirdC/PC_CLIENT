#include <QMutex>
#include "TNUserDataUtil.h"

TNUserDataUtil::TNUserDataUtil()
{

}

TNUserDataUtil::~TNUserDataUtil()
{

}
TNUserDataUtil* TNUserDataUtil::GetInstance()
{
	static TNUserDataUtil* userData;
	static QMutex s_mutex;
	if (userData == NULL)
	{
		QMutexLocker locker(&s_mutex);
		if (userData == NULL)
			userData = new TNUserDataUtil;
	}
	return userData;
}
void TNUserDataUtil::setUserPluginParam(TNPluginParamPtr pluginParam)
{
	_pluginParam = pluginParam;
}
TNPluginParamPtr TNUserDataUtil::getUserPluginParam()
{
	return _pluginParam;
}
