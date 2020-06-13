#ifndef TNDATASTATISTICS_H
#define TNDATASTATISTICS_H
#include "TNHttpDam.h"
#include <QObject>

class NETWORKAPI_EXPORT TNDataStatistics : public QObject
{
	Q_OBJECT

private:
	TNDataStatistics(QObject *parent);
	~TNDataStatistics();
	void RecordDamData(OPERATE_TYPE type, const TNPluginParamPtr &pluginParam);
	void RecordDamData(FUNCTION_TYPE type, const TNPluginParamPtr &pluginParam);
	void RecordDamSearchData(FUNCTION_TYPE type, const TNPluginParamPtr &pluginParam, const TNDamSearchData& searchData);
	void CloseRecord();
public: 
	static TNDataStatistics* GetInstance();
	//记录设备埋点
	static void RecordStatisData(OPERATE_TYPE type, const TNPluginParamPtr &pluginParam);
	//记录功能埋点
	static void RecordFuncStatisData(FUNCTION_TYPE type, const TNPluginParamPtr &pluginParam);
	static void RecordSearchStaticsData(FUNCTION_TYPE type, const TNPluginParamPtr &pluginParam, const TNDamSearchData& searchData);
	static void CloseStatisData();
private:
	TNHttpDam*	_httpDam;
};

#endif // TNDATASTATISTICS_H
