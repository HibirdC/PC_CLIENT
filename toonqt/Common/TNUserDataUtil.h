#ifndef TNUSERDATAUTIL_H
#define TNUSERDATAUTIL_H

#include <QObject>
#include "common_global.h"

class COMMON_EXPORT TNUserDataUtil : public QObject
{
public:
	TNUserDataUtil();
	~TNUserDataUtil();
	static TNUserDataUtil* GetInstance();
	void setUserPluginParam(TNPluginParamPtr pluginParam);
	TNPluginParamPtr getUserPluginParam();

private:
	TNPluginParamPtr _pluginParam;
};

#endif // TNUSERDATAUTIL_H
